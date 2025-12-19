#include"../include/vital.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<locale.h>
#include<ncurses.h>
#include<signal.h>

volatile sig_atomic_t running = 1;

typedef struct{
    pthread_mutex_t *mutex;//protect shared data
    VitalSigns *shared;//pointer to shared vital signs data
}DisplayArgs;


void* display_thread(void* arg){
    DisplayArgs* a = (DisplayArgs*)arg;//cast void* to DisplayArgs*//force translation
    setlocale(LC_ALL, "");//set locale to support UTF-8
    initscr();//initialize ncurses
    noecho();//disable echoing of typed characters
    curs_set(FALSE);//hide cursor
    nodelay(stdscr, TRUE);//non-blocking input
    if(has_colors){//initialize color if supported
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
    }
    while(running){                      //main loop
        pthread_mutex_lock(a->mutex);
        VitalSigns copy = *(a->shared);//get a copy of shared data
        pthread_mutex_unlock(a->mutex);

        //time formatting
        char timestr[64];
        struct tm* tm_info = localtime(&copy.timestamp);
        if(tm_info){
            strftime(timestr,sizeof(timestr),"%Y-%m-%d %H:%M:%S",tm_info);
        }else{
            snprintf(timestr,sizeof(timestr),"%ld",(long)copy.timestamp);
        }                         

        clear();//clear screen
        mvprintw(0,0,"time:%s",timestr);//display time
        mvprintw(1,0,"Heart Rate: %d bpm",copy.heart_rate);//display heart rate
        mvprintw(2,0,"Blood Oxygen: %d %%",copy.blood_oxygen);
        mvprintw(3,0,"Temperature: %.2f °C",copy.temperature);
        
        if(has_colors()) attron(COLOR_PAIR(1)|A_BOLD);//red and bold
        else attron(A_BOLD);//bold only
        
        int alert_line = 5;
        if(alert_status.heart_rate_alert){
            mvprintw(alert_line, 0, "ALERT: High Heart Rate!");
            alert_line++;
        }
        if(alert_status.oxygen_alert){
            mvprintw(alert_line, 0, "ALERT: Low Blood Oxygen!");
            alert_line++;
        }
        if(alert_status.temperature_alert){
            mvprintw(alert_line, 0, "ALERT: High Temperature!");
            alert_line++;
        }
        
        if(has_colors()) attroff(COLOR_PAIR(1)|A_BOLD);
        else attroff(A_BOLD);
        refresh();//refresh screen to show changes

        int ch = getch();//check for user input
        if(ch == 'q' || ch == 'Q'){
            running = 0;
            break;
        }
        usleep(1000000);//sleep for 1 second
    }







    endwin();//end ncurses mode
    return NULL;
}