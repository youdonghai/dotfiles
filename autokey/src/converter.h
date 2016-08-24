/*
 * converter.h
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <linux/input.h>
#include <queue>

class Converter
{
public:
    Converter();
    virtual ~Converter();

    bool addInput(struct input_event* input) {
        return handleInput(input);
    }

    bool getOutput(struct input_event ** output);

protected:
    virtual bool handleInput(struct input_event* input) = 0;
    void addOutput(struct input_event* output, bool setTime = true);

private:
    std::queue<struct input_event *> m_output;
};

#endif /* CONVERTER_H_ */
