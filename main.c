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
        "  -r <argument>,   Reads the supplied PARAM.sfo file and outputs it to stdout.\n"
        "  -h,              Prints this help dialog.\n";

    fprintf(stdout, "%s", help);
}

int main(int argc, char *argv[])
{
    int          option;
    FILE         *sfo_file;

    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments, at least one is required. See -h for help.\n");

        exit(EXIT_FAILURE);
    }

    while ((option = getopt(argc, argv, "rh:")) != -1)
    {
        char       path[PATH_MAX];
        char       *realpath_result;
        const char *path_argument_value = argv[2];

        switch (option)
        {
        case 'r':
            realpath_result = realpath(path_argument_value, path);

            if (!realpath_result)
            {
                fprintf(stderr, "Incorrect file path given, make sure it's correct.\n");

                exit(EXIT_FAILURE);
            }

            sfo_file = fopen(path, "rb");

            if (NULL == sfo_file)
            {
                fprintf(stderr, "There was an error reading the file.\n");

                exit(EXIT_FAILURE);
            }

            sforead(sfo_file);

            exit(EXIT_SUCCESS);
        case 'h':
            print_help();

            exit(EXIT_SUCCESS);
        default:
            fprintf(stderr, "Incorrect argument provided, for help use -h.\n");

            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
