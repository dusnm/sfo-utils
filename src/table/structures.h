#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdint.h>
#include "../utils/constants.h"
#include "values.h"

struct _sfo_header
{
    uint32_t magic;            /* Always PSF */
    uint32_t version;          /* Usually 1.1 */
    uint32_t key_table_start;  /* Start offset of key table */
    uint32_t data_table_start; /* Start offset of data table */
    uint32_t tables_entries;   /* Number of all entries in all tables */
};

struct _sfo_index_table_entry
{
    uint16_t key_offset;   /* param key offset (relative to start offset of key_table */
    uint16_t data_fmt;     /* param_data offset data type */
    uint32_t data_len;     /* param_data used bytes */
    uint32_t data_max_len; /* param_data total bytes */
    uint32_t data_offset;  /* param_data offset (relative to start offset of data_table) */
};

struct _sfo_key_table_entry
{
    char key[KEY_MAX_SIZE]; /* key_entry. Number of entries is stored in the sfo_header */
};

struct _sfo_data_table_entry
{
    char data[DATA_MAX_SIZE]; /* data_entry. Maps onto a key entry. Number of entries is stored in the sfo_header */
};

typedef struct _sfo_header sfo_header_t;
typedef struct _sfo_index_table_entry sfo_index_table_entry_t;
typedef struct _sfo_key_table_entry sfo_key_table_entry_t;
typedef struct _sfo_data_table_entry sfo_data_table_entry_t;

#endif
