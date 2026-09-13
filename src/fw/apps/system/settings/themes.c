/* SPDX-FileCopyrightText: 2025 Elad Dvash */
/* SPDX-License-Identifier: Apache-2.0 */

#include "themes.h"
#include "menu.h"
#include "option_menu.h"
#include "window.h"

#include "applib/ui/dialogs/dialog.h"
#include "applib/ui/dialogs/expandable_dialog.h"
#include "applib/graphics/gtypes.h"
#include "applib/graphics/graphics.h"
#include "applib/ui/menu_layer.h"
#include "kernel/pbl_malloc.h"
#include "pbl/services/i18n/i18n.h"
#include "shell/prefs.h"
#include "system/passert.h"
#include "pbl/util/size.h"

#ifdef CONFIG_THEMING

#define DEFAULT_THEME_HIGHLIGHT_COLOR GColorVividCerulean
#define INVERT_ENTRY_INDEX 1

typedef struct ColorDefinition {
  const char *name;
  const GColor color;
} ColorDefinition;

static const ColorDefinition s_color_definitions[12] = {
  {i18n_noop("Default"), GColorClear},
  {i18n_noop("Invert"), GColorClear},
  {i18n_noop("Red"), GColorSunsetOrange},
  {i18n_noop("Orange"), GColorChromeYellow},
  {i18n_noop("Yellow"), GColorYellow},
  {i18n_noop("Green"), GColorGreen},
  {i18n_noop("Cyan"), GColorCyan},
  {i18n_noop("Light Blue"), GColorVividCerulean},
  {i18n_noop("Royal Blue"), GColorVeryLightBlue},
  {i18n_noop("Purple"), GColorLavenderIndigo},
  {i18n_noop("Magenta"), GColorMagenta},
  {i18n_noop("Pink"), GColorBrilliantRose},
};
static const char* color_names[ARRAY_LENGTH(s_color_definitions)];
static bool color_names_initialized = false;

static const char** prv_get_color_names(bool short_list) {
  if (!color_names_initialized) {
    for (size_t i = 0; i < ARRAY_LENGTH(s_color_definitions); i++) {
      color_names[i] = (char*)s_color_definitions[i].name;
    }
    color_names_initialized = true;
  }
  return color_names;
}




static int prv_color_to_index(GColor color, GColor default_color) {
  if (color.argb == GColorClear.argb || color.argb == default_color.argb) {
    return 0;
  }
  for (size_t i = 0; i < ARRAY_LENGTH(s_color_definitions); i++) {
    GColor selected_color = s_color_definitions[i].color;
    if ((uint8_t)(color.argb) == (uint8_t)(selected_color.argb)) {
      return i;
    }
  }
  return -1;
}


/////////////////////////////
// Unified Accent Color Settings
/////////////////////////////

static void prv_color_menu_select(OptionMenu *option_menu, int selection, void *context) {
  if (selection == INVERT_ENTRY_INDEX) {
    shell_prefs_set_theme_highlight_inverted(true);
    app_window_stack_remove(&option_menu->window, true /* animated */);
    return;
  }

  GColor color;
  if (selection == 0) {
    /* Default option selected -> restore default color. */
    color = DEFAULT_THEME_HIGHLIGHT_COLOR;
  } else {
    color = s_color_definitions[selection].color;
  }

  /* Set the theme highlight color */
  shell_prefs_set_theme_highlight_inverted(false);
  shell_prefs_set_theme_highlight_color(color);

  app_window_stack_remove(&option_menu->window, true /* animated */);
}

static void prv_option_menu_selection_will_change(OptionMenu *option_menu,
                                                   uint16_t new_row,
                                                   uint16_t old_row,
                                                   void *context) {
  if (new_row == old_row) {
    return;
  }
  GColor normal_bg = shell_prefs_get_theme_normal_background();
  option_menu_set_status_colors(option_menu, normal_bg, gcolor_legible_over(normal_bg));
  if (new_row == INVERT_ENTRY_INDEX) {
    GColor color = shell_prefs_get_theme_dark_background() ? GColorWhite : GColorBlack;
    option_menu_set_highlight_colors(option_menu, color, gcolor_legible_over(color));
    return;
  }
  GColor color = s_color_definitions[new_row].color;
  if (color.argb != GColorClear.argb) {
    option_menu_set_highlight_colors(option_menu, color, gcolor_legible_over(color));
  } else {
    option_menu_set_highlight_colors(option_menu, DEFAULT_THEME_HIGHLIGHT_COLOR, gcolor_legible_over(DEFAULT_THEME_HIGHLIGHT_COLOR));
  }
}

static OptionMenu *prv_push_color_menu(void) {
  const char *title = i18n_noop("Accent Color");
  int selected = shell_prefs_get_theme_highlight_inverted() ? INVERT_ENTRY_INDEX :
      prv_color_to_index(shell_prefs_get_theme_highlight_color(), DEFAULT_THEME_HIGHLIGHT_COLOR);
  const char** color_names = prv_get_color_names(false);
  const OptionMenuCallbacks callbacks = {
    .select = prv_color_menu_select,
    .selection_will_change = prv_option_menu_selection_will_change,
  };
  if (selected < 0) {
    // Invalid color stored - fall back to default instead of crashing
    // This can happen if an invalid color was synced from the phone
    PBL_LOG_WRN("Invalid menu color, using default");
    selected = 0;
  }
  OptionMenu * const option_menu = settings_option_menu_create(
      title, OptionMenuContentType_SingleLine, selected, &callbacks,
      ARRAY_LENGTH(s_color_definitions), true /* icons_enabled */, color_names, NULL);

  if (option_menu) {
    if (selected == INVERT_ENTRY_INDEX) {
      GColor color = shell_prefs_get_theme_dark_background() ? GColorWhite : GColorBlack;
      option_menu_set_highlight_colors(option_menu, color, gcolor_legible_over(color));
    } else if (selected == 0) {
      option_menu_set_highlight_colors(option_menu, DEFAULT_THEME_HIGHLIGHT_COLOR,
                                       gcolor_legible_over(DEFAULT_THEME_HIGHLIGHT_COLOR));
    } else {
      option_menu_set_highlight_colors(option_menu, s_color_definitions[selected].color,
                                       gcolor_legible_over(s_color_definitions[selected].color));
    }
  }

  return option_menu;
}

/////////////////////////////
// Background Setting
/////////////////////////////

static void prv_background_menu_select(OptionMenu *option_menu, int selection, void *context) {
  shell_prefs_set_theme_dark_background(selection == 1);
  app_window_stack_remove(&option_menu->window, true /* animated */);
}

static void prv_theme_menu_selection_will_change(OptionMenu *option_menu, uint16_t new_row,
                                                 uint16_t old_row, void *context) {
  if (new_row == old_row) {
    return;
  }
  GColor normal_bg = shell_prefs_get_theme_normal_background();
  option_menu_set_status_colors(option_menu, normal_bg, gcolor_legible_over(normal_bg));
  GColor highlight_bg = shell_prefs_get_theme_highlight_color();
  option_menu_set_highlight_colors(option_menu, highlight_bg, gcolor_legible_over(highlight_bg));
}

static OptionMenu *prv_push_background_menu(void) {
  const char *title = i18n_noop("Background");
  static const char *s_background_names[] = { i18n_noop("Light"), i18n_noop("Dark") };
  int selected = shell_prefs_get_theme_dark_background() ? 1 : 0;
  const OptionMenuCallbacks callbacks = {
    .select = prv_background_menu_select,
    .selection_will_change = prv_theme_menu_selection_will_change,
  };
  return settings_option_menu_create(
      title, OptionMenuContentType_SingleLine, selected, &callbacks,
      ARRAY_LENGTH(s_background_names), true /* icons_enabled */, s_background_names, NULL);
}

/////////////////////////////
// Themes Top Menu
/////////////////////////////

static void prv_top_menu_select(OptionMenu *option_menu, int selection, void *context) {
  OptionMenu *next_menu = (selection == 0) ? prv_push_color_menu() : prv_push_background_menu();
  if (next_menu) {
    app_window_stack_push(&next_menu->window, true /* animated */);
  }
}

static OptionMenu *prv_push_top_menu(void) {
  const char *title = i18n_noop("Themes");
  static const char *s_top_menu_rows[] = { "Accent Color", "Background" };
  const OptionMenuCallbacks callbacks = {
    .select = prv_top_menu_select,
    .selection_will_change = prv_theme_menu_selection_will_change,
  };
  return settings_option_menu_create(
      title, OptionMenuContentType_SingleLine, OPTION_MENU_CHOICE_NONE, &callbacks,
      ARRAY_LENGTH(s_top_menu_rows), false /* icons_enabled */, s_top_menu_rows, NULL);
}
#endif // CONFIG_THEMING

static Window *prv_create_top_menu(void) {
#ifdef CONFIG_THEMING
  OptionMenu *option_menu = prv_push_top_menu();
  return option_menu ? &option_menu->window : NULL;
#else
  WTF;
  return NULL;
#endif
}

static Window *prv_init(void) {
  return prv_create_top_menu();
}


const SettingsModuleMetadata *settings_themes_get_info(void) {
  static const SettingsModuleMetadata s_module_info = {
    /// Title of the Themes Settings submenu in Settings
    .name = i18n_noop("Themes"),
    .init = prv_init,
  };

  return &s_module_info;
}
