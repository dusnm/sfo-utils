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
#include "sforead.h"

/* Print the parsed data */
static void print_result(
    uint32_t               number_of_entries,
    sfo_key_table_entry_t  sfo_key_table_entries[],
    sfo_data_table_entry_t sfo_data_table_entries[]
)
{
    for (int i = 0; i < number_of_entries; i++)
    {
        fprintf(
            stdout,
            "%s: %s\n",
            sfo_key_table_entries[i].key,
            sfo_data_table_entries[i].data
        );
    }
}

void sforead(FILE *sfo_file)
{
    sfo_header_t sfo_header;

    sfo_header = parse_sfo_header(sfo_file);

    if (SFO_HEADER_MAGIC_VALUE != sfo_header.magic)
    {
        fclose(sfo_file);
        fprintf(stderr, "The file doesn't appear to be an SFO file or is corrupted.\n");

        exit(EXIT_FAILURE);
    }

    uint32_t tables_entries   = sfo_header.tables_entries;
    uint32_t key_table_start  = sfo_header.key_table_start;
    uint32_t data_table_start = sfo_header.data_table_start;

    sfo_index_table_entry_t sfo_index_table_entries[tables_entries];
    sfo_key_table_entry_t   sfo_key_table_entries[tables_entries];
    sfo_data_table_entry_t  sfo_data_table_entries[tables_entries];

    parse_sfo_index_table_entries(
        sfo_file,
        tables_entries,
        sfo_index_table_entries
    );

    int key_table_status = parse_sfo_key_table_entries(
        sfo_file,
        tables_entries,
        key_table_start,
        sfo_key_table_entries
    );

    int data_table_status = parse_sfo_data_table_entries(
        sfo_file,
        tables_entries,
        data_table_start,
        sfo_index_table_entries,
        sfo_data_table_entries
    );

    fclose(sfo_file);

    if (
            STATUS_SUCCESS != key_table_status ||
            STATUS_SUCCESS != data_table_status
       )
    {
        fprintf(stderr, "There was an error reading the file.\n");

        exit(EXIT_FAILURE);
    }

    print_result(
        tables_entries,
        sfo_key_table_entries,
        sfo_data_table_entries
    );
}
