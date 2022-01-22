/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include <QtCore>
#include <QObject>
#include <QString>

namespace Board {

  enum Type
  {
    BOARD_UNKNOWN = -1,
    BOARD_SKY9X,
    BOARD_9XRPRO,
    BOARD_AR9X,
    BOARD_TARANIS_X7,
    BOARD_TARANIS_X7_ACCESS,
    BOARD_TARANIS_X9D,
    BOARD_TARANIS_X9DP,
    BOARD_TARANIS_X9DP_2019,
    BOARD_TARANIS_X9E,
    BOARD_HORUS_X12S,
    BOARD_X10,
    BOARD_X10_EXPRESS,
    BOARD_TARANIS_XLITE,
    BOARD_TARANIS_XLITES,
    BOARD_TARANIS_X9LITE,
    BOARD_TARANIS_X9LITES,
    BOARD_JUMPER_T12,
    BOARD_JUMPER_T16,
    BOARD_RADIOMASTER_TX16S,
    BOARD_JUMPER_T18,
    BOARD_RADIOMASTER_TX12,
    BOARD_RADIOMASTER_T8,
    BOARD_JUMPER_TLITE,
    BOARD_FLYSKY_NV14,
    BOARD_RADIOMASTER_ZORRO,
    BOARD_JUMPER_TPRO,
    BOARD_TYPE_COUNT,
    BOARD_TYPE_MAX = BOARD_TYPE_COUNT - 1
  };

  enum PotType
  {
    POT_NONE,
    POT_WITH_DETENT,
    POT_MULTIPOS_SWITCH,
    POT_WITHOUT_DETENT,
    POT_TYPE_COUNT
  };

  enum SliderType
  {
    SLIDER_NONE,
    SLIDER_WITH_DETENT,
    SLIDER_TYPE_COUNT
  };

  enum SwitchType
  {
    SWITCH_NOT_AVAILABLE,
    SWITCH_TOGGLE,
    SWITCH_2POS,
    SWITCH_3POS,
    SWITCH_TYPE_COUNT
  };

  enum StickAxes {
    STICK_AXIS_LH = 0,
    STICK_AXIS_LV,
    STICK_AXIS_RV,
    STICK_AXIS_RH,
    STICK_AXIS_COUNT
  };

  enum TrimAxes {
    TRIM_AXIS_LH = 0,
    TRIM_AXIS_LV,
    TRIM_AXIS_RV,
    TRIM_AXIS_RH,
    TRIM_AXIS_T5,
    TRIM_AXIS_T6,
    TRIM_AXIS_COUNT
  };

  enum TrimSwitches
  {
    TRIM_SW_LH_DEC,
    TRIM_SW_LH_INC,
    TRIM_SW_LV_DEC,
    TRIM_SW_LV_INC,
    TRIM_SW_RV_DEC,
    TRIM_SW_RV_INC,
    TRIM_SW_RH_DEC,
    TRIM_SW_RH_INC,
    TRIM_SW_T5_DEC,
    TRIM_SW_T5_INC,
    TRIM_SW_T6_DEC,
    TRIM_SW_T6_INC,
    TRIM_SW_COUNT
  };

  enum Capability {
    Sticks,
    Pots,
    FactoryInstalledPots,
    Sliders,
    MouseAnalogs,
    GyroAnalogs,
    MaxAnalogs,
    MultiposPots,
    MultiposPotsPositions,
    Switches,
    SwitchPositions,
    FactoryInstalledSwitches,
    NumTrims,
    NumTrimSwitches,
    HasRTC,
    HasColorLcd,
    NumFunctionSwitches,
    HasSDCard,
    HasInternalModuleSupport
  };

  struct SwitchInfo
  {
    SwitchType config;
    QString name;
  };

  struct SwitchPosition {
    SwitchPosition(unsigned int index, unsigned int position):
      index(index),
      position(position)
      {
      }
      unsigned int index;
      unsigned int position;
  };

  enum SwitchTypeMasks {
    SwitchTypeFlag2Pos    = 0x01,
    SwitchTypeFlag3Pos    = 0x02,
    SwitchTypeContext2Pos = SwitchTypeFlag2Pos,
    SwitchTypeContext3Pos = SwitchTypeFlag2Pos | SwitchTypeFlag3Pos
  };

}