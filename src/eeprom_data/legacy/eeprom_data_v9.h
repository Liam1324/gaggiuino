#ifndef EEPROM_DATA_V4_H
#define EEPROM_DATA_V4_H

#include "../eeprom_data.h"
#include "../eeprom_metadata.h"

/**
* Version 9:
* - Multiple changes to the brew profile settings to support more customization of phases
* - Re-organize fields
*/

struct eepromValues_t_v9 {
  uint16_t setpoint;
  uint16_t steamSetPoint;
  uint16_t offsetTemp;
  uint16_t hpwr;
  uint16_t mainDivider;
  uint16_t brewDivider;
  // Preinfusion vars section
  bool     preinfusionState;
  bool     preinfusionFlowState;
  uint16_t preinfusionSec;
  float    preinfusionBar;
  float    preinfusionFlowVol;
  uint16_t preinfusionFlowTime;
  float    preinfusionFlowPressureTarget;
  float    preinfusionPressureFlowTarget;
  float    preinfusionFilled;
  bool     preinfusionPressureAbove;
  float    preinfusionWeightAbove;
  // Soak vars section
  bool     soakState;
  uint16_t soakTimePressure;
  uint16_t soakTimeFlow;
  float    soakKeepPressure;
  float    soakKeepFlow;
  float    soakBelowPressure;
  float    soakAbovePressure;
  float    soakAboveWeight;
  // PI -> PF ramp settings
  uint16_t preinfusionRamp;
  uint16_t preinfusionRampSlope;
  // Profiling vars section
  bool     profilingState;
  bool     flowProfileState;
  float    pressureProfilingStart;
  float    pressureProfilingFinish;
  uint16_t pressureProfilingHold;
  float    pressureProfilingHoldLimit;
  uint16_t pressureProfilingSlope;
  uint16_t pressureProfilingSlopeShape;
  float    pressureProfilingFlowRestriction;
  float    flowProfileStart;
  float    flowProfileEnd;
  uint16_t flowProfileHold;
  float    flowProfileHoldLimit;
  uint16_t flowProfileSlope;
  uint16_t flowProfileSlopeShape;
  float    flowProfilingPressureRestriction;
  // Settings vars section
  uint16_t powerLineFrequency;
  uint16_t lcdSleep;
  bool     warmupState;
  bool     homeOnShotFinish;
  bool     brewDeltaState;
  bool     basketPrefill;
  int      scalesF1;
  int      scalesF2;
  float    pumpFlowAtZero;
  bool     stopOnWeightState;
  float    shotDose;
  float    shotStopOnCustomWeight;
  uint16_t shotPreset;
};

static bool upgradeSchema_v9(eepromValues_t &targetValues, eepromValues_t_v9 &loadedValues) {
  targetValues.setpoint = loadedValues.setpoint;
  targetValues.steamSetPoint = loadedValues.steamSetPoint;
  targetValues.offsetTemp = loadedValues.offsetTemp;
  targetValues.hpwr = loadedValues.hpwr;
  targetValues.mainDivider = loadedValues.mainDivider;
  targetValues.brewDivider = loadedValues.brewDivider;
  ACTIVE_PROFILE(targetValues).preinfusionState = loadedValues.preinfusionState;
  ACTIVE_PROFILE(targetValues).preinfusionFlowState = loadedValues.preinfusionFlowState;
  ACTIVE_PROFILE(targetValues).preinfusionSec = loadedValues.preinfusionSec;
  ACTIVE_PROFILE(targetValues).preinfusionBar = loadedValues.preinfusionBar;
  ACTIVE_PROFILE(targetValues).preinfusionFlowVol = loadedValues.preinfusionFlowVol;
  ACTIVE_PROFILE(targetValues).preinfusionFlowTime = loadedValues.preinfusionFlowTime;
  ACTIVE_PROFILE(targetValues).preinfusionFlowPressureTarget = loadedValues.preinfusionFlowPressureTarget;
  ACTIVE_PROFILE(targetValues).preinfusionPressureFlowTarget = loadedValues.preinfusionPressureFlowTarget;
  ACTIVE_PROFILE(targetValues).preinfusionFilled = loadedValues.preinfusionFilled;
  ACTIVE_PROFILE(targetValues).preinfusionPressureAbove = loadedValues.preinfusionPressureAbove;
  ACTIVE_PROFILE(targetValues).preinfusionWeightAbove = loadedValues.preinfusionWeightAbove;
  ACTIVE_PROFILE(targetValues).soakState = loadedValues.soakState;
  ACTIVE_PROFILE(targetValues).soakTimePressure = loadedValues.soakTimePressure;
  ACTIVE_PROFILE(targetValues).soakTimeFlow = loadedValues.soakTimeFlow;
  ACTIVE_PROFILE(targetValues).soakKeepPressure = loadedValues.soakKeepPressure;
  ACTIVE_PROFILE(targetValues).soakKeepFlow = loadedValues.soakKeepFlow;
  ACTIVE_PROFILE(targetValues).soakBelowPressure = loadedValues.soakBelowPressure;
  ACTIVE_PROFILE(targetValues).soakAbovePressure = loadedValues.soakAbovePressure;
  ACTIVE_PROFILE(targetValues).soakAboveWeight = loadedValues.soakAboveWeight;
  ACTIVE_PROFILE(targetValues).preinfusionRamp = loadedValues.preinfusionRamp;
  ACTIVE_PROFILE(targetValues).preinfusionRampSlope = loadedValues.preinfusionRampSlope;
  ACTIVE_PROFILE(targetValues).profilingState = loadedValues.profilingState;
  ACTIVE_PROFILE(targetValues).flowProfileState = loadedValues.flowProfileState;
  ACTIVE_PROFILE(targetValues).pressureProfilingStart = loadedValues.pressureProfilingStart;
  ACTIVE_PROFILE(targetValues).pressureProfilingFinish = loadedValues.pressureProfilingFinish;
  ACTIVE_PROFILE(targetValues).pressureProfilingHold = loadedValues.pressureProfilingHold;
  ACTIVE_PROFILE(targetValues).pressureProfilingHoldLimit = loadedValues.pressureProfilingHoldLimit;
  ACTIVE_PROFILE(targetValues).pressureProfilingSlope = loadedValues.pressureProfilingSlope;
  ACTIVE_PROFILE(targetValues).pressureProfilingSlopeShape = loadedValues.pressureProfilingSlopeShape;
  ACTIVE_PROFILE(targetValues).pressureProfilingFlowRestriction = loadedValues.pressureProfilingFlowRestriction;
  ACTIVE_PROFILE(targetValues).flowProfileStart = loadedValues.flowProfileStart;
  ACTIVE_PROFILE(targetValues).flowProfileEnd = loadedValues.flowProfileEnd;
  ACTIVE_PROFILE(targetValues).flowProfileHold = loadedValues.flowProfileHold;
  ACTIVE_PROFILE(targetValues).flowProfileHoldLimit = loadedValues.flowProfileHoldLimit;
  ACTIVE_PROFILE(targetValues).flowProfileSlope = loadedValues.flowProfileSlope;
  ACTIVE_PROFILE(targetValues).flowProfileSlopeShape = loadedValues.flowProfileSlopeShape;
  ACTIVE_PROFILE(targetValues).flowProfilingPressureRestriction = loadedValues.flowProfilingPressureRestriction;
  targetValues.powerLineFrequency = loadedValues.powerLineFrequency;
  targetValues.lcdSleep = loadedValues.lcdSleep;
  targetValues.warmupState = loadedValues.warmupState;
  targetValues.homeOnShotFinish = loadedValues.homeOnShotFinish;
  targetValues.brewDeltaState = loadedValues.brewDeltaState;
  targetValues.basketPrefill = loadedValues.basketPrefill;
  targetValues.scalesF1 = loadedValues.scalesF1;
  targetValues.scalesF2 = loadedValues.scalesF2;
  targetValues.pumpFlowAtZero = loadedValues.pumpFlowAtZero;
  targetValues.stopOnWeightState = loadedValues.stopOnWeightState;
  targetValues.shotDose = loadedValues.shotDose;
  targetValues.shotStopOnCustomWeight = loadedValues.shotStopOnCustomWeight;
  targetValues.shotPreset = loadedValues.shotPreset;
  return true;
}

REGISTER_LEGACY_EEPROM_DATA(9, eepromValues_t_v9, upgradeSchema_v9)

#endif