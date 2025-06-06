#include "../include/ft_ping.h"
#include <sys/time.h>


/**
 * @brief Compute the checksum for the ICMP packet.
 * checksum is a value used to verify the integrity of the data in the packet.
 * It is calculated by summing all 16-bit words in the packet and then taking the one's complement of the sum.
 * @param data 
 * @param len 
 * @return uint16_t 
 */
uint16_t compute_checksum(void *data, int len)
{
	uint32_t sum = 0;
	uint16_t *ptr = data;

	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}

	if (len == 1)
		sum += *(uint8_t *)ptr;

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);

	return ~sum;
}

/**
 * @brief Calculate the time difference in milliseconds between two timeval structures.
 * This function computes the difference between two timeval structures and returns the result in milliseconds.
 * @param start Pointer to the starting timeval structure.
 * @param end Pointer to the ending timeval structure.
 * @return long The time difference in milliseconds.
 */
long time_diff_ms(struct timeval *start, struct timeval *end)
{
	long seconds = end->tv_sec - start->tv_sec;
	long useconds = end->tv_usec - start->tv_usec;
	return (seconds * 1000) + (useconds / 1000);
}