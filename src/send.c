#include "../include/ft_ping.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <math.h>

#define PACKET_SIZE 64


t_stats g_stats;  // déclaration globale

/**
 * @brief this function calculates the mean deviation (mdev) of the RTTs.
 * It computes the average RTT and then calculates the average of the absolute
 * differences between each RTT and the average.
 * 
 * @return double the mean deviation of the RTTs.
 */
double calculate_mdev(void) 
{
    double sum = 0;
    double avg = g_stats.rtt_total / g_stats.sent;
    
    for (int i = 0; i < g_stats.sent; i++) {
        sum += fabs(g_stats.rtts[i] - avg);
    }
    return sum / g_stats.sent;
}

/**
 * @brief this function handles the Ctrl+C signal (SIGINT).
 * It calculates the packet loss percentage, average round-trip time (RTT),
 * and the mean deviation (mdev) of the RTTs.
 * It then prints the statistics and exits the program.
 * 
 * 
 * @param signum 
 */
void handle_sigint(int signum)
{
	(void)signum;
	double loss = 100.0 * (g_stats.sent - g_stats.received) / g_stats.sent;
	double avg = g_stats.received ? g_stats.rtt_total / g_stats.received : 0;
    double mdev = g_stats.received ? calculate_mdev() : 0;
    // (void)mdev;
	printf("\n--- ft_ping statistics ---\n");
	printf("%d packets transmitted, %d received, %.1f%% packet loss\n",
		g_stats.sent, g_stats.received, loss);
	if (g_stats.received)
		printf("round-trip min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
			g_stats.rtt_min, avg, g_stats.rtt_max, mdev);
	exit(0);
}

/**
 * @brief this function is the main loop of the ping program.
 * It sends ICMP echo requests to the target IP address and waits for replies.
 * It calculates the round-trip time (RTT) for each reply and updates the statistics.
 * It handles the Ctrl+C signal to gracefully exit and display the statistics.
 * It uses a raw socket to send and receive ICMP packets.
 * 
 * @param env describes the environment, including the target IP and verbosity level.
 * @param sockfd socket file descriptor for the raw socket.
 * @param addr pointer to the sockaddr_in structure containing the target IP address.
 * @param ip_str input string representation of the target IP address.
 */
void ping_loop(t_env *env, int sockfd, struct sockaddr_in *addr, const char *ip_str)
{
	int seq = 1;
	char packet[PACKET_SIZE];
	pid_t pid = getpid();

	signal(SIGINT, handle_sigint);  // handle the Ctrl+C

	// Init stats
	g_stats.sent = 0;
	g_stats.received = 0;
	g_stats.rtt_min = __DBL_MAX__;
	g_stats.rtt_max = 0;
	g_stats.rtt_total = 0;

    // Allocat tab rtts
    g_stats.rtts = malloc(sizeof(double) * 1000); 
    if (!g_stats.rtts) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

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
            g_stats.rtts[g_stats.sent - 1] = rtt;  // -1 car sent est déjà incrémenté
			g_stats.received++;
			g_stats.rtt_total += rtt;
			if (rtt < g_stats.rtt_min) g_stats.rtt_min = rtt;
			if (rtt > g_stats.rtt_max) g_stats.rtt_max = rtt;
		}

		seq++;
		sleep(1);
	}
}