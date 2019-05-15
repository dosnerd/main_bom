#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>

int main() {
    Bom bom;
    bom.WaitForArmed();
    bom.WaitForCountdown();
    bom.CountDown();

    std::cout << "END GAME" << std::endl;
    return 0;
}