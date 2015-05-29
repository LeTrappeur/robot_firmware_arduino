#ifndef REMOTECONTROLDRIVER_H
#define REMOTECONTROLDRIVER_H

namespace Rbt
{
  class RemoteControlDriver
  {
    public:
        struct command_t {
            enum key_t { keyNone, keyFollowObject, keyRemoteControl, keyForward, keyBackward, keyLeft, keyRight, keyStop};
            key_t key;
            command_t() : key(keyNone) {}
        };
        RemoteControlDriver() {}

        virtual bool getRemoteCommand(command_t& cmd) = 0;
  };
};

#endif
