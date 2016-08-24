/*
 * keyboard_device.cpp
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#include "keyboard_device.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iterator>

std::vector<std::string> KeyboardDevice::GetKeyboardDeviceList()
{
    std::string INPUT_DEVICES = "/proc/bus/input/devices";
    std::ifstream ifs(INPUT_DEVICES);
    std::string line;

    std::vector<std::string> result;
    bool find_keyboard = false;
    bool find_event = false;
    while (std::getline(ifs, line))
    {
        if (line.find("I: Bus=") != std::string::npos)
        {
            find_keyboard = false;
            find_event = false;
        }

        if (line.find("N: Name=") != std::string::npos && line.find("keyboard") != std::string::npos)
        {
            find_keyboard = true;
        }

        if (find_keyboard && line.find("H: Handlers=") != std::string::npos && line.find("kbd") != std::string::npos)
        {
            find_event = true;
        }

        if (find_event)
        {
            std::istringstream iss(line);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{}};
            for (int i=0; i<tokens.size(); ++i)
            {
                 if (tokens[i].find("event") == 0)
                 {
                    result.push_back(tokens[i]);
                 }
            }
            find_keyboard = false;
            find_event = false;
        }
    }
    return result;
}

KeyboardDevice::KeyboardDevice(std::string kbd_event_path, bool grab)
{
    m_grab = grab;
    m_kbd_event_fh = -1;

    m_kbd_event_fh = open(kbd_event_path.c_str(), O_RDWR);
    if (m_kbd_event_fh >= 0) {
        releaseAllKeys(m_kbd_event_fh);
        if (m_grab)
            ioctl(m_kbd_event_fh, EVIOCGRAB, 1);
    }
}

KeyboardDevice::~KeyboardDevice()
{
    if (m_kbd_event_fh >= 0) {
        if (m_grab)
            ioctl(m_kbd_event_fh, EVIOCGRAB, 0);
        close(m_kbd_event_fh);
    }
}

bool KeyboardDevice::getKey(struct input_event* key)
{
    ssize_t len;
    do {
        len = read(m_kbd_event_fh, key, sizeof(*key));
    } while (len == -1 && errno == EINTR);

    //printf("\t in:  type %d, code %3d, value %d (%d)\n", key->type, key->code, key->value, (int)len);

    return (len == (ssize_t)sizeof(*key));
}

void KeyboardDevice::releaseAllKeys(int fd)
{
    struct input_event input;
    memset(&input, 0, sizeof(input));

    input.type = EV_KEY;
    input.value = 0;
    gettimeofday(&(input.time), NULL);
    for (int i = 0; i < 256; i++) {
        input.code = i;
        write(fd, &input, sizeof(input));
    }

    input.type = EV_SYN;
    input.code = SYN_REPORT;
    input.value = 0;
    gettimeofday(&(input.time), NULL);
    write(fd, &input, sizeof(input));
}

