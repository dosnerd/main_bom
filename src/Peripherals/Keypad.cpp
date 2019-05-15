//
// Created by david on 14-5-19.
//

#include <iostream>
#include <limits>
#include "Peripherals/Keypad.h"


bool Peripherals::Keypad::Check() {
    return SimulateCheck();
}

Peripherals::Keypad::Key Peripherals::Keypad::GetKey() {
    return SimulateKey();
}

bool Peripherals::Keypad::SimulateCheck() {
    return std::cin.peek() != EOF;
}

Peripherals::Keypad::Key Peripherals::Keypad::SimulateKey() {
    std::string key;
    std::cin >> key;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    if (key == "0") return KEY0;
    if (key == "1") return KEY1;
    if (key == "2") return KEY2;
    if (key == "3") return KEY3;
    if (key == "4") return KEY4;
    if (key == "5") return KEY5;
    if (key == "6") return KEY6;
    if (key == "7") return KEY7;
    if (key == "8") return KEY8;
    if (key == "9") return KEY9;
    if (key == "*") return KEY_ASTERISK;
    if (key == "#") return KEY_HASH_TAG;

    return NONE;
}
