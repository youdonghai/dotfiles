//
// Created by youdonghai on 5/8/16.
//

#include "worker.h"
#include "donghai_converter.h"

Worker::Worker(std::string kbd_event_file) {
    this->kbd_event_file = kbd_event_file;
    this->cvt = new DonghaiConverter();
}

Worker::~Worker() {
    if (this->cvt)
        delete this->cvt;
}

void Worker::run() {
    std::string kbd_event_path = "/dev/input/" + kbd_event_file;
    KeyboardDevice kbd_device(kbd_event_path, true);
    std::string device_name = "donghai_" + kbd_event_file;
    UserInputDevice uinput_device(device_name);

    if (!(kbd_device.isOK() && uinput_device.isOK())) {
        return;
    }

    struct input_event key;
    struct input_event *pkey = NULL;

    while (true) {
        if (kbd_device.getKey(&key)) {
            this->cvt->addInput(&key);
        }

        while (this->cvt->getOutput(&pkey)) {
            uinput_device.PutKey(pkey);
        }
    }
}
