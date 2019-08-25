#include<iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define PORT 8080
#define MAX_QUEUE 5

void sort(int num[], int n) {
	
	int t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1-i; j++) {
			if (num[j] > num[j+1]) {
				t = num[j];
				num[j] = num[j+1];
				num[j+1] = t;
			}
		}
	}
}

int main() {
	
	struct sockaddr_in serv_address, client_address;
	socklen_t client_len;

	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		cout << "Error creating socket" << endl;
		return 0;
	}

	cout << "Socket created" << endl;

	bzero((char *) &serv_address, sizeof(serv_address));

	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(PORT);

	int code = bind(socketfd, (struct sockaddr* ) &serv_address, sizeof(serv_address));
	if (code < 0) {
		cout << "Error binding the socket" << endl;	
	}
	cout << "Socket binded" << endl;

	listen(socketfd, MAX_QUEUE);
	
	client_len = sizeof(client_address);
	int new_socket_fd = accept(socketfd, (struct sockaddr*) &client_address, &client_len);
	if (new_socket_fd < 0) {
		cout << "Error accepting a socket" << endl;	
	}
	cout << "Socket accepted" << endl;

	int  numbers[10];

	while (recv(new_socket_fd, &numbers, 10 * sizeof(int), 0) > 0) {
		sort(numbers, 10);
		write(new_socket_fd, &numbers, 10 * sizeof(int));
	}
	
}	
