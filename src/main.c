#include"../include/vital.h"
#include<stdio.h>
#include<stdlib.h>`
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<signal.h>
#include<termios.h>
#include<locale.h>
#include<stdint.h>
//declare external functions
void generate_sensor_data(VitalSigns* out);
int check_abnormal(const VitalSigns* data);
void check_all_abnormal(const VitalSigns* data);
void trigger_alert(int alert_type);
void log_data(const VitalSigns* data);
void* display_thread(void* arg);

extern volatile sig_atomic_t running;

static void handle_sigint (int sig);

static pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;//initialize mutex
static VitalSigns shared;

void* sensor_loop(void* arg){     //sensor thread function
                                  //initialize random generator
    unsigned long seed = (unsigned long)time(NULL)^(unsigned long)(uintptr_t)pthread_self();
    srand((unsigned)seed);                  //seed random number generator
    while(running){
        VitalSigns mid_shared;
        generate_sensor_data(&mid_shared);       //generate new sensor data
        //multiple threads access shared data,protect with mutex,have read and write
        pthread_mutex_lock(&data_mutex);
        shared = mid_shared;                   //update shared data
        pthread_mutex_unlock(&data_mutex);




        //new functions
        check_all_abnormal(&shared);     //check for all abnormal data
       
        if(alert_status.heart_rate_alert){
            trigger_alert(HEART_RATE_ALERT);    //trigger alert if abnormal
        }
        if(alert_status.oxygen_alert){
            trigger_alert(OXYGEN_ALERT);
        }
        if(alert_status.temperature_alert){
            trigger_alert(TEMPERATURE_ALERT);
        }
        log_data(&shared);               //log data to file

        sleep(1);
    }return NULL;
}

static void handle_sigint(int sig){//handle SIGINT and SIGTERM,do running=0
                                   // threads will exit their loops and terminate
                                   //all threads exit safely
     (void)sig;
    running=0;
}


int main(void){
    pthread_t sensor_tid,display_tid;
    //initialize signal handlers
    signal(SIGINT,handle_sigint);
    signal(SIGTERM,handle_sigint);
    
    //initialize shared data
    time(&shared.timestamp);
    shared.heart_rate=75;
    shared.blood_oxygen=98;
    shared.temperature=36.5;
    //create sensor thread
    if(pthread_create(&sensor_tid,NULL,sensor_loop,NULL)!=0){
        perror("Failed to create sensor thread");
        return 1;
    }

    setlocale(LC_ALL,"");//set locale to default environment


    //set local for UTF-8 so ncurses can prints Chinese correctly

    //create display thread
    struct {pthread_mutex_t* mutex;VitalSigns* shared;} 
    args={&data_mutex,&shared};
    if(pthread_create(&display_tid,NULL,display_thread,&args)!=0){
        perror("Failed to create display thread");
        running=0;
        pthread_join(sensor_tid,NULL);
        return 1;
}
while(running){
        sleep(1);
    }
    //wait for threads to finish
pthread_join(sensor_tid,NULL);
pthread_join(display_tid,NULL);
return 0;
}

