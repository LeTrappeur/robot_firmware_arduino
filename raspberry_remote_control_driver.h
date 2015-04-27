#include "remote_control_driver.h"

namespace Rbt
{
    class RaspberryRemoteControl : public RemoteControlDriver
    {
    public:
        /**
          * @brief Class constructor.
          */
        RaspberryRemoteControl() : RemoteControlDriver() {}

        virtual bool getRemoteCommand(command_t& cmd)
        {
            cmd.key = command_t::keyNone;

            if (Serial.available() <= 0)
                return false; // no commands available
            char ch = Serial.read();
            switch (ch) {
                case '8': // up
                    cmd.key = command_t::keyForward;
                    break;
                case '2': // down
                    cmd.key = command_t::keyBackward;
                    break;
                case '4': // left
                    cmd.key = command_t::keyLeft;
                    break;
                case '6': // right
                    cmd.key = command_t::keyRight;
                    break;
                case 'A': // function key #1
                case 'C':
                    cmd.key = command_t::keyFollowObject;
                    break;
                case 'B': // function key #2
                case 'D':
                    cmd.key = command_t::keyRemoteControl;
                    break;
                case 'E': // function key #3
                    cmd.key = command_t::keyNone;
                    break;
                case 'F': // function key #4
                    cmd.key = command_t::keyNone;
                    break;
                default:
                    break;
            }
            if (cmd.key != command_t::keyNone) {
                return false;
            }
            return true;
        }

    private:
    };
};
