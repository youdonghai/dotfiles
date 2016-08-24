//
// Created by youdonghai on 5/8/16.
//

#ifndef AUTOKEY_LINUX_USER_INPUT_DEVICE_H
#define AUTOKEY_LINUX_USER_INPUT_DEVICE_H

#include <linux/input.h>
#include <string>


#define USERDEV_FILENAME "/dev/uinput"

class UserInputDevice{
public:
    UserInputDevice(std::string name);
    ~UserInputDevice();

    bool PutKey(struct input_event* key);

    bool isOK()
    {
        return m_user_device_fh >= 0;
    }

private:
    void releaseAllKeys(int fd);

    int m_user_device_fh;
};


#endif //AUTOKEY_LINUX_USER_INPUT_DEVICE_H
