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
#ifndef TABLEVALUES_H
#define TABLEVALUES_H

enum _HEADER_VALUES
{
    HEADER_MAGIC_OFFSET = 0x00,
    HEADER_MAGIC_SIZE = 0x04,
    HEADER_MAGIC_VALUE = 0x46535000,
    HEADER_VERSION_SIZE = 0x04,
    HEADER_KEY_START_SIZE = 0x04,
    HEADER_DATA_START_SIZE = 0x04,
    HEADER_ENTRIES_SIZE = 0x04,
};

enum _INDEX_VALUES
{
    INDEX_START_OFFSET = 0x14,
    INDEX_KEY_OFFSET_SIZE = 0x02,
    INDEX_DATA_FMT_SIZE = 0x02,
    INDEX_DATA_LEN_SIZE = 0x04,
    INDEX_DATA_MAX_LEN_SIZE = 0x04,
    INDEX_DATA_OFFSET_SIZE = 0x04,
};

enum _KEY_VALUES
{
    KEY_MAX_SIZE = 0x14,
};

enum _DATA_VALUES
{
    DATA_MAX_SIZE = 0xC60,
    DATA_PARAM_UTF8 = 0x0204,
    DATA_PARAM_UTF8S = 0x0004,
    DATA_PARAM_UINT32 = 0x0404,
    DATA_PARAM_UINT32_MAX_SIZE = 0x04,
};

#endif