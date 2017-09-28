# Proxy-Server-in-C
--  Part #1 of a proxy server program. 
Networking Project - Proxy server written in C using HTTP requests and ports. 


CLIENT:
  Client socket code that writes to proxy server an inputted url
  (proxy server then finds IP address of url sends request) and then client
  reads from proxy server the message received from the HTTP request.
 
PSERVER:
  Proxy server that listens for incoming connections from user input port.
  The proxy server then reads the input from the connected client and uses
  input to make GET command(2 lines). Proxy server then connects to another port
  80 to pass in this HTTP command and then receives message back. This message
  is again trasnferred back to the client.

Two main programs make up the first part of the proxy server: client.c and pserver.c
