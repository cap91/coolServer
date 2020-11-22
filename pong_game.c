#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "utils.h"
#define MAX_SESSIONS 5
#define HALF_BAR_HEIGTH 15

typedef struct SESSION {
       char* ip_pl1;
       char* ip_pl2;
       char* session_code;
       int pl1_pos;
       int pl2_pos;
       int x_ball;
       int y_ball;
       int vector_x;
       int vector_y;
       long last_time;
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
        array[i].vector_x = 1;
        array[i].vector_y = 0;
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

    struct timeval tv;
    gettimeofday(&tv, NULL);

    for(int i = 0;i<MAX_SESSIONS;i++){
        if(!strcmp("null",sessions[i].ip_pl1)){
            sessions[i].ip_pl1 = ip;
            if(strcmp("null",sessions[i].ip_pl2)) sessions[i].last_time = tv.tv_sec;
            response = sessions[i].session_code;
            break;
        }
        if(!strcmp("null",sessions[i].ip_pl2)){
            sessions[i].ip_pl2 = ip;
            if(strcmp("null",sessions[i].ip_pl1)) sessions[i].last_time = tv.tv_sec;
            response = sessions[i].session_code;
            break;
        }
    }

    return response;

}
char* compose_session_response(char* session_code){
    char *prefix = "{\"sid\":\"";
    char *suffix = "\"}";
    char *response = malloc(strlen(session_code) + strlen(prefix) + strlen(suffix) + 1);
    strcpy(response,prefix);
    strcat(response,session_code);
    strcat(response,suffix);
    return response;
}
BUF* get_session_response(char* client_ip){

    int index = check_if_exis(client_ip);
    SESSION *sessions = get_sessions();
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
void compute_session_changes(SESSION* session){
    if(!strcmp("null",session->ip_pl1) || !strcmp("null",session->ip_pl2)) return;
    struct timeval tv;
    gettimeofday(&tv, NULL);
     
    /*
    y_ball = y_ball + (tv.tv_sec - session) * vector_y;
    if(y_ball \ 100 % 2 == 0){
        y_ball = y_ball % 100;
    }else{
        y_ball = 100 - y_ball % 100; 
    }
    x_ball = x_ball + (tv.tv_sec - session) * vector_x;
    if(x_ball % 100 == 0){
        // Controllo collisione con le barre
    }else{
        if(x_ball \ 100 % 2 == 0){
            x_ball = x_ball % 100;
        }else{
            x_ball = 100 - x_ball % 100;
        }    
    }
    */
    
    printf("Time passed :%d\n",tv.tv_sec - session->last_time);

    session->last_time = tv.tv_sec;

}
void change_player_position(SESSION* session,char* client_ip,int add_position){
    int *position = NULL;

    if(!strcmp(session->ip_pl1,client_ip)){
        position = &session->pl1_pos;
    }
    else if(!strcmp(session->ip_pl2,client_ip)){
        position = &session->pl2_pos;
    }
    if(position == NULL) return;

    if(*position + add_position < HALF_BAR_HEIGTH){
        add_position = (*position - HALF_BAR_HEIGTH) * -1;
    }
    if(*position + add_position > 100 - HALF_BAR_HEIGTH){
        add_position = 100 - HALF_BAR_HEIGTH - *position;
    }
    *position = *position + add_position;
}
char* compose_position_response(SESSION session){
    char *prefix = "{\"p1\":";
    char *string_1 = ",\"p2\":";
    char *string_2 = ",\"ball_x\":";
    char *string_3 = ",\"ball_y\":";
    char *suffix = "}";

    char p1[4];
    char p2[4];
    char ball_x[4];
    char ball_y[4];

    sprintf(p1, "%d", session.pl1_pos);
    sprintf(p2, "%d", session.pl2_pos);
    sprintf(ball_x, "%d", session.x_ball);
    sprintf(ball_y, "%d", session.y_ball);

    int static_length = strlen(prefix) + strlen(string_1) + strlen(string_2) + strlen(string_3) + strlen(suffix);
    int num_length = strlen(p1) + strlen(p2) + strlen(ball_x) + strlen(ball_y);

    char *response = malloc(static_length + num_length + 1);

    strcpy(response,prefix);
    strcat(response,p1);
    strcat(response,string_1);
    strcat(response,p2);
    strcat(response,string_2);
    strcat(response,ball_x);
    strcat(response,string_3);
    strcat(response,ball_y);
    strcat(response,suffix);
    
    return response;
}
BUF* get_upd_session_data(char* client_ip,char* args){
    int index = check_if_exis(client_ip);
    SESSION *sessions = get_sessions();
    if(index==-1) return NULL;

    compute_session_changes(&sessions[index]);
    if(!strcmp(args,"top"))change_player_position(&sessions[index],client_ip,10);
    if(!strcmp(args,"bot"))change_player_position(&sessions[index],client_ip,-10);

    BUF *result = malloc(sizeof(BUF));
    result->buffer = compose_position_response(sessions[index]);
    result->length = strlen(result->buffer);
    return result;

}

\\ prova
