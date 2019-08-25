#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <strings.h>

using namespace std;

int main(int argc, char *argv[]) {

	struct sockaddr_in serv_address;
	int socket_fd, portno;
	
	// Utility node to get host address
	struct hostent *server;
	
	// Get the port number from the argument
	portno = atoi(argv[2]);

	socket_fd = socket(AF_INET,SOCK_STREAM, 0);
	if (socket_fd < 0) {
		cout << "Error creating a socket" << endl;	
	}
	
	// Setting server credentials
	bzero((char *) &serv_address, sizeof(serv_address));
	serv_address.sin_family = AF_INET;
	serv_address.sin_port = htons(portno);
	
	// Setting the server address from IP
	if(inet_pton(AF_INET, argv[1], &serv_address.sin_addr) <= 0)   { 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
    	} 

	if (connect(socket_fd, (struct sockaddr*) &serv_address, sizeof(serv_address)) < 0)
  		cout << "Error connecting to server" << endl;

	int buffer[10] = {0};
	for (int i = 0; i < 10; i++)
		cin >> buffer[i];

	int code = send(socket_fd, buffer, 10 * sizeof(int), 0);
	if (code < 0)
    		cout << "ERROR reading from socket" << endl;

	int response[10];
	code = recv(socket_fd, &response, 10 * sizeof(int), 0);
	if (code < 0)
		cout << "Error receiving response" << endl;

	for (int i = 0; i < 10; i++)
		cout << response[i] << " ";
	cout << endl;
	
}
