#include <Arduino.h>

namespace Rbt
{
    class Robot
    {
        public:
        Robot(): leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT), distanceSensor(DISTANCE_SENSOR_INIT),
        bluestickRemoteControl(BLUESTICK_REMOTE_CONTROL_INIT), raspberryRemoteControl(RASPBERRY_REMOTE_CONTROL_INIT)
        {initialize();}

        void initialize()
        {
            startTime = millis();
            endTime = millis() + RUN_TIME * 1000;
            remote();
        }
        void run()
        {
            unsigned long currentTime = millis();
            unsigned long elapsedTime = currentTime - startTime;
            int distance = distanceSensor.getDistance();
            RemoteControlDriver::command_t remoteCmd;
            bool haveRemoteCmd = bluestickRemoteControl.getRemoteCommand(remoteCmd) || raspberryRemoteControl.getRemoteCommand(remoteCmd);

            log("state: %s, currentTime: %lu, distance: %u remote: (%d,k:%d)\n", getStateName(state), currentTime, distance ,
            haveRemoteCmd, remoteCmd.key);

            if (isRemoteControlled()) {
                if (haveRemoteCmd)
                    handleRemoteControl(remoteCmd);
            }

           if(doneRunning(currentTime)){
              stop();
              return;
            }
        }

        protected:
        void moveForward()
        {
             state = stateMoving;
             leftMotor.setSpeed(255);
             rightMotor.setSpeed(255);
        }

        void turnLeft()
        {
             state = stateTurning;
             leftMotor.setSpeed(255);
             rightMotor.setSpeed(-255);
        }

        void turnRight()
        {
             state = stateTurning;
             leftMotor.setSpeed(-255);
             rightMotor.setSpeed(255);
        }

        void remote()
        {
          state = stateRemoteControlled;
          leftMotor.setSpeed(0);
          rightMotor.setSpeed(0);
        }

        void handleRemoteControl(RemoteControlDriver::command_t remoteCmd)
        {
          switch (remoteCmd.key) {
            case RemoteControlDriver::command_t::keyFollowObject:
                state = stateFollowingObject;
                break;
            case RemoteControlDriver::command_t::keyForward:
                leftMotor.setSpeed(255);
                rightMotor.setSpeed(255);
                break;
            case RemoteControlDriver::command_t::keyLeft:
                leftMotor.setSpeed(255);
                rightMotor.setSpeed(-255);
                break;
            case RemoteControlDriver::command_t::keyRight:
                leftMotor.setSpeed(-255);
                rightMotor.setSpeed(255);
                break;
            case RemoteControlDriver::command_t::keyBackward:
                leftMotor.setSpeed(0);
                rightMotor.setSpeed(0);
                break;
            case RemoteControlDriver::command_t::keyStop:
                leftMotor.setSpeed(0);
                rightMotor.setSpeed(0);
                break;
            default:
                break;
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
        bool isTurning(){return state == stateTurning;}
        bool isFollowingObject(){return state == stateFollowingObject;}
        bool isRemoteControlled(){return state == stateRemoteControlled;}
        bool obstacleAhead(unsigned int distance){return (distance <= TOO_CLOSE);}
        bool doneRunning(unsigned long currentTime){return (currentTime >= endTime);}

        private:
        enum state_t {stateStopped = 0, stateMoving = 1, stateFollowingObject = 2, stateRemoteControlled = 3, stateTurning = 4};
        state_t state;

        const char* getStateName(state_t state)
        {
             static const char* stateNames[] = {"stateStopped", "stateMoving", "stateFollowingObject", "stateRemoteControlled", "stateTurning"};
             return stateNames[state];
        }

        unsigned long startTime;
        unsigned long endTime;

        Motor leftMotor;
        Motor rightMotor;
        DistanceSensor distanceSensor;
        BluestickRemoteControl bluestickRemoteControl;
        RaspberryRemoteControl raspberryRemoteControl;
    };
};
