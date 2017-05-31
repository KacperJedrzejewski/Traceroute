//Kacper Jędrzejewski 280045
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

int send_sock(int sockfd, int PID, int TTL,char* adres_ip){
	struct icmphdr icmp_header;
	icmp_header.type = ICMP_ECHO;
	icmp_header.code = 0;
	icmp_header.un.echo.id = PID;
	icmp_header.un.echo.sequence = TTL;
	icmp_header.checksum = 0;
	icmp_header.checksum = compute_icmp_checksum ((u_int16_t*)&icmp_header, sizeof(icmp_header));
	
	struct sockaddr_in recipient;
	//bzero (&recipient, sizeof(recipient)); 
	recipient.sin_family = AF_INET;
	inet_pton(AF_INET, adres_ip, &recipient.sin_addr);
   	setsockopt (sockfd, IPPROTO_IP, IP_TTL, &TTL, sizeof(int));
	
	ssize_t bytes_sent = sendto (sockfd, &icmp_header, sizeof(icmp_header), 0, (struct sockaddr*)&recipient, sizeof(recipient));
	
	if(bytes_sent < 0){		
		return -1;
		}
	return 0;
}

int send_tree_socks(int sockfd,int PID,int TTL,char* adres_ip){
	for(int i = 0; i < 3; i++){
		if(send_sock(sockfd,PID,TTL,adres_ip) == -1) return -1;
	}
	return 0;
}