#include "../include/ft_ping.h"
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(int argc, char **argv)
{
	t_env env;
	struct sockaddr_in addr;
	char ip_str[INET_ADDRSTRLEN];
	int sockfd;

	parse_args(argc, argv, &env);
	resolve_host(env.target, &addr, ip_str);
	sockfd = create_socket();

	printf("PING %s (%s): 56 data bytes\n", env.target, ip_str);

	ping_loop(&env, sockfd, &addr, ip_str);

	close(sockfd);
	return 0;
}