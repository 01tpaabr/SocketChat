#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main () {
	struct sockaddr_in server;
	struct sockaddr_in from;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	int retVal, len;
	char buffer[256];

	if (sock < 0){
		printf("Error starting socket\n");
		exit(EXIT_FAILURE);
	}
	
		
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5123);
	len = sizeof(struct sockaddr_in);

	retVal = bind(sock, (struct sockaddr *)&server, sizeof(server));
	
	if(retVal < 0){
		printf("Error binding \n");
		exit(EXIT_FAILURE);
	}		
	
	int t;
	while(sock){
		t = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&from, &len);
		if(t < 0){
			printf("Error receiving\n");
			exit(EXIT_FAILURE);
		}
		
		printf("Received: %s \n", buffer);
		t = sendto(sock, "OK\n", 21, 0, (struct sockaddr *)&from, len);
		if(t < 0) {
			printf("Error sending message \n");
			exit(EXIT_FAILURE);
		}

	}

	return 0xbeef;
}
