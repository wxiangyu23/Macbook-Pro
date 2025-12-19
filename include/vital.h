#ifndef VITAL_H
#define VITAL_H

#include<time.h>
#include<signal.h>

typedef struct{
    time_t timestamp;
    int heart_rate;
    int blood_oxygen;
    double temperature;
}VitalSigns;

enum AlertType{
    NORMAL = 0,
    HEART_RATE_ALERT = 1,
    OXYGEN_ALERT = 2,
    TEMPERATURE_ALERT=3,
};

typedef struct{
    int heart_rate_alert;
    int oxygen_alert;
    int temperature_alert;
}AlertStatus;

extern volatile sig_atomic_t last_alert;
extern AlertStatus alert_status;
#endif