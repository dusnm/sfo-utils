#ifndef PARSE_H
#define PARSE_H

#include "../table/structures.h"

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
