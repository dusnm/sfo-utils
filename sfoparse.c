/**
 * Reads Sony's PARAM.SFO files
 * Copyright (C) 2021 Dusan Mitrovic <dusan@dusanmitrovic.xyz> This program is free software: you can redistribute it and/or modify
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
#include "sfoparse.h"

sfo_header_t parse_sfo_header(FILE *sfo_file)
{
    sfo_header_t sfo_header;

    /* Make sure the file pointer is at the correct starting offset */
    fseek(sfo_file, SFO_HEADER_MAGIC_OFFSET, SEEK_SET);

    fread(&sfo_header.magic,            SFO_HEADER_MAGIC_SIZE,            1, sfo_file);
    fread(&sfo_header.version,          SFO_HEADER_VERSION_SIZE,          1, sfo_file);
    fread(&sfo_header.key_table_start,  SFO_HEADER_KEY_TABLE_START_SIZE,  1, sfo_file);
    fread(&sfo_header.data_table_start, SFO_HEADER_DATA_TABLE_START_SIZE, 1, sfo_file);
    fread(&sfo_header.tables_entries,   SFO_HEADER_TABLES_ENTRIES_SIZE,   1, sfo_file);

    return sfo_header;
}

void parse_sfo_index_table_entries(
    FILE                    *sfo_file,
    uint32_t                number_of_entries,
    sfo_index_table_entry_t sfo_index_table_entries[]
)
{
    /* Move the pointer to the beginning of the index_table */
    fseek(sfo_file, SFO_INDEX_TABLE_START_OFFSET, SEEK_SET);

    for (int i = 0; i < number_of_entries; i++)
    {
        fread(&sfo_index_table_entries[i].key_offset,   SFO_INDEX_TABLE_KEY_OFFSET_SIZE,   1, sfo_file);
        fread(&sfo_index_table_entries[i].data_fmt,     SFO_INDEX_TABLE_DATA_FMT_SIZE,     1, sfo_file);
        fread(&sfo_index_table_entries[i].data_len,     SFO_INDEX_TABLE_DATA_LEN_SIZE,     1, sfo_file);
        fread(&sfo_index_table_entries[i].data_max_len, SFO_INDEX_TABLE_DATA_MAX_LEN_SIZE, 1, sfo_file);
        fread(&sfo_index_table_entries[i].data_offset,  SFO_INDEX_TABLE_DATA_OFFSET_SIZE,  1, sfo_file);
    }
}

int parse_sfo_key_table_entries(
    FILE                    *sfo_file,
    uint32_t                number_of_entries,
    uint32_t                starting_offset,
    sfo_key_table_entry_t   sfo_key_table_entries[]
)
{
    /* Move the file pointer to the beginning of key_table */
    fseek(sfo_file, starting_offset, SEEK_SET);

    for (int i = 0; i < number_of_entries; i++)
    {
        int  j = 0;
        char ch;

        /* The keys are null terminated strings,
         * just read them character by character into a buffer
         * while making sure not to overflow it
         */
        do
        {
            ch = fgetc(sfo_file);

            /* To avoid potential issues, if we're somehow at the end of file break the loop and return */
            if (EOF == ch)
            {
                return STATUS_FAILURE;
            }

            sfo_key_table_entries[i].key[j++] = ch;
        }
        while ('\0' != ch && j < SFO_KEY_TABLE_KEY_MAX_SIZE - 1);
    }

    return STATUS_SUCCESS;
}

int parse_sfo_data_table_entries(
    FILE                    *sfo_file,
    uint32_t                number_of_entries,
    uint32_t                starting_offset,
    sfo_index_table_entry_t sfo_index_table_entries[],
    sfo_data_table_entry_t  sfo_data_table_entries[]
)
{
    for (int i = 0; i < number_of_entries; i++)
    {
        uint16_t data_fmt = sfo_index_table_entries[i].data_fmt;
        uint32_t data_len = sfo_index_table_entries[i].data_len;
        uint32_t data_offset = sfo_index_table_entries[i].data_offset;
        uint32_t uint32_data = 0;

        /* Move the file pointer to the next entry in the data table */
        fseek(sfo_file, starting_offset, SEEK_SET);
        fseek(sfo_file, data_offset,     SEEK_CUR);

        switch (data_fmt)
        {
        case SFO_DATA_TABLE_PARAM_UTF8:
            /* The data are null terminated UTF-8 encoded strings */
            if (SFO_DATA_TABLE_DATA_MAX_SIZE < data_len)
            {
                /* Not enough space in the buffer to read the incoming data */
                return STATUS_FAILURE;
            }

            fread(sfo_data_table_entries[i].data, data_len, 1, sfo_file);
            break;
        case SFO_DATA_TABLE_PARAM_UTF8S:
            /* The data are a special type of UTF-8 strings that are not null terminated */
            if (SFO_DATA_TABLE_DATA_MAX_SIZE < data_len)
            {
                /* Not enough space in the buffer to read the incoming data */
                return STATUS_FAILURE;
            }

            fread(sfo_data_table_entries[i].data, data_len, 1, sfo_file);
            break;
        case SFO_DATA_TABLE_PARAM_UINT32:
            /* The data are 32 bit unsingned integers, always exactly 4 bytes long */
            if (SFO_DATA_TABLE_PARAM_UINT32_MAX_SIZE != data_len)
            {
                /* Something went wrong, the data that we're about to read isn't exactly 4 bytes long */
                return STATUS_FAILURE;
            }

            fread(&uint32_data, data_len, 1, sfo_file);
            sprintf(sfo_data_table_entries[i].data, "%u", uint32_data);
            break;
        default:
            /* There was obviously some kind of an error in this case so we'll just fail and bail */
            return STATUS_FAILURE;
        }
    }

    return STATUS_SUCCESS;
}
