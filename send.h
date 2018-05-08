//Kacper Jędrzejewski 280045
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
u_int16_t compute_icmp_checksum (const void *buff, int length);
int send_sock(int sockfd, int PID, int TTL,char* adres_ip);

int send_tree_socks(int sockfd,int PID,int TTL,char* adres_ip);