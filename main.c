#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "src/cmd/cmd.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments, at least one is required.\n\n");
        help_command();

        exit(EXIT_FAILURE);
    }

    run_commands(argc, argv);

    return EXIT_SUCCESS;
}