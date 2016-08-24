/*
 * converter.cpp
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#include "converter.h"
#include <unistd.h>
#include <stdio.h>

Converter::Converter()
{
}

Converter::~Converter()
{
}

bool Converter::getOutput(struct input_event ** output)
{
    if (m_output.empty())
        return false;
    *output = m_output.front();
    m_output.pop();
    return true;
}

void Converter::addOutput(struct input_event* output, bool setTime)
{
    if (setTime) {
        gettimeofday(&(output->time), NULL);
        m_output.push(output);
    }
    else {
        m_output.push(output);
    }
}
