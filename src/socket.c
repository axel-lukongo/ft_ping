#include "../include/ft_ping.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <errno.h>

int create_socket(void)
{
	int sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("ft_ping: socket");
		fprintf(stderr, "Did you run the program with sudo?\n");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}