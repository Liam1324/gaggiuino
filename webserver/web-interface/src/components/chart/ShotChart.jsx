import React, {
  useEffect, useRef, useState, useMemo,
} from 'react';
import PropTypes from 'prop-types';
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  TimeScale,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';
import { useTheme, alpha } from '@mui/material';
import getShotChartConfig from './ChartConfig';

ChartJS.register(
  CategoryScale,
  LinearScale,
  TimeScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
);

function mapDataPointToLabel(dataPoint) {
  if (!dataPoint.timeInShot) {
    return 0;
  }

  return dataPoint.timeInShot / 1000;
}

function getLabels(input) {
  return input.map(mapDataPointToLabel);
}

function getDataset(input, key) {
  return input.map((dp) => dp[key]);
}

function mapToChartData(input, theme) {
  return {
    labels: getLabels(input),
    datasets: [
      {
        label: 'Temperature',
        data: getDataset(input, 'temperature'),
        backgroundColor: alpha(theme.palette.temperature.main, 0.8),
        borderColor: theme.palette.temperature.main,
        tension: 0.3,
        yAxisID: 'y1',
      },
      {
        label: 'Pressure',
        data: getDataset(input, 'pressure'),
        backgroundColor: alpha(theme.palette.pressure.main, 0.8),
        borderColor: theme.palette.pressure.main,
        tension: 0.3,
        yAxisID: 'y2',
      },
      {
        label: 'Pump Flow',
        data: getDataset(input, 'pumpFlow'),
        backgroundColor: alpha(theme.palette.flow.main, 0.8),
        borderColor: theme.palette.flow.main,
        tension: 0.3,
        yAxisID: 'y2',
      },
      {
        label: 'Weight Flow',
        data: getDataset(input, 'weightFlow'),
        backgroundColor: alpha(theme.palette.weightFlow.main, 0.8),
        borderColor: theme.palette.weightFlow.main,
        tension: 0.3,
        yAxisID: 'y2',
      },
      {
        label: 'Weight',
        data: getDataset(input, 'shotWeight'),
        backgroundColor: alpha(theme.palette.weight.main, 0.8),
        borderColor: theme.palette.weight.main,
        tension: 0.3,
        yAxisID: 'y1',
      },
      {
        label: 'Target Pressure',
        data: getDataset(input, 'targetPressure'),
        backgroundColor: alpha(theme.palette.pressure.main, 0.3),
        borderColor: alpha(theme.palette.pressure.main, 0.6),
        tension: 0.3,
        borderDash: [8, 4],
        yAxisID: 'y2',
      },
      {
        label: 'Target Flow',
        data: getDataset(input, 'targetPumpFlow'),
        backgroundColor: alpha(theme.palette.flow.main, 0.3),
        borderColor: alpha(theme.palette.flow.main, 0.6),
        tension: 0.3,
        borderDash: [8, 4],
        yAxisID: 'y2',
      },
    ],
  };
}

// function popDataFromChartData(chartData) {
//   chartData.labels.shift();
//   chartData.datasets.forEach((dataset) => dataset.data.shift());
// }

function addDataPointToChartData(chartData, dataPoint) {
  // while (maxLength > 0 && chartData.labels.length >= maxLength) {
  //   popDataFromChartData(chartData);
  // }
  if (!dataPoint) {
    return;
  }

  // If we pull a second shot while he graph is open push the
  // datapoints of the previous shot back in time so that the new shot
  // begins from time=0sec
  const newTimeLabel = mapDataPointToLabel(dataPoint);
  const previousMaxTimeLabel = chartData.labels[chartData.labels.length - 1] || 0;
  if (previousMaxTimeLabel > newTimeLabel) {
    chartData.labels.forEach((label, index) => {
      // eslint-disable-next-line no-param-reassign
      chartData.labels[index] = label - previousMaxTimeLabel;
    });
  }

  chartData.labels.push(newTimeLabel);
  chartData.datasets[0].data.push(dataPoint.temperature);
  chartData.datasets[1].data.push(dataPoint.pressure);
  chartData.datasets[2].data.push(dataPoint.pumpFlow);
  chartData.datasets[3].data.push(dataPoint.weightFlow);
  chartData.datasets[4].data.push(dataPoint.shotWeight);
  chartData.datasets[5].data.push(dataPoint.targetPressure);
  chartData.datasets[6].data.push(dataPoint.targetPumpFlow);
}

function Chart({ data, newDataPoint }) {
  const chartRef = useRef(null);
  const theme = useTheme();
  const config = useMemo(() => getShotChartConfig(theme), [theme]);
  const [chartData, setChartData] = useState(mapToChartData([], theme));

  useEffect(() => {
    if (newDataPoint && chartData.labels.length < data.length - 1) {
      return;
    }
    setChartData(mapToChartData(data, theme));
  }, [data]);

  useEffect(() => {
    addDataPointToChartData(chartData, newDataPoint);
    chartRef.current.data.labels = chartData.labels;
    chartData.datasets.forEach((dataset, index) => {
      chartRef.current.data.datasets[index].data = dataset.data;
    });
    chartRef.current.update();
  }, [newDataPoint]);

  return (
    <Line
      ref={chartRef}
      options={config}
      data={chartData}
    />
  );
}

export default Chart;

export const ShotChartDataPointType = PropTypes.shape({
  timeInShot: PropTypes.number,
  temperature: PropTypes.number,
  pressure: PropTypes.number,
  pumpFlow: PropTypes.number,
  weightFlow: PropTypes.number,
  shotWeight: PropTypes.number,
  targetTemperature: PropTypes.number,
  targetPumpFlow: PropTypes.number,
  targetPressure: PropTypes.number,
});

Chart.propTypes = {
  data: PropTypes.arrayOf(ShotChartDataPointType),
  newDataPoint: ShotChartDataPointType,
  // maxLength: PropTypes.number,
};

Chart.defaultProps = {
  data: undefined,
  newDataPoint: undefined,
  // maxLength: undefined,
};
