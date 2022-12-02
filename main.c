#include <limits.h>
#include <unistd.h>
#include "src/read/read.h"

static void print_help()
{
    const char *help =
        "Copyright (C) 2021 Dusan Mitrovic <dusan@dusanmitrovic.xyz>\n"
        "Licensed under the terms of the GNU GPL, version 3 or later\n"
        "\n"
        "Usage: sfo-utils [option] [argument]\n"
        "\n"
        "  -r <file path>, Reads the supplied PARAM.SFO file and outputs it to stdout.\n"
        "  -h,             Prints this help dialog.\n";

    fprintf(stdout, "%s", help);
}

int main(int argc, char *argv[])
{
    FILE *sfo_file;
    int option;

    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments, at least one is required. See -h for help.\n");
        exit(EXIT_FAILURE);
    }

    while ((option = getopt(argc, argv, "hr:")) != -1)
    {
        char path[PATH_MAX];
        char *realpath_result;

        switch (option)
        {
        case 'h':
            print_help();
            exit(EXIT_SUCCESS);
        case 'r':
            realpath_result = realpath(optarg, path);

            if (!realpath_result)
            {
                fprintf(stderr, "Incorrect file path given, make sure it's correct.\n");
                exit(EXIT_FAILURE);
            }

            sfo_file = fopen(path, "rb");

            if (NULL == sfo_file)
            {
                fprintf(stderr, "Failed to open file. Make sure that it exists and that you have proper permissions.\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    sforead(sfo_file);

    return EXIT_SUCCESS;
}