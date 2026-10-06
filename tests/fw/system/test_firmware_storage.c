/* SPDX-FileCopyrightText: 2026 uaparit Basstardo */
/* SPDX-License-Identifier: Apache-2.0 */

#include "system/firmware_storage.h"

#include "flash_region/flash_region.h"
#include <pbl/drivers/flash.h>

#include "clar.h"
#include "fake_spi_flash.h"

#include "stubs_logging.h"
#include "stubs_passert.h"

uint32_t flash_crc32(uint32_t flash_addr, uint32_t num_bytes) {
  return 0;
}

void flash_region_erase_optimal_range(uint32_t min_start, uint32_t max_start, uint32_t min_end,
                                      uint32_t max_end) {
}

#define SLOT_0 FLASH_REGION_FIRMWARE_SLOT_0_BEGIN
#define SLOT_1 FLASH_REGION_FIRMWARE_SLOT_1_BEGIN

static const FirmwareHeader s_header = {
  .magic = FIRMWARE_HEADER_MAGIC,
  .header_length = sizeof(FirmwareHeader),
  .fw_timestamp = 0x8000000068e3a1b2ULL,
  .fw_start = 512,
  .fw_length = 1024,
  .fw_crc = 0x12345678,
};

static void prv_write_header(uint32_t addr, const FirmwareHeader *header) {
  flash_write_bytes((const uint8_t *)header, addr, sizeof(*header));
}

void test_firmware_storage__initialize(void) {
  fake_spi_flash_init(SLOT_0, SLOT_1 + SUBSECTOR_SIZE_BYTES - SLOT_0);
}

void test_firmware_storage__cleanup(void) {
  fake_spi_flash_cleanup();
}

void test_firmware_storage__demote_clears_only_priority(void) {
  prv_write_header(SLOT_0, &s_header);

  firmware_storage_demote_firmware_slot(0);

  const FirmwareHeader header = firmware_storage_read_firmware_header(SLOT_0);
  FirmwareHeader expected = s_header;
  expected.fw_timestamp = 0;
  cl_assert_equal_m(&header, &expected, sizeof(expected));
}

void test_firmware_storage__demote_leaves_other_slot_untouched(void) {
  prv_write_header(SLOT_0, &s_header);
  prv_write_header(SLOT_1, &s_header);

  firmware_storage_demote_firmware_slot(1);

  const FirmwareHeader slot_0 = firmware_storage_read_firmware_header(SLOT_0);
  const FirmwareHeader slot_1 = firmware_storage_read_firmware_header(SLOT_1);
  cl_assert_equal_m(&slot_0, &s_header, sizeof(s_header));
  cl_assert(slot_1.fw_timestamp == 0);
}

void test_firmware_storage__demote_ignores_invalid_header(void) {
  firmware_storage_demote_firmware_slot(0);

  cl_assert_equal_i(fake_flash_write_count(), 0);
}

void test_firmware_storage__demote_skips_already_demoted_slot(void) {
  FirmwareHeader header = s_header;
  header.fw_timestamp = 0;
  prv_write_header(SLOT_0, &header);
  const uint32_t writes = fake_flash_write_count();

  firmware_storage_demote_firmware_slot(0);

  cl_assert_equal_i(fake_flash_write_count(), writes);
}
