#include<stdio.h>
#include"../include/vital.h"
#include<time.h>


void log_data(const VitalSigns* data){
    FILE* fp = fopen("vital_log.csv", "a");//append mode
    if(!fp)return;
    struct tm* local_time = localtime(&data->timestamp);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    fprintf(fp,"\ntime %s,heart_rate %d,blood_oxygen %d,temperature %.2f\n",
         time_str, 
         data->heart_rate,
          data->blood_oxygen, 
          data->temperature);


    fclose(fp);
}