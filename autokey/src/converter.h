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

const int MAX_INPUT_BUFFER_SIZE = 100;

class Converter {
public:
    Converter();

    virtual ~Converter();

    bool addInput(struct input_event *input) {
        return handleInput(input);
    }

    bool getOutput(struct input_event **output);

protected:
    virtual bool handleInput(struct input_event *input) = 0;

    virtual void addOutput(struct input_event *output, bool setTime = true);

    struct input_event *getInputEvent(unsigned short type, unsigned short code, int value);
    struct input_event *getInputEvent(struct input_event *input);
    void keyDown(unsigned short code, bool msc = true, bool syn = true);
    void keyRelease(unsigned short code, bool msc = true, bool syn = true);
    void doKeyEvent(unsigned short code, int val, bool msc = true, bool syn = true);

private:
    std::queue<struct input_event *> m_output;

    struct input_event m_input_buffer[MAX_INPUT_BUFFER_SIZE];
    int m_input_buffer_index;
};

#endif /* CONVERTER_H_ */
