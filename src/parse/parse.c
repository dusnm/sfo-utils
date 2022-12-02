#include "../table/values.h"
#include "parse.h"

sfo_header_t parse_sfo_header(FILE *sfo_file)
{
    sfo_header_t sfo_header;

    /* Make sure the file pointer is at the correct starting offset */
    fseek(sfo_file, HEADER_MAGIC_OFFSET, SEEK_SET);

    fread(&sfo_header.magic, HEADER_MAGIC_SIZE, 1, sfo_file);
    fread(&sfo_header.version, HEADER_VERSION_SIZE, 1, sfo_file);
    fread(&sfo_header.key_table_start, HEADER_KEY_START_SIZE, 1, sfo_file);
    fread(&sfo_header.data_table_start, HEADER_DATA_START_SIZE, 1, sfo_file);
    fread(&sfo_header.tables_entries, HEADER_ENTRIES_SIZE, 1, sfo_file);

    return sfo_header;
}

void parse_sfo_index_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    sfo_index_table_entry_t sfo_index_table_entries[])
{
    /* Move the pointer to the beginning of the index_table */
    fseek(sfo_file, INDEX_START_OFFSET, SEEK_SET);

    for (uint32_t i = 0; i < number_of_entries; i++)
    {
        fread(&sfo_index_table_entries[i].key_offset, INDEX_KEY_OFFSET_SIZE, 1, sfo_file);
        fread(&sfo_index_table_entries[i].data_fmt, INDEX_DATA_FMT_SIZE, 1, sfo_file);
        fread(&sfo_index_table_entries[i].data_len, INDEX_DATA_LEN_SIZE, 1, sfo_file);
        fread(&sfo_index_table_entries[i].data_max_len, INDEX_DATA_MAX_LEN_SIZE, 1, sfo_file);
        fread(&sfo_index_table_entries[i].data_offset, INDEX_DATA_OFFSET_SIZE, 1, sfo_file);
    }
}

read_status_t parse_sfo_key_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    uint32_t starting_offset,
    sfo_key_table_entry_t sfo_key_table_entries[])
{
    read_status_t status = READ_FAILURE;
    /* Move the file pointer to the beginning of key_table */
    fseek(sfo_file, starting_offset, SEEK_SET);

    for (uint32_t i = 0; i < number_of_entries; i++)
    {
        int j = 0;
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
                return status;
            }

            sfo_key_table_entries[i].key[j++] = ch;
        } while ('\0' != ch && j < KEY_MAX_SIZE - 1);
    }

    status = READ_SUCCESS;

    return status;
}

read_status_t parse_sfo_data_table_entries(
    FILE *sfo_file,
    uint32_t number_of_entries,
    uint32_t starting_offset,
    sfo_index_table_entry_t sfo_index_table_entries[],
    sfo_data_table_entry_t sfo_data_table_entries[])
{
    read_status_t status = READ_FAILURE;

    for (uint32_t i = 0; i < number_of_entries; i++)
    {
        uint16_t data_fmt = sfo_index_table_entries[i].data_fmt;
        uint32_t data_len = sfo_index_table_entries[i].data_len;
        uint32_t data_offset = sfo_index_table_entries[i].data_offset;
        uint32_t uint32_data = 0;

        /* Move the file pointer to the next entry in the data table */
        fseek(sfo_file, starting_offset, SEEK_SET);
        fseek(sfo_file, data_offset, SEEK_CUR);

        switch (data_fmt)
        {
        case DATA_PARAM_UTF8:
            /* The data are null terminated UTF-8 encoded strings */
            if (DATA_MAX_SIZE < data_len)
            {
                /* Not enough space in the buffer to read the incoming data */
                return status;
            }

            fread(sfo_data_table_entries[i].data, data_len, 1, sfo_file);
            break;
        case DATA_PARAM_UTF8S:
            /* The data are a special type of UTF-8 strings that are not null terminated */
            if (DATA_MAX_SIZE < data_len)
            {
                /* Not enough space in the buffer to read the incoming data */
                return status;
            }

            fread(sfo_data_table_entries[i].data, data_len, 1, sfo_file);
            break;
        case DATA_PARAM_UINT32:
            /* The data are 32 bit unsingned integers, always exactly 4 bytes long */
            if (DATA_PARAM_UINT32_MAX_SIZE != data_len)
            {
                /* Something went wrong, the data that we're about to read isn't exactly 4 bytes long */
                return status;
            }

            fread(&uint32_data, data_len, 1, sfo_file);
            sprintf(sfo_data_table_entries[i].data, "%u", uint32_data);
            break;
        default:
            /* There was obviously some kind of an error in this case so we'll just fail and bail */
            return status;
        }
    }

    status = READ_SUCCESS;

    return status;
}
