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
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SFO_HEADER_MAGIC_OFFSET              0x00
#define SFO_HEADER_MAGIC_SIZE                0x04
#define SFO_HEADER_VERSION_SIZE              0x04
#define SFO_HEADER_KEY_TABLE_START_SIZE      0x04
#define SFO_HEADER_DATA_TABLE_START_SIZE     0x04
#define SFO_HEADER_TABLES_ENTRIES_SIZE       0x04
#define SFO_HEADER_MAGIC_VALUE               0x46535000

#define SFO_INDEX_TABLE_START_OFFSET         0x14
#define SFO_INDEX_TABLE_KEY_OFFSET_SIZE      0x02
#define SFO_INDEX_TABLE_DATA_FMT_SIZE        0x02
#define SFO_INDEX_TABLE_DATA_LEN_SIZE        0x04
#define SFO_INDEX_TABLE_DATA_MAX_LEN_SIZE    0x04
#define SFO_INDEX_TABLE_DATA_OFFSET_SIZE     0x04

#define SFO_KEY_TABLE_KEY_MAX_SIZE           0x14

#define SFO_DATA_TABLE_DATA_MAX_SIZE         0xC60

#define SFO_DATA_TABLE_PARAM_UTF8            0x0204
#define SFO_DATA_TABLE_PARAM_UTF8S           0x0004
#define SFO_DATA_TABLE_PARAM_UINT32          0x0404
#define SFO_DATA_TABLE_PARAM_UINT32_MAX_SIZE 0x04

#define STATUS_SUCCESS                       0x00
#define STATUS_FAILURE                       -0x01

#define FILE_MODE_BINARY_READ                0x00
#define FILE_MODE_BINARY_WRITE               0x01
#define OUTPUT_FORMAT_STRING                 0x00
#define OUTPUT_FORMAT_JSON                   0x01

#endif
