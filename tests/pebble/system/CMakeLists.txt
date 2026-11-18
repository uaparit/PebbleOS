# SPDX-FileCopyrightText: 2026 uaparit Basstardo
# SPDX-License-Identifier: Apache-2.0

pbl_clar_test(test_firmware_storage
  SOURCES
    pebble/system/firmware_storage.c
    tests/fakes/fake_spi_flash.c
  PLATFORMS emery
  OVERRIDES dummy_board
)
