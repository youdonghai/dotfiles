//
// Created by youdonghai on 5/8/16.
//

#include "user_input_device.h"
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <string.h>

UserInputDevice::UserInputDevice(std::string name) {
    m_user_device_fh = -1;
    m_user_device_fh = open(USERDEV_FILENAME, O_WRONLY | O_NONBLOCK);
    if (m_user_device_fh >= 0) {
        ioctl(m_user_device_fh, UI_SET_EVBIT, EV_KEY);
        ioctl(m_user_device_fh, UI_SET_EVBIT, EV_SYN);
        for (int i = 0; i < 256; i++) {
            ioctl(m_user_device_fh, UI_SET_KEYBIT, i);
        }
        struct uinput_user_dev device;
        memset(&device, 0, sizeof(device));
        strcpy(device.name, name.c_str());
        device.id.bustype = BUS_VIRTUAL;
        device.id.vendor = 1;
        device.id.product = 1;
        device.id.version = 1;
        write(m_user_device_fh, &device, sizeof(device));
        ioctl(m_user_device_fh, UI_DEV_CREATE);
    }
}

UserInputDevice::~UserInputDevice() {
    if (m_user_device_fh >= 0) {
        releaseAllKeys(m_user_device_fh);
        ioctl(m_user_device_fh, UI_DEV_DESTROY);
        close(m_user_device_fh);
    }
}

bool UserInputDevice::PutKey(struct input_event *key) {
    ssize_t len;
    do {
        len = write(m_user_device_fh, key, sizeof(*key));
    } while (len == -1 && errno == EINTR);

    //printf("\t\e[1;31mout:  type %d, code %3d, value %d, time %ld (%d)\e[0m\n", key->type, key->code, key->value,
    //       key->time.tv_usec, (int)len);

    return (len == (ssize_t) sizeof(*key));
}

void UserInputDevice::releaseAllKeys(int fd) {
    struct input_event input;
    memset(&input, 0, sizeof(input));

    input.type = EV_KEY;
    input.value = 0;
    gettimeofday(&(input.time), NULL);
    for (int i = 0; i < 256; i++) {
        input.code = (unsigned short) i;
        write(fd, &input, sizeof(input));
    }

    input.type = EV_SYN;
    input.code = SYN_REPORT;
    input.value = 0;
    gettimeofday(&(input.time), NULL);
    write(fd, &input, sizeof(input));
}

