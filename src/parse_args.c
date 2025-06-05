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

void	parse_args(int argc, char **argv, t_env *env)
{
	if (argc < 2)
	{
		fprintf(stderr, "ft_ping: missing destination\n");
		print_usage();
	}

	env->target = argv[1];
	env->verbose = 0;

	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-v") == 0)
			env->verbose = 1;
		else if (strcmp(argv[i], "-?") == 0)
			print_usage();
		else
			print_invalid_option(argv[i]);
	}
}