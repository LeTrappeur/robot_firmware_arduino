#define LOGGING

#define ENABLE_ADAFRUIT_MOTOR_DRIVER
#define ENABLE_NEWPING_DISTANCE_SENSOR_DRIVER

#define TOO_CLOSE 10
#define MAX_DISTANCE (TOO_CLOSE * 20)
#define RUN_TIME 10

#ifdef ENABLE_ADAFRUIT_MOTOR_DRIVER
#include <AFMotor.h>
#include "adafruit_motor_driver.h"
#define LEFT_MOTOR_INIT 1
#define RIGHT_MOTOR_INIT 3
#endif

#ifdef ENABLE_NEWPING_DISTANCE_SENSOR_DRIVER
#include <NewPing.h>
#include "newping_distance_sensor.h"
#define DISTANCE_SENSOR_INIT 14,15,MAX_DISTANCE
#endif

#include "logging.h"
#include "robot.h"

Rbt::Robot robot;

void setup()
{
    Serial.begin(9600);
    robot.initialize();
}

void loop()
{
    robot.run();
}
