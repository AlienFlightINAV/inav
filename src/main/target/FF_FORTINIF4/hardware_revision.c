/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/io.h"
#include "drivers/time.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = FORTINIF4_UNKNOWN;

static IO_t HWDetectPinA = IO_NONE;
static IO_t HWDetectPinB = IO_NONE;

void detectHardwareRevision(void)
{
    HWDetectPinA = IOGetByTag(IO_TAG(HW_PIN_A));
    IOInit(HWDetectPinA, OWNER_SYSTEM, RESOURCE_INPUT, 0);
    IOConfigGPIO(HWDetectPinA, IOCFG_IPU);
    HWDetectPinB = IOGetByTag(IO_TAG(HW_PIN_B));
    IOInit(HWDetectPinB, OWNER_SYSTEM, RESOURCE_INPUT, 0);
    IOConfigGPIO(HWDetectPinB, IOCFG_IPU);

    delayMicroseconds(10);  // allow configuration to settle

    // Check hardware revision
    if (IORead(HWDetectPinB)) {
        if (IORead(HWDetectPinA)) {
            hardwareRevision = FORTINIF4_REV_1;
        } else {
            hardwareRevision = FORTINIF4_REV_2;
        }
    } else {
        if (IORead(HWDetectPinA)) {
            hardwareRevision = FORTINIF4_REV_4;
        } else {
            hardwareRevision = FORTINIF4_REV_3;
        }
    }
}

void updateHardwareRevision(void)
{
}
