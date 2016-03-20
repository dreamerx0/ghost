/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Ghost, a micro-kernel based operating system for the x86 architecture    *
 *  Copyright (C) 2015, Max SchlÃ¼ssel <lokoxe@gmail.com>                     *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation, either version 3 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GHOST_KERNQUERY__
#define __GHOST_KERNQUERY__

#include "ghost/common.h"
#include "ghost/fs.h"
#include "ghost/kernel.h"

__BEGIN_C

/**
 *
 */
typedef int g_kernquery_status;
static const g_kernquery_status G_KERNQUERY_STATUS_SUCCESSFUL = 0;
static const g_kernquery_status G_KERNQUERY_STATUS_UNKNOWN_ID = 1;

/**
 * Command IDs
 */
#define G_KERNQUERY_PCI_COUNT			0x500
#define G_KERNQUERY_PCI_GET				0x501

#define G_KERNQUERY_TASK_COUNT			0x600
#define G_KERNQUERY_TASK_GET_BY_POS		0x601
#define G_KERNQUERY_TASK_GET_BY_ID		0x601

/**
 * PCI
 */
typedef struct {
	uint32_t count;
}__attribute__((packed)) g_kernquery_pci_count_out;

typedef struct {
	uint32_t position;
}__attribute__((packed)) g_kernquery_pci_get_in;

typedef struct {
	uint8_t found;

	uint8_t slot;
	uint8_t bus;
	uint8_t function;

	uint16_t vendorId;
	uint16_t deviceId;

	uint8_t classCode;
	uint8_t subclassCode;
	uint8_t progIf;
}__attribute__((packed)) g_kernquery_pci_get_out;

/**
 * Processes / threads
 */
typedef struct {
	uint32_t count;
}__attribute__((packed)) g_kernquery_task_count_out;

typedef struct {
	uint32_t position;
}__attribute__((packed)) g_kernquery_task_get_by_pos_in;

typedef struct {
	g_tid id;
}__attribute__((packed)) g_kernquery_task_get_by_id_in;

typedef struct {
	uint8_t found;

	g_tid id;
	g_tid parent;
	g_thread_type type;
	char identifier[512];
	char source_path[G_PATH_MAX];

	g_virtual_address memory_used;
}__attribute__((packed)) g_kernquery_task_get_out;

__END_C

#endif