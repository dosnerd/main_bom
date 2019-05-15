//
// Created by david on 14-5-19.
//

#ifndef MAIN_BOM_KEYPAD_H
#define MAIN_BOM_KEYPAD_H


namespace Peripherals {
    class Keypad {
    public:
                            Keypad() = default;
                            ~Keypad() = default;

    public:
        enum Key {
            NONE,
            KEY1,
            KEY2,
            KEY3,
            KEY4,
            KEY5,
            KEY6,
            KEY7,
            KEY8,
            KEY9,
            KEY0,
            KEY_ASTERISK,
            KEY_HASH_TAG
        };

    public:
        bool                Check();
        enum Key            GetKey();

    private:
        static bool         SimulateCheck();
        enum Key            SimulateKey();
    };
};


#endif //MAIN_BOM_KEYPAD_H
