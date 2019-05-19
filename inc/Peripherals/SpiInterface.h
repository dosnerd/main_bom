//
// Created by david on 1-11-18.
//

#ifndef MWA_SPI_H
#define MWA_SPI_H


#include <cstdint>
#include <string>
#include <mutex>
#include "Config.h"

namespace Peripherals {
    class SpiInterface {
    public:
        explicit            SpiInterface(const std::string& path);
                            SpiInterface(const std::string& path, uint8_t mode);
        virtual             ~SpiInterface();

    public:
        enum                Registers {

        };

    public:
        void                    WriteRaw(uint8_t value);
        void                    WriteRaw(uint8_t *values, uint8_t size);

        uint8_t                 ReadRaw();
        void                    ReadRaw(uint8_t *buffer, uint8_t size);

        virtual void            ReadWriteRaw(uint8_t *txBuffer, uint8_t *rxBuffer, uint8_t size);


    private:
        int                     m_fd;
        uint8_t                 m_buffer[SPI_BUFFER_SIZE];
        uint32_t                m_speed;
        uint8_t                 m_bitsPerWord;
        std::mutex              m_sending;
    };
}


#endif //MWA_SPI_H
