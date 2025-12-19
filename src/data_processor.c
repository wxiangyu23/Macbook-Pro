#include<stdio.h>
#include"../include/vital.h"

int check_abnormal(const VitalSigns *data){
    if(data->heart_rate<60||data->heart_rate>120)return HEART_RATE_ALERT;
    if(data->blood_oxygen<96)return OXYGEN_ALERT;
    if(data->temperature>38)return TEMPERATURE_ALERT;
    return NORMAL;
}

void check_all_abnormal(const VitalSigns *data){
    if(data->heart_rate<60||data->heart_rate>120){
        alert_status.heart_rate_alert = 1;
    }else{
        alert_status.heart_rate_alert = 0;
    }
    
    if(data->blood_oxygen<96){
        alert_status.oxygen_alert = 1;
    }else{
        alert_status.oxygen_alert = 0;
    }
    
    if(data->temperature>38){
        alert_status.temperature_alert = 1;
    }else{
        alert_status.temperature_alert = 0;
    }
}