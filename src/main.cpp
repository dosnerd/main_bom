#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <alsa/asoundlib.h>
#include <cmath>
#include <Peripherals/Tca8418Interface.h>


int main() {
    try {
        Peripherals::TCA8418Interface jumpers;
        while (true) {
            int key = jumpers.CheckKey();
            if (key != -1) {
                std::cout << key << std::endl;
            } else {
                std::cout << "No keys" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const char *err) {
        std::cerr << err << std::endl;
    } catch (std::string &err) {
        std::cerr << err << std::endl;
    }


//    Bom bom;
//    bom.WaitForArmed();
//    bom.WaitForCountdown();
//    bom.CountDown();
//
//    std::cout << "END GAME" << std::endl;
    return 0;
}