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
void resolve_host(const char *target, struct sockaddr_in *addr, char *ip_str)
{
	struct addrinfo hints;
	struct addrinfo *result;
	int ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;        
	hints.ai_socktype = SOCK_RAW;     
	hints.ai_protocol = IPPROTO_ICMP; 

    // We use this function to resolve the hostname to an IP address.
	ret = getaddrinfo(target, NULL, &hints, &result);
	if (ret != 0)
	{
		fprintf(stderr, "ft_ping: unknown host '%s'\n", target);
		exit(EXIT_FAILURE);
	}

	// We extract the ip address from the result
	struct sockaddr_in *res_addr = (struct sockaddr_in *)result->ai_addr;

	// On copie l'adresse dans la structure fournie
	memcpy(addr, res_addr, sizeof(struct sockaddr_in));

	// On convertit l'adresse en string lisible (ex: "8.8.8.8")
	if (inet_ntop(AF_INET, &(res_addr->sin_addr), ip_str, INET_ADDRSTRLEN) == NULL)
	{
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(result);
}