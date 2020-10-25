
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>

#include "utils.h"

typedef struct PARAMS {
       char* path;
} PARAMS;

static PARAMS* parse_request(char* request_string){
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

static void free_params(PARAMS* data){

       free(data->path);

       free(data);

}

static BUF* request_handler(char* request){

       PARAMS *formatted_data = parse_request(request);
           
       BUF *file = NULL;
       printf("Requested resource : '%s'\n", formatted_data->path);
              
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
              free(name_with_extension);
              if(file == NULL) file = read_file("./htdocs/error.html");
              if(file == NULL ){
                     free_params(formatted_data);
                     printf("Forces crash");
                     return NULL;                
              }

       }

       free_params(formatted_data);

       return file;
}

void handle_requests(int server_socket){

       struct sockaddr_in client_address;

       listen(server_socket, 10);

       while (1)
       {
              int client_socket;
              socklen_t peer_addr_size;
              peer_addr_size = sizeof(struct sockaddr_in);
              
              client_socket = accept(server_socket,(struct sockaddr *) &client_address,&peer_addr_size);

              char request[2048] = "";

              recv(client_socket,&request,sizeof(request),0);
              BUF *responce = request_handler(request);
              
              if(responce != NULL){
                     char* name_with_extension;

                     char *response_message = "HTTP/1.1 200 OK \r\n\n";
                     name_with_extension = malloc(strlen(response_message)+strlen(responce->buffer)+1); /* make space for the new string (should check the return value ...) */
                     strcpy(name_with_extension, response_message); /* copy name into the new var */
                     strcat(name_with_extension, responce->buffer); /* add the extension */

                     send(client_socket,name_with_extension,strlen(name_with_extension),0);
                     free(responce->buffer);
                     free(responce);
                     free(name_with_extension);
                     
              }

              close(client_socket);
                     
       }

       return;

}
