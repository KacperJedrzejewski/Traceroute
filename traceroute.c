//Kacper Jędrzejewski 280045
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include "send.h"
#include "receive.h"
#include "print.h"
#include <unistd.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Invalid input: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
		
	}

	int TTL = 1;
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int pid = getpid();
	
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}
	for (TTL = 1; TTL < 31; TTL++){
		//wysylanie
		if(send_tree_socks(sockfd, pid,TTL,argv[1]) == -1) {
			fprintf(stderr, "send error: %s\n", strerror(errno)); 
			return EXIT_FAILURE;
		}

		struct sockaddr_in 	sender;	
		socklen_t 			sender_len = sizeof(sender);
		
		int reply = 0;
		//odbieranie
		int AvrTime = receive(sockfd,pid,TTL,&reply,&sender,&sender_len);
		if(AvrTime == -1){
		 fprintf(stderr, "receive error: %s\n", strerror(errno)); 
			return EXIT_FAILURE;
		}

		//wypisywanie
		if(print(reply,TTL,AvrTime,argv[1],&sender)) TTL = 42;
		
	}
	close(sockfd);
	return 0;
}
