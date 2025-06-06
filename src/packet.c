#include "../include/ft_ping.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define PACKET_SIZE 64

/**
 * @brief This function builds an ICMP Echo Request packet.
 * It initializes the ICMP header fields, sets the ID and sequence number,
 * and computes the checksum for the packet.
 * 
 * @param packet The buffer to hold the ICMP packet.
 * @param seq The sequence number for the ICMP request.
 * @param pid The process ID used to identify the ICMP request.
 */
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