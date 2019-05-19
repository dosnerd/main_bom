//
// Created by david on 18-5-19.
//

#ifndef MAIN_BOM_STLEDDRIVER_H
#define MAIN_BOM_STLEDDRIVER_H


#include "SpiInterface.h"
#include "Gpio.h"

namespace Peripherals {
    class StLedDriver : SpiInterface {
    public:
                                    StLedDriver();
                                    ~StLedDriver() override = default;

    public:
        void                        SetSegment(uint8_t segment, uint8_t value);
        void                        SetLed(uint8_t led, uint8_t value);

    private:
        Peripherals::Gpio           m_writeEnable;
        Peripherals::Gpio           m_readEnable;

    private:
        void                        Setup();
        void                        WriteToMemory(uint8_t address, uint8_t value);
    };
};


#endif //MAIN_BOM_STLEDDRIVER_H
