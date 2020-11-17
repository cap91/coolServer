#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#define MAX_SESSIONS 5

typedef struct SESSION {
       char* ip_pl1;
       char* ip_pl2;
       char* session_code;
       int pl1_pos;
       int pl2_pos;
       int x_ball;
       int y_ball;
       int last_time;
} SESSION;

void init_sessions(SESSION* array){
    for(int i = 0;i<MAX_SESSIONS;i++){
        array[i].ip_pl1 = "null";
        array[i].ip_pl2 = "null";
        array[i].session_code = "23";
        array[i].pl1_pos = 50;
        array[i].pl2_pos = 50;
        array[i].x_ball = 50;
        array[i].y_ball = 50;
        array[i].last_time = 0;
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
char* compose_session_response(char* session_code){
    char *prefix = "{\"sid\":\"";
    char *suffix = "\"}";
    char *response = malloc(strlen(session_code) + strlen(prefix) + strlen(suffix) + 3);
    strcpy(response,prefix);
    strcat(response,session_code);
    strcat(response,suffix);
    return response;
}
char* compose_position_response(SESSION session){

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
    printf("Found %d\n",index,code);
    BUF *result = malloc(sizeof(BUF));
    result->buffer = compose_session_response(code);
    result->length = strlen(result->buffer);

    return result;
}
void compute_session_changes(SESSION session){

}
void change_player_position(char* client_ip,int add_position){
    
}
BUF* get_upd_session_data(char* client_ip,int add_position){
    int index = check_if_exis(client_ip);
    SESSION *sessions = get_sessions();
    if(index==-1) return NULL;
    compute_session_changes(sessions[index]);
    change_player_position(client_ip,add_position);
    char *response = compose_position_response(sessions[index]);
}
