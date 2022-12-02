#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include <getopt.h>
#include "cmd.h"
#include "../read/read.h"

void help_command()
{
    const char *help =
        "Copyright (C) 2022 Dusan Mitrovic <dusan@dusanmitrovic.xyz>\n"
        "Licensed under the terms of the GNU GPL, version 3 or later\n"
        "\n"
        "Usage: sfo-utils [option] [argument]\n"
        "\n"
        "  --read, -r <file path>, Reads the supplied PARAM.SFO file and outputs it to stdout.\n"
        "  --help, -h,             Prints this help dialog.\n";

    fprintf(stdout, "%s", help);
}

void read_command(char *optarg)
{
    FILE *sfo_file;
    char path[PATH_MAX];
    char *realpath_result;

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

    sforead(sfo_file);
}

void run_commands(int argc, char *argv[])
{
    int option = 0;
    int option_index = 0;
    struct option options[] =
        {{"help", no_argument, 0, 'h'},
         {"read", required_argument, 0, 'r'},
         {0, 0, 0, 0}};

    while ((option = getopt_long(argc, argv, "hr:", options, &option_index)) != -1)
    {
        switch (option)
        {
        case 'h':
            help_command();
            break;
        case 'r':
            read_command(optarg);
            break;
        default:
            break;
        }
    }
}