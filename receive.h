//Kacper Jędrzejewski 280045
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/select.h>
#include <netinet/ip.h>
int receive_one(int sockfd, int pid,int TTL,int TimeReply,struct sockaddr_in *sender,socklen_t 	*sender_len);

int receive(int sockfd,int pid,int TTL, int *reply,struct sockaddr_in *sender,socklen_t *sender_len);