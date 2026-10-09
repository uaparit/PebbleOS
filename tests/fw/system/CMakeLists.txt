# SPDX-FileCopyrightText: 2026 Core Devices LLC
# SPDX-License-Identifier: Apache-2.0

pbl_clar_test(test_firmware_storage
  SOURCES
    fw/system/firmware_storage.c
    tests/fakes/fake_spi_flash.c
  PLATFORMS obelix
  DEFINES CONFIG_PBLBOOT=1 CONFIG_FIRMWARE_SLOT=0
  OVERRIDES dummy_board
)

pbl_clar_test(test_flash_region
  SOURCES
    fw/flash_region/flash_region.c
  PLATFORMS obelix
  OVERRIDES dummy_board
)
