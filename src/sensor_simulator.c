#include"../include/vital.h"
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
void generate_sensor_data(VitalSigns *out){
    out->heart_rate = 60+rand()%82;
    out->blood_oxygen = 90+rand()%8;
    out->temperature = 36.0 +(rand()%50)/10.0;
    time(&out->timestamp);

}