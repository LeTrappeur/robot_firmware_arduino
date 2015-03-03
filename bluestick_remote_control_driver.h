#include "remote_control_driver.h"

namespace Rbt
{
    class RemoteControl : public RemoteControlDriver
    {
    public:
        /**
          * @brief Class constructor.
          */
        RemoteControl() : RemoteControlDriver(), lastKey(command_t::keyNone) {}

        virtual bool getRemoteCommand(command_t& cmd)
        {
            //cmd.stop();
            cmd.key = command_t::keyNone;

            if (BTSerial.available() <= 0)
                return false; // no commands available
            char ch = BTSerial.read();
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
            if (cmd.key != command_t::keyNone && cmd.key == lastKey) {
                // repeated key, ignore it
                return false;
            }
            lastKey = cmd.key;
            return true;
        }

    private:
        command_t::key_t lastKey;
    };
};
