#include "../include/ft_ping.h"

void	print_usage(void)
{
	printf("Usage: ft_ping destination [-v] [-?]\n");
	printf("Options:\n");
	printf("  -v        : verbose output\n");
	printf("  -?        : display this help message\n");
	exit(EXIT_SUCCESS);
}

void	print_invalid_option(const char *opt)
{
	fprintf(stderr, "ft_ping: invalid option '%s'\n", opt);
	print_usage();
}
