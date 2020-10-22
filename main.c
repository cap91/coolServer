#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>

int main() {

       char response_message[256] = "HTTP/1.1 200 OK \r\n\n";
       char content[23] = "LOL";
       strcat(response_message,content);
        
       int socket_definer = socket(AF_INET, SOCK_STREAM, 0);

       if (socket_definer == -1) printf("Error Socket");

       struct sockaddr_in server_address,client_address;
       server_address.sin_family = AF_INET;
       server_address.sin_port = htons(80);
       server_address.sin_addr.s_addr = INADDR_ANY;

       int bind_result = bind(socket_definer, (struct sockaddr *) &server_address, sizeof(server_address));

       if( bind_result == -1) printf("Error Bind");

       //listen(socket_definer, LISTEN_BACKLOG);
       listen(socket_definer, 5);
       
       while (1)
       {
              int client_socket;
              socklen_t peer_addr_size;
              peer_addr_size = sizeof(struct sockaddr_in);
       
              client_socket = accept(socket_definer,(struct sockaddr *) &client_address,&peer_addr_size);
              char request[2048] = "";
              recv(client_socket,&request,sizeof(request),0);
              printf("%s",request);
              send(client_socket,response_message,strlen(response_message),0);

              close(client_socket);
              
       }
       
       close(socket_definer);

       return 0;
}