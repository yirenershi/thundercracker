/* -*- mode: C; c-basic-offset: 4; intent-tabs-mode: nil -*-
 *
 * Sifteo prototype simulator
 * M. Elizabeth Scott <beth@sifteo.com>
 *
 * Copyright <c> 2011 Sifteo, Inc. All rights reserved.
 */

/*
 * XXX: Pick a specific flash memory model.
 *
 * Currently this is based on the SST39VF1681, but this likely isn't
 * what we'll actually be using in the final design.
 *
 * Our current requirements:
 *
 *  - NOR flash, 2Mx8 (16 megabits)
 *
 *  - Low power (Many memories have an automatic standby feature, which gives them
 *    fairly low power usage when we're clocking them slowly. Our actual clock rate
 *    will be 2.67 MHz peak.)
 *
 *  - Fast program times. The faster we can get the better, this will directly
 *    impact asset download times.
 *
 *  - Fast erase times. This is very important- we'd like to stream assets in the
 *    background, but during an erase we can't refresh the screen at all until the
 *    erase finishes. This is clearly very bad for interactivity, so flashes with
 *    erase times in the tens of milliseconds are much better than flashes that
 *    take half a second or longer to erase.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "flash.h"

/* Maximum flash size supported by our addressing scheme */
#define FLASH_SIZE   (1 << 21)
#define FLASH_MASK   (FLASH_SIZE - 1)

struct {
    FILE *file;
    uint8_t data[FLASH_SIZE];
    uint32_t prev_addr;
    uint32_t cycle_count;
} flash;

void flash_init(const char *filename)
{
    size_t result;

    flash.file = fopen(filename, "rb+");
    if (!flash.file) {
        flash.file = fopen(filename, "wb+");
    }
    if (!flash.file) {
	perror("Error opening flash");
	exit(1);
    }

    result =  fread(flash.data, 1, FLASH_SIZE, flash.file);
    if (result < 0) {
	perror("Error reading flash");
	exit(1);
    }	
}

void flash_exit(void)
{
    fclose(flash.file);
}

uint32_t flash_cycle_count(void)
{
    uint32_t c = flash.cycle_count;
    flash.cycle_count = 0;
    return c;
}

void flash_cycle(struct flash_pins *pins)
{
    if (pins->ce) {
	// Chip disabled
	pins->data_drv = 0;
	flash.prev_addr = -1;
	return;
    }

    if (pins->oe) {
	flash.prev_addr = -1;
    } else {
	// Read mode
	
	uint32_t addr = FLASH_MASK & pins->addr;

	pins->data_drv = 1;
	pins->data_out = flash.data[addr];

	if (addr != flash.prev_addr) {
	    // For power consumption accounting purposes, this counts as a read cycle.
	    flash.cycle_count++;
	    flash.prev_addr = addr;
	}
    }
}
