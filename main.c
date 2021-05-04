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
#include <limits.h>
#include <unistd.h>
#include "sforead.h"

/* Print the help dialog */
static void print_help()
{
    const char *help =
        "Copyright (C) 2021 Dusan Mitrovic <dusan@dusanmitrovic.xyz>\n"
        "Licensed under the terms of the GNU GPL, version 3 or later\n"
        "\n"
        "Usage: sfo-utils [option] [argument]\n"
        "\n"
        "  -r <file path>, Reads the supplied PARAM.SFO file and outputs it to stdout.\n"
        "  -j,             Formats the output as JSON instead of an unformatted string.\n"
        "  -h,             Prints this help dialog.\n";

    fprintf(stdout, "%s", help);
}

int main(int argc, char *argv[])
{
    FILE *sfo_file;
    int  option;
    int  file_mode;
    int  output_format = OUTPUT_FORMAT_STRING;

    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments, at least one is required. See -h for help.\n");
        exit(EXIT_FAILURE);
    }

    while ((option = getopt(argc, argv, "hr:j")) != -1)
    {
        char       path[PATH_MAX];
        char       *realpath_result;

        switch (option)
        {
        case 'h':
            print_help();
            exit(EXIT_SUCCESS);
        case 'r':
            file_mode = FILE_MODE_BINARY_READ;
            realpath_result = realpath(optarg, path);

            if (!realpath_result)
            {
                fprintf(stderr, "Incorrect file path given, make sure it's correct.\n");
                exit(EXIT_FAILURE);
            }

            sfo_file = fopen(path, "rb");

            if (NULL == sfo_file)
            {
                fprintf(stderr, "There was an error while opening the file. Make you sure that the file exists and that you have the required permissions.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'j':
            output_format = OUTPUT_FORMAT_JSON;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    switch (file_mode)
    {
    case FILE_MODE_BINARY_READ:
        sforead(sfo_file, output_format);
        break;
    case FILE_MODE_BINARY_WRITE:
        // TODO: Implement this
        break;
    default:
        fprintf(stderr, "No file supplied for reading or writing, aborting.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
