/*
 * donghai_converter.h
 *
 *  Created on: 24 Dec, 2015
 *      Author: youdonghai
 */

#ifndef DONGHAI_CONVERTER_H_
#define DONGHAI_CONVERTER_H_

#include <set>
#include <map>
#include "converter.h"
#include "stdlib.h"

const int MAX_INPUT_BUFFER_SIZE = 100;

class DonghaiConverter : public Converter
{
public:
    DonghaiConverter();
    virtual ~DonghaiConverter();

protected:
    virtual bool handleInput(struct input_event* input);
    bool handleKeyInput(struct input_event* input);
    bool handleMscInput(struct input_event* input);
    bool handleMetaKeyInput(struct input_event* input);
    bool handleSpecialKey(struct input_event* input);
    void handleNavKeyI(struct input_event* input);
    void enterNavMode();
    void leaveNavMode();

    void outputKey(unsigned short code, int value);
    void keyDown(unsigned short code, bool msc = true, bool syn = true);
    void keyRelease(unsigned short code, bool msc = true, bool syn = true);

private:

    int m_key_flags;
    bool m_nav_mode;
    int m_skip_key_flags;

    struct input_event m_input_buffer[MAX_INPUT_BUFFER_SIZE];
    int m_input_buffer_index;
    struct input_event * m_cached_msc_event;

    struct input_event * getInputEvent(unsigned short type, unsigned short code, int value);

    std::map<int32_t, int> m_meta_key_map;
    std::map<int32_t, int> m_special_key_map;
};

#endif /* DONGHAI_CONVERTER_H_ */
