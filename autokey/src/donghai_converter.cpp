/*
 * donghai_converter.cpp
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#include "donghai_converter.h"


#define BIT_LEFTCTRL (1 << 0)
#define BIT_RIGHTCTRL (1 << 1)
#define BIT_LEFTSHIFT (1 << 2)
#define BIT_RIGHTSHIFT (1 << 3)
#define BIT_LEFTALT (1 << 4)
#define BIT_RIGHTALT (1 << 5)
#define BIT_CAPSLOCK (1 << 6)
#define BIT_H (1 << 7)
#define BIT_J (1 << 8)
#define BIT_K (1 << 9)
#define BIT_L (1 << 10)
#define BIT_I (1 << 11)
#define BIT_LEFTBRACE (1 << 12)

#define BIT_LEFT (1 << 13)
#define BIT_DOWN (1 << 14)
#define BIT_UP (1 << 15)
#define BIT_RIGHT (1 << 16)
#define BIT_INSERT (1 << 17)
#define BIT_ESC (1 << 18)

#define IS_LOGIC_KEY_DOWN(key_bit) ((m_logic_key_flags & key_bit) != 0)
#define ONLY_CAPSLOCK_DOWN() (m_physic_key_flags == BIT_CAPSLOCK)


DonghaiConverter::DonghaiConverter() {
    m_physic_key_flags = 0;
    m_logic_key_flags = 0;
    m_send_syn_event = false;
    m_donghai_mode = false;
}

DonghaiConverter::~DonghaiConverter() {
}

bool DonghaiConverter::handleInput(struct input_event *input) {
    switch (input->type) {
        case EV_MSC:
            return handleMscInput(input);
        case EV_KEY:
            return handleKeyInput(input);
        case EV_SYN:
            return handleSynInput(input);
        default:
            addOutput(input, false);
            break;
    }
    return true;
}

bool DonghaiConverter::handleMscInput(struct input_event *input) {
    if (!isSpecialKey(input)) {
        addOutput(input, false);
        return true;
    }
    return false;
}

bool DonghaiConverter::handleKeyInput(struct input_event *input) {
    if (!isSpecialKey(input)) {
        leaveDonghaiMode();
        addOutput(input, false);
        m_send_syn_event = true;
        updateKeyFlags(&m_physic_key_flags, input->code, input->value);
        return true;
    }

    switch (input->code) {
        case KEY_CAPSLOCK:
            handleCapsLock(input);
            break;
        case KEY_H:
            handleMapKey(input, KEY_LEFT, BIT_H, BIT_LEFT);
            break;
        case KEY_J:
            handleMapKey(input, KEY_DOWN, BIT_J, BIT_DOWN);
            break;
        case KEY_K:
            handleMapKey(input, KEY_UP, BIT_K, BIT_UP);
            break;
        case KEY_L:
            handleMapKey(input, KEY_RIGHT, BIT_L, BIT_RIGHT);
            break;
        case KEY_I:
            handleInsertKey(input);
            break;
        case KEY_LEFTBRACE:
            handleMapKey(input, KEY_ESC, BIT_LEFTBRACE, BIT_ESC);
            break;
        default:
            break;
    }
    updateKeyFlags(&m_physic_key_flags, input->code, input->value);
    return true;
}

bool DonghaiConverter::handleSynInput(struct input_event *input) {
    if (m_send_syn_event) {
        addOutput(input, false);
        m_send_syn_event = false;
    }
    return false;
}

void DonghaiConverter::updateKeyFlags(int *flags, uint16_t key_code, int32_t key_val) {
    if (key_val == 2) {
        return;
    }
    switch (key_code) {
        case KEY_LEFTCTRL:
            setKeyFlags(flags, BIT_LEFTCTRL, key_val);
            break;
        case KEY_RIGHTCTRL:
            setKeyFlags(flags, BIT_RIGHTCTRL, key_val);
            break;
        case KEY_LEFTSHIFT:
            setKeyFlags(flags, BIT_LEFTSHIFT, key_val);
            break;
        case KEY_RIGHTSHIFT:
            setKeyFlags(flags, BIT_RIGHTSHIFT, key_val);
            break;
        case KEY_LEFTALT:
            setKeyFlags(flags, BIT_LEFTALT, key_val);
            break;
        case KEY_RIGHTALT:
            setKeyFlags(flags, BIT_RIGHTALT, key_val);
            break;
        case KEY_CAPSLOCK:
            setKeyFlags(flags, BIT_CAPSLOCK, key_val);
            break;
        case KEY_H:
            setKeyFlags(flags, BIT_H, key_val);
            break;
        case KEY_J:
            setKeyFlags(flags, BIT_J, key_val);
            break;
        case KEY_K:
            setKeyFlags(flags, BIT_K, key_val);
            break;
        case KEY_L:
            setKeyFlags(flags, BIT_L, key_val);
            break;
        case KEY_I:
            setKeyFlags(flags, BIT_I, key_val);
            break;
        case KEY_LEFTBRACE:
            setKeyFlags(flags, BIT_LEFTBRACE, key_val);
            break;
        case KEY_LEFT:
            setKeyFlags(flags, BIT_LEFT, key_val);
            break;
        case KEY_DOWN:
            setKeyFlags(flags, BIT_DOWN, key_val);
            break;
        case KEY_UP:
            setKeyFlags(flags, BIT_UP, key_val);
            break;
        case KEY_RIGHT:
            setKeyFlags(flags, BIT_RIGHT, key_val);
            break;
        case KEY_INSERT:
            setKeyFlags(flags, BIT_INSERT, key_val);
            break;
        case KEY_ESC:
            setKeyFlags(flags, BIT_ESC, key_val);
            break;
        default:
            break;
    }
}

void DonghaiConverter::setKeyFlags(int *flags, int32_t bit, int32_t key_val) {
    if (0 == key_val) {
        *flags &= ~bit;
    } else if (1 == key_val) {
        *flags |= bit;
    }
}

void DonghaiConverter::handleCapsLock(struct input_event *key_event) {
    if (key_event->value == 0) {
        leaveDonghaiMode();
    }
    if (IS_LOGIC_KEY_DOWN(BIT_LEFTCTRL)) {
        if (key_event->value == 1) {
            return;
        }
        doKeyEvent(KEY_LEFTCTRL, key_event->value, true, false);
        m_send_syn_event = true;
        return;
    } else {
        if (key_event->value == 1) {
            doKeyEvent(KEY_LEFTCTRL, 1, true, false);
            m_send_syn_event = true;
        }
    }
}

void DonghaiConverter::enterDonghaiMode(struct input_event *key_event) {
    if (ONLY_CAPSLOCK_DOWN() && key_event->value == 1) {
        if (m_donghai_mode) {
            return;
        }
        if (IS_LOGIC_KEY_DOWN(BIT_LEFTCTRL)) {
            doKeyEvent(KEY_LEFTCTRL, 0);
        }
        m_donghai_mode = true;
    }
}

void DonghaiConverter::leaveDonghaiMode() {
    if (!m_donghai_mode) {
        return;
    }

    // release all the special key
    if (IS_LOGIC_KEY_DOWN(BIT_LEFT)) {
        doKeyEvent(KEY_LEFT, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_DOWN)) {
        doKeyEvent(KEY_DOWN, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_UP)) {
        doKeyEvent(KEY_UP, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_RIGHT)) {
        doKeyEvent(KEY_RIGHT, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_ESC)) {
        doKeyEvent(KEY_ESC, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_INSERT)) {
        doKeyEvent(KEY_INSERT, 0);
    }
    if (IS_LOGIC_KEY_DOWN(BIT_LEFTSHIFT)) {
        doKeyEvent(KEY_LEFTSHIFT, 0);
    }

    if (!IS_LOGIC_KEY_DOWN(BIT_LEFTCTRL)) {
        doKeyEvent(KEY_LEFTCTRL, 1);
    }
    m_donghai_mode = false;
}

void DonghaiConverter::handleMapKey(struct input_event *key_event, uint16_t map_key_code, int32_t original_bit, int32_t map_bit) {
    enterDonghaiMode(key_event);
    if (!m_donghai_mode) {
        normalKeyOutPut(key_event, original_bit);
        return;
    }
    if (IS_LOGIC_KEY_DOWN(map_bit)) {
        if (key_event->value == 1) {
            return;
        }
        doKeyEvent(map_key_code, key_event->value);
    } else {
        if (key_event->value == 1) {
            doKeyEvent(map_key_code, key_event->value);
        }
    }
}

void DonghaiConverter::handleInsertKey(struct input_event *key_event) {
    enterDonghaiMode(key_event);
    if (!m_donghai_mode) {
        normalKeyOutPut(key_event, BIT_I);
        return;
    }
    if (key_event->value == 1 || key_event->value == 2) {
        if (!IS_LOGIC_KEY_DOWN(BIT_LEFTSHIFT)) {
            doKeyEvent(KEY_LEFTSHIFT, 1);
        }
        if (!IS_LOGIC_KEY_DOWN(BIT_INSERT)) {
            doKeyEvent(KEY_INSERT, 1);
            if (key_event->value == 2) {
                doKeyEvent(KEY_INSERT, 2);
            }
        } else {
            if (key_event->value == 2) {
                doKeyEvent(KEY_INSERT, 2);
            }
        }
    } else if (key_event->value == 0) {
        if (IS_LOGIC_KEY_DOWN(BIT_INSERT)) {
            doKeyEvent(KEY_INSERT, 0);
        }
        if (IS_LOGIC_KEY_DOWN(BIT_LEFTSHIFT)) {
            doKeyEvent(KEY_LEFTSHIFT, 0);
        }
    }
}

void DonghaiConverter::addOutput(struct input_event *output, bool setTime) {
    if (output->type == EV_KEY) {
        updateKeyFlags(&m_logic_key_flags, output->code, output->value);
    }
    Converter::addOutput(output, setTime);
}

void DonghaiConverter::normalKeyOutPut(struct input_event *key_event, int32_t bit) {
    if (IS_LOGIC_KEY_DOWN(bit)) {
        if (key_event->value == 1) {
            return;
        }
        doKeyEvent(key_event->code, key_event->value, true, false);
        m_send_syn_event = true;
    } else {
        if (key_event->value == 1) {
            doKeyEvent(key_event->code, key_event->value, true, false);
            m_send_syn_event = true;
        }
    }
    return;
}





