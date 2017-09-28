//Zaira E Cruz
//September 28,2016
//Proxy server that listens for incoming connections from user input port.
//The proxy server then reads the inoput from the connected client and uses
//input to make GET command(2 lines). Proxy server then connects to another port
//80 to pass in this HTTP command and then receives message back. This message
//is again trasnferred back to the client.

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 4096

//Error handling function.
void error(const char *msg) {
	perror(msg); 
	exit(0);
}

int main(int argc, char **argv)
{

    char str[256];
    int listen_fd,conn_fd, sock_fd,portnum,n,m,p;
    char buffer[1024],recvline[BUFFER_SIZE];
    char *message="GET / HTTP/1.1\r\nHost: %s\r\n\r\n";
     struct sockaddr_in servaddr,serv_addr;
	portnum=atoi(argv[1]);

    /* AF_INET - IPv4 IP , Type of socket, protocol*/
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    sock_fd = socket(AF_INET, SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(portnum);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr =htons(INADDR_ANY);
    serv_addr.sin_port = htons(80);


    /* Binds the above details to the socket */
	bind(listen_fd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* Start listening to incoming connections */
	listen(listen_fd, 20);

    /* Accepts an incoming connection */
		conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
      	bzero(str, 256);
	n=read(conn_fd,str,255);
	strtok(str,"\n");

    /*Concatenate message with given url*/
	sprintf(buffer,message,str);
    /*Get IP address from url and copy to the socket address*/
	struct hostent *client_server;
	client_server = gethostbyname(str);
	bcopy((char *)client_server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         client_server->h_length);

     	//Connect to port 80 second socket(sock_fd).
	if(connect(sock_fd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
		error("ERROR connecting");
	//Write the given command to port 80 . HTTP Request.
	m=write(sock_fd, buffer, strlen(buffer));
	//Read in the message from port 80.
	bzero(recvline,BUFFER_SIZE);
	while(read(sock_fd,recvline, sizeof(recvline))!=0)
	{
		//While we receive input from port 80 then we write our 
		//output to the client through other socket.
		write(conn_fd,recvline,strlen(recvline));
		bzero(recvline, BUFFER_SIZE);
	}
	close (sock_fd);//close the connection
	close (conn_fd); //close the connection
	return 0;
}
