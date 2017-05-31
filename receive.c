//Kacper Jędrzejewski 280045
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/select.h>
#include <netinet/ip.h>
int receive_one(int sockfd,int pid,int TTL,struct sockaddr_in *sender,socklen_t 	*sender_len){
		
	fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd, &descriptors);
	struct timeval tv; tv.tv_sec = 1; tv.tv_usec = 0;
	
	int ready = select (sockfd+1, &descriptors, NULL, NULL, &tv);				
	if(ready < 0) return -1;
		
	else if (ready == 0 ){return -2;}	
		
	else{ 
		u_int8_t buffer[IP_MAXPACKET];

		ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT,(struct sockaddr *)sender,sender_len);
		if (packet_len < 0 ) return -1;				

		struct iphdr* ip_header = (struct iphdr*) buffer;
       	u_int8_t* icmp_packet = buffer + 4 * ip_header->ihl;		
		struct icmphdr* icmp_headerRev = (struct icmphdr*) icmp_packet;
				
		if(icmp_headerRev->type == ICMP_TIME_EXCEEDED){
		
			struct iphdr* ip_header1 = (struct iphdr*)(icmp_packet + 8);
			u_int8_t* icmp_packet = (u_int8_t*)(ip_header1) + 4 * ip_header1->ihl;
			struct icmphdr* icmp_headerRev = (struct icmphdr*)icmp_packet;
			
				
			if(icmp_headerRev->un.echo.id==pid &&icmp_headerRev->un.echo.sequence==TTL){
		
				if (packet_len >= 0) {
						
					return 1;
				}
			}	
		}
		
		else if(icmp_headerRev->type == ICMP_ECHOREPLY && icmp_headerRev->un.echo.id==pid && icmp_headerRev->un.echo.sequence==TTL){
		
			if (packet_len >= 0) {
				return 1;			
			}		
		}	
	}
	return -1;
}

int receive(int sockfd,int pid,int TTL, int *reply,struct sockaddr_in *sender,socklen_t *sender_len){
	int TimeStart, TimeCurrent,TimeReply;
	TimeStart = clock();
	while(*reply < 3 ){
	 	int tmp = receive_one(sockfd,pid,TTL,sender,sender_len);
	 	TimeCurrent = clock();
		TimeReply = TimeCurrent - TimeStart;
		if (tmp == 1) *reply+= 1;
		if(tmp== -1) return -1;
		if(tmp== -2) *reply += 42;		
	}
	if (*reply == 3) return TimeReply/3;
	return 0;
}