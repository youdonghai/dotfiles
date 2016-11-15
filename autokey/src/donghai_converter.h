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


class DonghaiConverter : public Converter {
public:
    DonghaiConverter();

    virtual ~DonghaiConverter();

protected:
    virtual bool handleInput(struct input_event *input);

    bool handleMscInput(struct input_event *input);
    bool handleKeyInput(struct input_event *input);
    bool handleSynInput(struct input_event *input);
    bool isSpecialKey(struct input_event *input) {
        uint16_t key_code = 0;
        if (input->type == EV_KEY) {
            key_code = input->code;
        } else if (input->type == EV_MSC) {
            key_code = (uint16_t) input->value;
        }
        switch (key_code) {
            case KEY_CAPSLOCK:
            case KEY_H:
            case KEY_J:
            case KEY_K:
            case KEY_L:
            case KEY_I:
            case KEY_LEFTBRACE:
                return true;
            default:
                break;
        }
        return false;
    }
    void updateKeyFlags(int *flags, uint16_t key_code, int32_t key_val);
    void setKeyFlags(int *flags, int32_t bit, int32_t key_val);
    void handleCapsLock(struct input_event *key_event);
    void enterDonghaiMode(struct input_event *key_event);
    void leaveDonghaiMode();
    void handleMapKey(struct input_event *key_event, uint16_t map_key_code, int32_t original_bit, int32_t map_bit);
    void handleInsertKey(struct input_event *key_event);
    void normalKeyOutPut(struct input_event *key_event, int32_t bit);

    void addOutput(struct input_event *output, bool setTime = true);

private:
    int m_physic_key_flags;
    int m_logic_key_flags;

    bool m_send_syn_event;
    bool m_donghai_mode;
};

#endif /* DONGHAI_CONVERTER_H_ */
