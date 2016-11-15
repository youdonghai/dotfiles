/*
 * keyboard_device.h
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#ifndef KEYBOARD_DEVICE_H_
#define KEYBOARD_DEVICE_H_

#include <string>
#include <vector>
#include <linux/input.h>

class KeyboardDevice {
public:
    static std::vector<std::string> GetKeyboardDeviceList();

    KeyboardDevice(std::string kbd_event_path, bool grab);

    virtual ~KeyboardDevice();

    bool getKey(struct input_event *key);

    bool isOK() {
        return m_kbd_event_fh >= 0;
    }

private:
    void releaseAllKeys(int fd);

    bool m_grab;
    int m_kbd_event_fh;
};

#endif /* KEYBOARD_DEVICE_H_ */
