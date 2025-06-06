#include "../include/ft_ping.h"

/**
 * @brief This function resolves the hostname to an IP address.
 * It uses getaddrinfo to resolve the target hostname and fills the provided
 * sockaddr_in structure with the resolved address.
 * 
 * @param target The hostname to resolve.
 * @param addr The sockaddr_in structure to fill with the resolved address.
 * @param ip_str A string buffer to hold the resolved IP address in human-readable form.
 */
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