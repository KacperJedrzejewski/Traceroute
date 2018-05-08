//Kacper Jędrzejewski 280045
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool print(int reply,int TTL,int AvrTime,char* ip,struct sockaddr_in *sender);
