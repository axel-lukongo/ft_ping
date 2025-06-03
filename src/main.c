
#include <stdio.h>
#include <string.h>

int parse_arguments(int argc, char **argv) {
    // Check if the correct number of arguments is provided
    if (argc == 2) {
        return 0;
    }
    if (strcmp(argv[2],"-v") == 0 && strcmp(argv[2], "-?") == 0) {
        printf("Usage: %s <filename> [optional_second_argument]\n", argv[0]);
        return 0;
    }
    // Process the filename argument
    const char *filename = argv[1];
    printf("Filename: %s\n", filename);

    // If a second argument is provided, print it
    if (argc == 3) {
        printf("Second argument: %s\n", argv[2]);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if (parse_arguments(argc, argv) != 0) {
        return 1;
    }

    // This is a simple C program that does nothing.
    return 0;
}