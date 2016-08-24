/*
 * donghai_converter.cpp
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#include "donghai_converter.h"
#include <string.h>
#include <stdio.h>

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

#define IS_KEY_DOWN(key_bit) ((m_key_flags & key_bit) != 0)
#define ONLY_CAPSLOCK_ON() (m_key_flags == BIT_CAPSLOCK)


DonghaiConverter::DonghaiConverter()
{
    m_key_flags = 0;
    m_nav_mode = false;
    m_skip_key_flags = 0;

    for (int i = 0; i < MAX_INPUT_BUFFER_SIZE; ++i)
    {
        memset(&m_input_buffer[i], 0x0, sizeof(m_input_buffer[i]));
    }
    m_input_buffer_index = 0;
    m_cached_msc_event = getInputEvent(4, 4, 0);

    m_special_key_map[KEY_H] = BIT_H;
    m_special_key_map[KEY_J] = BIT_J;
    m_special_key_map[KEY_K] = BIT_K;
    m_special_key_map[KEY_L] = BIT_L;
    m_special_key_map[KEY_I] = BIT_I;
    m_special_key_map[KEY_LEFTBRACE] = BIT_LEFTBRACE;

    m_meta_key_map[KEY_LEFTCTRL] = BIT_LEFTCTRL;
    m_meta_key_map[KEY_RIGHTCTRL] = BIT_RIGHTCTRL;
    m_meta_key_map[KEY_LEFTSHIFT] = BIT_LEFTSHIFT;
    m_meta_key_map[KEY_RIGHTSHIFT] = BIT_RIGHTSHIFT;
    m_meta_key_map[KEY_LEFTALT] = BIT_LEFTALT;
    m_meta_key_map[KEY_RIGHTALT] = BIT_RIGHTALT;
    m_meta_key_map[KEY_CAPSLOCK] = BIT_CAPSLOCK;
}

DonghaiConverter::~DonghaiConverter()
{
}

bool DonghaiConverter::handleInput(struct input_event* input)
{
    switch (input->type)
    {
    case EV_KEY:
        /* Key events are manipulated */
        return handleKeyInput(input);
    case EV_MSC:
        return handleMscInput(input);
    default:
        /* For other events, simply send the event as it is */
        addOutput(input);
        return true;
    }
}

bool DonghaiConverter::handleMscInput(struct input_event *input)
{
    if (input->value == KEY_CAPSLOCK)
    {
        input->value = KEY_LEFTCTRL;
    }
    m_cached_msc_event = getInputEvent(input->type, input->code, input->value);
    return true;
}

bool DonghaiConverter::handleKeyInput(struct input_event* input)
{
    switch (input->code)
    {
    case KEY_LEFTCTRL:
    case KEY_RIGHTCTRL:
    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT:
    case KEY_LEFTALT:
    case KEY_RIGHTALT:
    case KEY_CAPSLOCK:
        return handleMetaKeyInput(input);
    case KEY_H:
    case KEY_J:
    case KEY_K:
    case KEY_L:
    case KEY_I:
    case KEY_LEFTBRACE:
        return handleSpecialKey(input);
    default:
        leaveNavMode();
        addOutput(m_cached_msc_event);
        addOutput(input);
        break;
    }
    return true;
}

bool DonghaiConverter::handleMetaKeyInput(struct input_event* input)
{
    int bit = m_meta_key_map[input->code];

    if (input->code == KEY_CAPSLOCK)
    {
        input->code = KEY_LEFTCTRL;
        if (input->value == 0)
        {
            leaveNavMode();
        }
    }

    if (input->value == 1)
        m_key_flags |= bit;
    else if (input->value == 0)
        m_key_flags &= ~bit;

    addOutput(m_cached_msc_event);
    addOutput(input);
    return true;
}

void DonghaiConverter::enterNavMode()
{
    if (m_nav_mode)
    {
        return;
    }
    keyRelease(KEY_LEFTCTRL);
    m_nav_mode = true;
}
void DonghaiConverter::leaveNavMode()
{
    if (!m_nav_mode)
    {
        return;
    }

    if (IS_KEY_DOWN(BIT_H))
    {
        m_skip_key_flags |= BIT_H;
        keyRelease(KEY_LEFT);
    }
    if (IS_KEY_DOWN(BIT_J))
    {
        m_skip_key_flags |= BIT_J;
        keyRelease(KEY_DOWN);
    }
    if (IS_KEY_DOWN(BIT_K))
    {
        m_skip_key_flags |= BIT_K;
        keyRelease(KEY_UP);
    }
    if (IS_KEY_DOWN(BIT_L))
    {
        m_skip_key_flags |= BIT_L;
        keyRelease(KEY_RIGHT);
    }
    if (IS_KEY_DOWN(BIT_I))
    {
        m_skip_key_flags |= BIT_I;
        keyRelease(KEY_ESC);
    }
    if (IS_KEY_DOWN(BIT_LEFTBRACE))
    {
        m_skip_key_flags |= BIT_LEFTBRACE;
        keyRelease(KEY_INSERT);
        keyRelease(KEY_LEFTSHIFT);
    }
    keyDown(KEY_LEFTCTRL);
    m_nav_mode = false;
}


bool DonghaiConverter::handleSpecialKey(struct input_event* input)
{
    int bit = m_special_key_map[input->code];

    if(ONLY_CAPSLOCK_ON() && input->value == 1)
    {
        enterNavMode();
    }

    if (input->value == 1)
        m_key_flags |= bit;
    else if (input->value == 0)
        m_key_flags &= ~bit;

    if (!m_nav_mode)
    {
        addOutput(m_cached_msc_event);
        addOutput(input);
        return true;
    }

    switch (input->code)
    {
    case KEY_H:
        addOutput(getInputEvent(EV_MSC, 4, KEY_LEFT));
        outputKey(KEY_LEFT, input->value);
        break;
    case KEY_J:
        addOutput(getInputEvent(EV_MSC, 4, KEY_DOWN));
        outputKey(KEY_DOWN, input->value);
        break;
    case KEY_K:
        addOutput(getInputEvent(EV_MSC, 4, KEY_UP));
        outputKey(KEY_UP, input->value);
        break;
    case KEY_L:
        addOutput(getInputEvent(EV_MSC, 4, KEY_RIGHT));
        outputKey(KEY_RIGHT, input->value);
        break;
    case KEY_I:
        handleNavKeyI(input);
        break;
    case KEY_LEFTBRACE:
        addOutput(getInputEvent(EV_MSC, 4, input->code));
        outputKey(KEY_ESC, input->value);
        break;
    }

    return true;
}

void DonghaiConverter::handleNavKeyI(struct input_event* input)
{
    if (input->value == 1)
    {
        keyDown(KEY_LEFTSHIFT);
        keyDown(KEY_INSERT, true, false);
    }
    else if (input->value == 2)
    {
        addOutput(getInputEvent(EV_MSC, 4, KEY_INSERT));
        outputKey(KEY_INSERT, 2);
    }
    else if (input->value == 0)
    {
        keyRelease(KEY_INSERT);
        keyRelease(KEY_LEFTSHIFT, true, false);
    }
}

void DonghaiConverter::outputKey(unsigned short code, int value)
{
    addOutput(getInputEvent(EV_KEY, code, value));
}

void DonghaiConverter::keyDown(unsigned short code, bool msc, bool syn)
{
    if (msc)
        addOutput(getInputEvent(EV_MSC, 4, code));
    addOutput(getInputEvent(EV_KEY, code, 1));
    if (syn)
        addOutput(getInputEvent(EV_SYN, SYN_REPORT, 0));
}

void DonghaiConverter::keyRelease(unsigned short code, bool msc, bool syn)
{
    if (msc)
        addOutput(getInputEvent(EV_MSC, 4, code));
    addOutput(getInputEvent(EV_KEY, code, 0));
    if (syn)
        addOutput(getInputEvent(EV_SYN, SYN_REPORT, 0));
}

struct input_event * DonghaiConverter::getInputEvent(unsigned short type, unsigned short code, int value)
{
    m_input_buffer_index = (m_input_buffer_index + 1) % MAX_INPUT_BUFFER_SIZE;
    struct input_event * event = &m_input_buffer[m_input_buffer_index];
    event->type = type;
    event->code = code;
    event->value = value;
    return event;
}
