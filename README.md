# sfo-utils

A program to handle working with Sony's PARAM.SFO metadata files.

# Usage

To see usage information run the program as follows:

```shell
sfo-utils -h
```

```
Copyright (C) 2021 Dusan Mitrovic <dusan@dusanmitrovic.xyz>
Licensed under the terms of the GNU GPL, version 3 or later

Usage: sfo-utils [option] [argument]

  -r <argument>,   Reads the supplied PARAM.SFO file and outputs it to stdout.
  -h,              Prints this help dialog.
```

## Example

```shell
sfo-utils -r /tmp/PARAM.SFO
```

```
CATEGORY: MS
PARENTAL_LEVEL: 9
SAVEDATA_DETAIL: Total Time: 01:28:49
Red Orbs: 82064 Health: 100 Magic: 100
Difficulty: Mortal (Easy)
SAVEDATA_DIRECTORY: UCES00842DATA04
SAVEDATA_FILE_LIST: SECURE
SAVEDATA_PARAMS: A
SAVEDATA_TITLE: Fields of Elysium
TITLE: God of War™: Chains of Olympus
```

# Licensing

This program is free software, licensed under the terms of the GNU General Public License, version 3 or later.
For details please refer to the LICENSE file included in the root of the project.
