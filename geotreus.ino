/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"

// Things I want to do maybe:
// - Play with one-shot mods
// - 2-purpose some of the home keys? Maybe for paren-likes.
// - maybe tap dance the paren-likes
// - play with leader keys? maybe for shifting to oddball layers or help text.

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)
#define UG(n) UnlockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  MACRO_SPECIAL_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

enum {
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  MOUSE
};

#define LEFT_MODS                                                              \
  ,Key_LeftShift ,Key_Esc ,Key_LeftGui ,Key_LeftControl ,Key_Backspace, MO(LOWER)
#define RIGHT_MODS                                                             \
  ,MO(RAISE) ,Key_Space ,Key_LeftAlt ,Key_Minus ,Key_Quote ,Key_RightShift

// clang-format off
KEYMAPS(
  // Keep this identical to the COLEMAK map (except for the Colemak keys)
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q     ,Key_W         ,Key_E           ,Key_R       ,Key_T
      ,Key_A     ,Key_S         ,Key_D           ,Key_F       ,Key_G
      ,Key_Z     ,Key_X         ,Key_C           ,Key_V       ,Key_B         ,Key_Tab
      LEFT_MODS

                   ,Key_Y          ,Key_U        ,Key_I     ,Key_O      ,Key_P
                   ,Key_H          ,Key_J        ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Enter  ,Key_N          ,Key_M        ,Key_Comma ,Key_Period ,Key_Slash
       RIGHT_MODS
  ),

  // Keep this identical to the QWERTY map (except for the Colemak keys)
  // TODO: fix this to match QWERTY
  [COLEMAK] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_F       ,Key_P         ,Key_G
      ,Key_A   ,Key_R   ,Key_S       ,Key_T         ,Key_D
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Tab
      LEFT_MODS

                             ,Key_J     ,Key_L      ,Key_U     ,Key_Y      ,Key_Semicolon
                             ,Key_H     ,Key_N      ,Key_E     ,Key_I      ,Key_O
               ,Key_Enter    ,Key_K     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
               RIGHT_MODS
  ),

  [LOWER] = KEYMAP_STACKED
  (
       XXX  ,XXX            ,Key_UpArrow     ,XXX             ,XXX
      ,XXX  ,Key_LeftArrow  ,Key_DownArrow   ,Key_RightArrow  ,Key_PageUp
      ,XXX  ,XXX            ,XXX             ,XXX             ,Key_PageDown  ,Key_Home
      ,___  ,Key_Delete     ,___             ,___             ,___           ,___

                           ,Key_Backtick ,Key_7  ,Key_8      ,Key_9    ,Key_Minus
                           ,Key_Period   ,Key_4  ,Key_5      ,Key_6    ,Key_Plus
              ,Key_End     ,Key_0        ,Key_1  ,Key_2      ,Key_3    ,Key_Backslash
              ,TG(MOUSE)   ,Key_Enter    ,___    ,Key_Equals ,Key_Star ,___
   ),

  [RAISE] = KEYMAP_STACKED
  (
       Key_F7    ,Key_F8     ,Key_F9  ,Key_F10  ,Consumer_FastForward
      ,Key_F4    ,Key_F5     ,Key_F6  ,Key_F11  ,Consumer_Rewind
      ,Key_F1    ,Key_F2     ,Key_F3  ,Key_F12  ,Consumer_PlaySlashPause ,Consumer_Mute
      ,___       ,Key_Delete ,___     ,___      ,TG(MOUSE)               ,___

                                 ,LCTRL(LALT(Key_LeftArrow)),LCTRL(LALT(Key_DownArrow)) ,LCTRL(LALT(Key_UpArrow)) ,LCTRL(LALT(Key_RightArrow)) ,LCTRL(LALT(Key_Enter))
                                 ,XXX                       ,Key_LeftCurlyBracket       ,Key_RightCurlyBracket    ,Key_LeftBracket             ,Key_RightBracket
      ,Consumer_VolumeIncrement  ,Consumer_VolumeDecrement  ,XXX                        ,XXX                      ,XXX                         ,Key_Backslash
      ,___                       ,Key_Enter                 ,___                        ,XXX                      ,XXX                         ,___
   ),

  [MOUSE] = KEYMAP_STACKED
  (
       XXX                   ,XXX        ,Key_mouseUp ,XXX        ,Key_mouseBtnL
      ,XXX                   ,Key_mouseL ,Key_mouseDn ,Key_mouseR ,Key_mouseBtnM
      ,XXX                   ,XXX        ,XXX         ,XXX        ,Key_mouseBtnR ,XXX
      ,M(MACRO_VERSION_INFO) ,XXX        ,___         ,___        ,___           ,UG(MOUSE)

                       ,Key_PrintScreen ,Key_mouseWarpEnd ,XXX             ,XXX ,XXX
                       ,Key_Insert      ,Key_mouseWarpNW  ,Key_mouseWarpNE ,XXX ,XXX
                       ,XXX             ,XXX              ,Key_mouseWarpSW ,Key_mouseWarpSE ,XXX ,XXX
                       ,UG(MOUSE)       ,XXX              ,___             ,XXX             ,XXX ,___
   )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  Qukeys,
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  OneShot,
  Macros,
  MouseKeys);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_QWERTY:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();

  QUKEYS(
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 0), LSHIFT(Key_9)),    // LShift/(
    kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(3, 0), LSHIFT(Key_9)),   // LShift/(
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 11), LSHIFT(Key_0)),   // RShift/)
    kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(3, 11), LSHIFT(Key_0)),  // RShift/)
  )

  EEPROMKeymap.setup(10);
}

void loop() {
  Kaleidoscope.loop();
}
