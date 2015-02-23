#include <Arduino.h>

namespace Rbt
{
    class Robot
    {
        public:
        Robot(): leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT), distanceSensor(DISTANCE_SENSOR_INIT)
        {
            initialize();
        }
        
        void initialize()
        {
            startTime = millis();
            endTime = millis() + RUN_TIME * 1000;
            followObject();          
        }
        void run()
        {
            unsigned long currentTime = millis();
            unsigned long elapsedTime = currentTime - startTime;            
            int distance = distanceSensor.getDistance();
            log("state: %s, currentTime: %lu, distance: %u\n", getStateName(state), currentTime, distance);        
            
            if(doneRunning(currentTime)){
              stop();
              return;
            }
            
            if(obstacleAhead(distance))
              stop();
            else
              followObject();
        }
        
        protected:        
        void move()
        {
             state = stateMoving;
             leftMotor.setSpeed(255);
             rightMotor.setSpeed(255);
        }
        
        void followObject()
        {
             if(Serial.available() > 0){
             int num_received = Serial.parseInt();
             if(num_received == 2)
               leftMotor.setSpeed(255);
             if(num_received == 1)
                rightMotor.setSpeed(255);
             if(num_received == 0){
               rightMotor.setSpeed(0);
               leftMotor.setSpeed(0);
             }         
           }
        }
        
        void stop()
        {
             state = stateStopped;
             leftMotor.setSpeed(0);
             rightMotor.setSpeed(0);
        }
        
        bool isStopped(){return state == stateStopped;}
        bool isMoving(){return state == stateMoving;}
        bool isFollowingObject(){return state == stateFollowingObject;}
        bool obstacleAhead(unsigned int distance){return (distance <= TOO_CLOSE);}        
        bool doneRunning(unsigned long currentTime){return (currentTime >= endTime);}
    
        private:
        enum state_t {stateStopped = 0, stateMoving = 1, stateFollowingObject = 2};
        state_t state;
        
        const char* getStateName(state_t state)
        {
             static const char* stateNames[] = {"stateStopped", "stateMoving", "stateFollowingObject"};  
             return stateNames[state];
        }    
        
        unsigned long startTime;
        unsigned long endTime;
        
        Motor leftMotor;
        Motor rightMotor;
        DistanceSensor distanceSensor;
    };
};
