//Kacper Jędrzejewski 280045
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool print(int reply,int TTL,int AvrTime,char* ip,struct sockaddr_in *sender){
	if (reply>3) reply -= 42;
		if (reply == 3){
			
			char sender_ip_str[20]; 
			inet_ntop(AF_INET, &(sender->sin_addr), sender_ip_str, sizeof(sender_ip_str));
			printf ("%d %s    %dms\n",TTL, sender_ip_str,AvrTime);
			if(strcmp(sender_ip_str, ip)==0){	return true;}
		}
		else if (reply == 0)
		{	
			printf("%d * \n",TTL);
		}
		else
		{
			char sender_ip_str[20]; 
			inet_ntop(AF_INET, &(sender->sin_addr), sender_ip_str, sizeof(sender_ip_str));
			printf ("%d %s    ??\n",TTL, sender_ip_str);
			if(strcmp(sender_ip_str, ip)==0){	return true;}
		}
	return false;
	}
