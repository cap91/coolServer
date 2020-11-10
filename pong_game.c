#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "utils.h"

BUF* get_session_response(char* client_ip){
    //char *response = "{\"sid\":\"1\"\n}";
    BUF *result = malloc(sizeof(BUF));
    result->buffer = malloc(strlen(client_ip) + 1);
    memcpy(result->buffer,client_ip,strlen(client_ip));
    result->length = strlen(result->buffer);

    return result;
}