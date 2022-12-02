#ifndef VALUES_H
#define VALUES_H

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