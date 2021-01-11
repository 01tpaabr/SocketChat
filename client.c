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
	char s_address[20];
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	printf("Enter server IP: \n");
	scanf("%[^\n]s", s_address);

	if(sock < 0){
		printf("Error creating socket \n");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(s_address);
	server.sin_port = htons(5123);
	len = sizeof(struct sockaddr_in);
	int end = 0;

	while(sock){
		printf("Enter the message:  \n");
		memset(buffer, 0, sizeof(buffer));
		if(fgets(buffer, sizeof(buffer), stdin)){
			buffer[strcspn(buffer, "\n")] = '\0';
		
			if(strcmp("Bye!", buffer) == 0){
				end = 1;
			}

			memset(buffer, 0, sizeof(buffer));	
			t = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, len);

			if(t < 0){
				printf("Error sending the message \n");
				exit(EXIT_FAILURE);
			}

			if(end){
				return 0xb100d;
			}
		}
		
		memset(buffer, 0, sizeof(buffer));
		t = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&from, &len);
		
		if(t < 0){
			printf("Error receiving message \n");
		}

		printf("Responded: %s \n", buffer);

	}
			
	return 0xbeef;
}
