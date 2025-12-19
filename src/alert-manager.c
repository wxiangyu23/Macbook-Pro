#include<stdio.h>
#include"../include/vital.h"
#include<stdlib.h>
#include<time.h>

volatile sig_atomic_t last_alert = NORMAL;
AlertStatus alert_status = {0, 0, 0};

void trigger_alert(int alert_type){
    last_alert = alert_type;
    printf("\033[1;31m"); 
    printf("\a");
    
    /*switch(alert_type){
        case HEART_RATE_ALERT:
            alert_status.heart_rate_alert = 1;
            printf("ALERT: Abnormal Heart Rate Detected!\n");
            break;
        case OXYGEN_ALERT:
            alert_status.oxygen_alert = 1;
            printf("ALERT: Low Blood Oxygen Level Detected!\n");
            break;
        case TEMPERATURE_ALERT:
            alert_status.temperature_alert = 1;
            printf("ALERT: Abnormal Body Temperature Detected!\n");
            break;
        default:
            printf("No Alerts.\n");
            break;
    }*/
    printf("\033[0m");
    fflush(stdout);
}