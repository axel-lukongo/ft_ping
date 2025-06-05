#include "../include/ft_ping.h"
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024
int receive_icmp_reply(int sockfd, pid_t pid, int seq, const char *ip_str, struct timeval *send_time, int verbose)
{
	char buffer[BUFFER_SIZE];
	struct sockaddr_in sender;
	socklen_t addrlen = sizeof(sender);
	struct timeval recv_time;

	ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
		(struct sockaddr *)&sender, &addrlen);

	if (received < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			if (verbose)
				fprintf(stderr, "[VERBOSE] Timeout waiting for reply (icmp_seq=%d)\n", seq);
			return -1;
		}
		perror("ft_ping: recvfrom");
		return -1;
	}

	gettimeofday(&recv_time, NULL);

	struct ip *ip_hdr = (struct ip *)buffer;
	int ip_header_len = ip_hdr->ip_hl * 4;
	struct icmphdr *icmp = (struct icmphdr *)(buffer + ip_header_len);

	if (verbose)
	{
		printf("[VERBOSE] ICMP type=%d code=%d ident=%d seq=%d ttl=%d\n",
			icmp->type,
			icmp->code,
			ntohs(icmp->un.echo.id),
			ntohs(icmp->un.echo.sequence),
			ip_hdr->ip_ttl);
	}

	if (icmp->type == ICMP_ECHOREPLY && ntohs(icmp->un.echo.id) == (pid & 0xFFFF))
	{
		long rtt = time_diff_ms(send_time, &recv_time);
		printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
			received - ip_header_len, ip_str, seq,
			ip_hdr->ip_ttl, (double)rtt);
		return 0;
	}
	return -1;
}