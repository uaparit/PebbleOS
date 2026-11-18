/* SPDX-FileCopyrightText: 2026 Core Devices LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <pbl/services/mic_manager.h>

//! Records from the board microphone and hands frames of @p buffer_len samples to @p handler on
//! SysWorkq. The buffer is owned by the source until mic_source_stop() returns.
bool mic_source_start(MicDataHandlerCB handler, void *context, int16_t *buffer, size_t buffer_len);

//! Stops recording. No handler runs once it returns.
void mic_source_stop(void);

//! Picks the microphone and gain for the next start. The secondary microphone is the second
//! channel of a stereo capture, so it needs a device with two channels.
//! @param secondary Record the secondary microphone instead of the primary one.
//! @param gain_offset_db Gain relative to the device default, in dB.
void mic_source_set_input(bool secondary, int8_t gain_offset_db);
