#include "../include/ft_ping.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define PACKET_SIZE 64


t_stats g_stats;  // déclaration globale

void handle_sigint(int signum)
{
	(void)signum;
	double loss = 100.0 * (g_stats.sent - g_stats.received) / g_stats.sent;
	double avg = g_stats.received ? g_stats.rtt_total / g_stats.received : 0;

	printf("\n--- ft_ping statistics ---\n");
	printf("%d packets transmitted, %d received, %.1f%% packet loss\n",
		g_stats.sent, g_stats.received, loss);
	if (g_stats.received)
		printf("round-trip min/avg/max = %.3f/%.3f/%.3f ms\n",
			g_stats.rtt_min, avg, g_stats.rtt_max);
	exit(0);
}

void ping_loop(t_env *env, int sockfd, struct sockaddr_in *addr, const char *ip_str)
{
	int seq = 1;
	char packet[PACKET_SIZE];
	pid_t pid = getpid();

	signal(SIGINT, handle_sigint);  // Attrape Ctrl+C

	// Init stats
	g_stats.sent = 0;
	g_stats.received = 0;
	g_stats.rtt_min = __DBL_MAX__;
	g_stats.rtt_max = 0;
	g_stats.rtt_total = 0;
    (void)env;  
    if (env->verbose){
        printf("ai->ai_family: AF_INET, ai->ai_family: '%s'\n",env->target);
    }
	while (1)
	{
		struct timeval send_time;

		memset(packet, 0, PACKET_SIZE);
		build_icmp_packet(packet, seq, pid);
		gettimeofday(&send_time, NULL);

		if (sendto(sockfd, packet, PACKET_SIZE, 0,
			(struct sockaddr *)addr, sizeof(*addr)) >= 0)
		{
			g_stats.sent++;
		}
		else
		{
			perror("ft_ping: sendto");
		}

		if (receive_icmp_reply(sockfd, pid, seq, ip_str, &send_time, env->verbose) == 0)
		{
			struct timeval recv_time;
			gettimeofday(&recv_time, NULL);
			long rtt = time_diff_ms(&send_time, &recv_time);
			g_stats.received++;
			g_stats.rtt_total += rtt;
			if (rtt < g_stats.rtt_min) g_stats.rtt_min = rtt;
			if (rtt > g_stats.rtt_max) g_stats.rtt_max = rtt;
		}

		seq++;
		sleep(1);
	}
}