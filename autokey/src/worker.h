//
// Created by youdonghai on 5/8/16.
//

#ifndef AUTOKEY_LINUX_WORKER_H
#define AUTOKEY_LINUX_WORKER_H

#include "keyboard_device.h"
#include "user_input_device.h"
#include "converter.h"

class Worker {
public:
    Worker(std::string kbd_event_file);
    ~Worker();

    void run();

private:
    std::string kbd_event_file;
    Converter *cvt;
};


#endif //AUTOKEY_LINUX_WORKER_H
