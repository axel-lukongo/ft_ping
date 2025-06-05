#include "../include/ft_ping.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define PACKET_SIZE 64

void build_icmp_packet(char *packet, int seq, pid_t pid)
{
	memset(packet, 0, PACKET_SIZE);  // ← TRÈS important

	struct icmphdr *icmp = (struct icmphdr *)packet;

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = htons(pid & 0xFFFF);
	icmp->un.echo.sequence = htons(seq);
	icmp->checksum = 0;

	for (unsigned long i = 0; i < PACKET_SIZE - sizeof(struct icmphdr); i++)
		packet[sizeof(struct icmphdr) + i] = i;

	icmp->checksum = compute_checksum(packet, PACKET_SIZE);
}