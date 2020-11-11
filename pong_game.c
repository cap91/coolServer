#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#define MAX_SESSIONS 5

typedef struct SESSION {
       char* ip_pl1;
       char* ip_pl2;
       char* session_code;
} SESSION;

void init_sessions(SESSION* array){
    for(int i = 0;i<MAX_SESSIONS;i++){
        array[i].ip_pl1 = "null";
        array[i].ip_pl2 = "null";
        array[i].session_code = "23";
    }
    return;
}

SESSION* get_sessions(){
    static SESSION *sessions = NULL;
    if(sessions == NULL){
        sessions = malloc(sizeof(struct SESSION)*MAX_SESSIONS);
        init_sessions(sessions);
    }
    return sessions;
}

int check_if_exis(char* ip){
    SESSION *sessions = get_sessions();
    int found = -1;

    for(int i = 0;i<MAX_SESSIONS;i++){
        if(!strcmp(ip,sessions[i].ip_pl1) || !strcmp(ip,sessions[i].ip_pl2)){
            found = i;
            break;
        }
    }

    return found;
}
char* get_first_empty(char* ip){
    SESSION *sessions = get_sessions();
    char *response = "FULL";
    for(int i = 0;i<MAX_SESSIONS;i++){
        if(!strcmp("null",sessions[i].ip_pl1)){
            sessions[i].ip_pl1 = ip;
            response = sessions[i].session_code;
            break;
        }
        if(!strcmp("null",sessions[i].ip_pl2)){
            sessions[i].ip_pl2 = ip;
            response = sessions[i].session_code;
            break;
        }
    }

    return response;

}
BUF* get_session_response(char* client_ip){

    int index = check_if_exis(client_ip);
    SESSION *sessions = get_sessions();
    //char *response = "{\"sid\":\"1\"\n}";
    char *code = "";
    if(index!=-1){
        code = sessions[index].session_code;
    }else{
        code = get_first_empty(client_ip);
    }
    printf("Found %d\n",index);
    BUF *result = malloc(sizeof(BUF));
    result->buffer = malloc(strlen(code) + 1);
    memcpy(result->buffer,code,strlen(code));
    result->length = strlen(result->buffer);

    return result;
}

