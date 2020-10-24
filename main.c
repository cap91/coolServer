#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>

#include "utils.h"
typedef struct PARAMS
{
       char* path;
} PARAMS;

PARAMS* read_request(char* request_string){
       PARAMS *data;
       data = malloc(sizeof(PARAMS));

       char *p1 = strstr(request_string,"/");
       char *p2 = strstr(p1," ");
       size_t len = p2-p1;
       char *res = (char*)malloc(sizeof(char)*(len+1));
       //char res[len+1];
       strncpy(res, p1, len);
       res[len] = '\0';
       data->path = res;
       
       return data;
}

void free_params(PARAMS* data){
       free(data->path);
       free(data);

}

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

              PARAMS *formatted_data = read_request(request);

              
              BUF *file = NULL;
              printf("'%s'\n", formatted_data->path);
              
              if(!strcmp(formatted_data->path,"/")){
                     file = read_file("./htdocs/index.html");
              } 
              else{
                     char* name_with_extension;
                     char* root = "./htdocs";
                     name_with_extension = malloc(strlen(formatted_data->path)+strlen(root)+1); /* make space for the new string (should check the return value ...) */
                     strcpy(name_with_extension, root); /* copy name into the new var */
                     strcat(name_with_extension, formatted_data->path); /* add the extension */

                     file = read_file(name_with_extension);
                     if(file == NULL) file = read_file("./htdocs/error.html");
                     if(file == NULL ){
                            free_params(formatted_data);
                            close(client_socket);   
                            printf("Forces crash");
                            return 0;                
                     }

              }
              
              send(client_socket,file->buffer,strlen(file->buffer),0);
              //send(client_socket,request,strlen(request),0);

              free(file->buffer);
              free(file);
              free_params(formatted_data);
              close(client_socket);
              
       }
       
       close(socket_definer);

       return 0;
}

