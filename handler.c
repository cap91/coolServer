
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#include "utils.h"
#include "pong_game.h"

typedef struct PARAMS {
       char* path;
       char* arguments;
} PARAMS;

static PARAMS* parse_request(char* request_string){
       PARAMS *data;
       data = malloc(sizeof(PARAMS));

       char *p1 = strstr(request_string,"/");
       char *p2 = strstr(p1," ");
	char *p3 = strstr(p1,"?");

       size_t len = p2-p1;
	size_t len_question = p3-p1;
	size_t len_path = len;
	

	if(p3 != NULL && len_question < len) len_path = len_question;

       char *path = (char*)malloc(sizeof(char)*(len_path+1));
       strncpy(path, p1, len_path);
       path[len_path] = '\0';
       data->path = path;

       if(p3 != NULL){
              size_t len_args= len - len_question - 1;
              char *arg = (char*)malloc(sizeof(char)*(len_args+1));
              strncpy(arg, p3 + 1, len_args);
              arg[len_args] = '\0';
              data->arguments = arg;
       }else{
              data->arguments = "";
       }
       
       return data;
}

static void free_params(PARAMS* data){

       free(data->path);

       free(data);

}

static BUF* get_file(char* path){

       BUF *file = NULL;
       char* name_with_extension;
       char* root = "../web_site";
       name_with_extension = malloc(strlen(path)+strlen(root)+1); 
       strcpy(name_with_extension, root); 
       strcat(name_with_extension, path); 

       file = read_file(name_with_extension);
       free(name_with_extension);
       if(file == NULL) file = read_file("../web_site/error.html");
       return file;

}

static BUF* request_handler(char* request,struct sockaddr_in client){

       PARAMS *formatted_data = parse_request(request);
       
       char *connected_ip = inet_ntoa(client.sin_addr);
       int port = ntohs(client.sin_port); 
       printf("IP: %s Port: %d Requested resource: '%s'\n",connected_ip,port, formatted_data->path);
      
       BUF *result = NULL;
              
       if(!strcmp(formatted_data->path,"/")){
              result = get_file("/index.html");
		//printf("result :%s len:%d\n",result->buffer,result->length); ;bug alla terza richiesta vengono il buffer contiene troppi dati 
       } 
       else if (!strcmp(formatted_data->path,"/join")){

              result = get_session_response(connected_ip);
              
       }
       else if (!strcmp(formatted_data->path,"/update")){

              result = get_upd_session_data(connected_ip,formatted_data->arguments);
              
       }else{
              result = get_file(formatted_data->path);
       }

       free_params(formatted_data);
	
       return result;
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
              BUF *responce = request_handler(request,client_address);
              char *response_message = "HTTP/1.1 200 OK \r\n\n";
              if(responce != NULL){
                     char* name_with_extension;
                     
                     name_with_extension = malloc(strlen(response_message)+responce->length+1); /* make space for the new string (should check the return value ...) */
                     strcpy(name_with_extension, response_message); /* copy name into the new var */
                     strncat(name_with_extension, responce->buffer,responce->length); /* add the extension */

                     send(client_socket,name_with_extension,strlen(name_with_extension),0);
                     free(responce->buffer);
                     free(responce);
                     free(name_with_extension);
                     
              }else{
                  send(client_socket,response_message,strlen(response_message),0);
              }

              close(client_socket);
                     
       }

       return;

}
