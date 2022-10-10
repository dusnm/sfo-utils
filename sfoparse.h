/**
 * Reads Sony's PARAM.SFO files
 * Copyright (C) 2021 Dusan Mitrovic <dusan@dusanmitrovic.xyz>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef SFOPARSE_H
#define SFOPARSE_H

#include "structures.h"

/**
 * Parses sfo_header data from the binary file
 * with the given byte offsets and sizes.
 *
 * Returns the parsed header data as sfo_header_t
 */
sfo_header_t parse_sfo_header(FILE *sfo_file);

/**
 * Parses sfo_index_table entry from the binary file
 * with the given byte offsets and sizes
 */
void parse_sfo_index_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    sfo_index_table_entry_t sfo_index_table_entries[]);

/**
 * Parses sfo_key_table entry from the binary file
 */
read_status_t parse_sfo_key_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    uint32_t starting_offset,
    sfo_key_table_entry_t sfo_key_table_entries[]);

/**
 * Parses sfo_data_table entry from the binary file
 */
read_status_t parse_sfo_data_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    uint32_t starting_offset,
    sfo_index_table_entry_t sfo_index_table_entries[],
    sfo_data_table_entry_t sfo_data_table_entries[]);

#endif
