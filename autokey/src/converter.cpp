/*
 * converter.cpp
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#include "converter.h"
#include <cstring>

Converter::Converter() {
    for (int i = 0; i < MAX_INPUT_BUFFER_SIZE; ++i) {
        memset(&m_input_buffer[i], 0x0, sizeof(m_input_buffer[i]));
    }
    m_input_buffer_index = 0;
}

Converter::~Converter() {
}

bool Converter::getOutput(struct input_event **output) {
    if (m_output.empty())
        return false;
    *output = m_output.front();
    m_output.pop();
    return true;
}

void Converter::addOutput(struct input_event *output, bool setTime) {
    if (setTime) {
        gettimeofday(&(output->time), NULL);
        m_output.push(output);
    } else {
        m_output.push(output);
    }
}

struct input_event *Converter::getInputEvent(unsigned short type, unsigned short code, int value) {
    m_input_buffer_index = (m_input_buffer_index + 1) % MAX_INPUT_BUFFER_SIZE;
    struct input_event *event = &m_input_buffer[m_input_buffer_index];
    event->type = type;
    event->code = code;
    event->value = value;
    return event;
}

struct input_event *Converter::getInputEvent(struct input_event *input) {
    m_input_buffer_index = (m_input_buffer_index + 1) % MAX_INPUT_BUFFER_SIZE;
    struct input_event *event = &m_input_buffer[m_input_buffer_index];
    memcpy(event, input, sizeof(struct input_event));
    return event;
}

void Converter::keyDown(unsigned short code, bool msc, bool syn) {
    doKeyEvent(code, 1, msc, syn);
}

void Converter::keyRelease(unsigned short code, bool msc, bool syn) {
    doKeyEvent(code, 0, msc, syn);
}

void Converter::doKeyEvent(unsigned short code, int val, bool msc, bool syn) {
    if (msc)
        addOutput(getInputEvent(EV_MSC, 4, code));
    addOutput(getInputEvent(EV_KEY, code, val));
    if (syn)
        addOutput(getInputEvent(EV_SYN, SYN_REPORT, 0));
}
