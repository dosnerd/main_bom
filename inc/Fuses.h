//
// Created by david on 15-5-19.
//

#ifndef MAIN_BOM_FUSES_H
#define MAIN_BOM_FUSES_H


#include "Config.h"

class Fuses {
public:
                            Fuses();
                            ~Fuses() = default;

public:
    const unsigned          GetActiveFuses() const;
    const unsigned&         GetIncorrectCodes() const;

public:
    void                    SetMinCodes(unsigned nCodes);

public:
    bool                    CheckCode(unsigned code);

private:
    unsigned                m_codes;
    unsigned                m_minLimitCodes;
    unsigned                m_incorrect;
    bool                    m_puzzles[NUMBER_OF_PUZZELS];

private:
    bool                    ValidateCode(unsigned code);
    static bool             CheckChecksum(unsigned idCode, unsigned random, unsigned checksumCode);

    void                    LoadFromFile();
    void                    SaveToFile();
};


#endif //MAIN_BOM_FUSES_H
