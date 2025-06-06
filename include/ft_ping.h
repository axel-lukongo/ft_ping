#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <stdint.h>

#define EAGAIN 11 /* Try again */
#define EWOULDBLOCK EAGAIN /* Operation would block */

typedef struct s_env {
	char	*target;
	int		verbose;
}	t_env;

// i defined header ICMP 
struct icmphdr {
	uint8_t type;       // 8 = Echo Request, 0 = Echo Reply
	uint8_t code;       // généralement 0
	uint16_t checksum;
	union {
		struct {
			uint16_t id;
			uint16_t sequence;
		} echo;
		uint32_t gateway;
		struct {
			uint16_t unused;
			uint16_t mtu;
		} frag;
	} un;
    
};

typedef struct s_stats {
	int sent;
	int received;
	double rtt_min;
	double rtt_max;
	double rtt_total;
    double rtt_mdev;    
    double *rtts;       
}	t_stats;

extern t_stats g_stats; 

void	    parse_args(int argc, char **argv, t_env *env);
void	    print_usage(void);
void	    print_invalid_option(const char *opt);
void        resolve_host(const char *target, struct sockaddr_in *addr, char *ip_str);
int         create_socket(void);
void        build_icmp_packet(char *packet, int seq, pid_t pid);
uint16_t    compute_checksum(void *data, int len);
// int         receive_icmp_reply(int sockfd, pid_t pid, int seq, const char *ip_str, struct timeval *send_time);
long        time_diff_ms(struct timeval *start, struct timeval *end);
void        ping_loop(t_env *env, int sockfd, struct sockaddr_in *addr, const char *ip_str);
int         receive_icmp_reply(int sockfd, pid_t pid, int seq, const char *ip_str, struct timeval *send_time, int verbose);
#endif