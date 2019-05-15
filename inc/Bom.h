//
// Created by david on 22-4-19.
//

#ifndef MAIN_BOM_BOM_H
#define MAIN_BOM_BOM_H


#include <Peripherals/Display.h>
#include <Peripherals/Keypad.h>

class Bom {
public:
    explicit                        Bom();
                                    ~Bom() = default;

public:
    void                            WaitForArmed();
    void                            WaitForCountdown();
    void                            CountDown();

private:
    unsigned                        m_startTime;
    time_t                          m_start;
    unsigned                        m_duration;
    Peripherals::Display            m_display;
    Peripherals::Keypad             m_keypad;
    std::string                     m_file;
    bool                            m_displayError;

    int                             m_userInput[6];
    bool                            m_userInputActive;

private:
    void                            SetCountdown(int h, int m, int s);
    void                            SetStartTime(int h, int m, int s);
    void                            DisplayUpdater(time_t end);
    int*                            ExtractTime(int *buffer, int time, int &ms);

    void                            SearchBomFile(AssembleConnection &connection, const std::string& moveTo = "./tmp.bom");
    std::string                     SearchInDir(const std::string &dirName);

    void                            AssembleError(AssembleConnection &connection);

    int*                            Encrypt(int *data, int *buffer);

    bool                            HasExtension(char *filename);

    AssembleConnection &            DisplayTime(AssembleConnection &connection, int *buffer);
    void                            ReadKeyPad();
};


#endif //MAIN_BOM_BOM_H
