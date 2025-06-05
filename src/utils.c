#include "../include/ft_ping.h"
#include <sys/time.h>

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


long time_diff_ms(struct timeval *start, struct timeval *end)
{
	long seconds = end->tv_sec - start->tv_sec;
	long useconds = end->tv_usec - start->tv_usec;
	return (seconds * 1000) + (useconds / 1000);
}