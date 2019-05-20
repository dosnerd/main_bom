#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <alsa/asoundlib.h>
#include <cmath>
#include <Peripherals/Tca8418Interface.h>
#include <linux/spi/spidev.h>


int main() {
//    try {
//        Peripherals::StLedDriver driver;
//        uint8_t i = 0;
//        uint8_t buffer[2] = {0};
//
//
//        while (true) {
//            buffer[0] = Peripherals::Display::To7Segment(i % 10);
//            buffer[1] = Peripherals::Display::To7Segment((i / 10) % 10);
//            driver.SetSegment(5, buffer[0]);
//            driver.SetSegment(4, buffer[1]);
//
//            std::cout << (int) driver.GetCableStates() << std::endl;
//
//            i++;
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//        }
//
//    } catch (const char *err) {
//        std::cerr << err << std::endl;
//    } catch (std::string &err) {
//        std::cerr << err << std::endl;
//    }


    Bom bom;
    bom.WaitForArmed();
    bom.WaitForCountdown();
    bom.CountDown();

    std::cout << "END GAME" << std::endl;
    return 0;
}