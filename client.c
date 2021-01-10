#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(){

	//Simple UDP client
	
	int sock, len, t;
	struct sockaddr_in server, from;
	char buffer[256];

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		printf("Error creating socket \n");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5123);
	len = sizeof(struct sockaddr_in);

	while(sock){
		printf("Enter the message:  \n");
		scanf("%s", buffer);

		t = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, len);

		if(t < 0){
			printf("Error sending the message \n");
			exit(EXIT_FAILURE);
		}

		t = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&from, &len);
		
		if(t < 0){
			printf("Error receiving message \n");
		}

		printf("Responded: %s \n", buffer);

	}
			
	return 0xbeef;
}
