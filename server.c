#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int get_binded_soket(int port){
    
       int socket_definer = socket(AF_INET, SOCK_STREAM, 0);

       if (socket_definer == -1) return -1;

       struct sockaddr_in server_address;

       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(port);
       server_address.sin_addr.s_addr = INADDR_ANY;

       int bind_result = bind(socket_definer, (struct sockaddr *) &server_address, sizeof(server_address));

       if( bind_result == -1) return -1;

       return socket_definer;

}