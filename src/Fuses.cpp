//
// Created by david on 15-5-19.
//

#include <fstream>
#include "Fuses.h"

#define FILTER_ID			0b110011001100u
#define FILTER_RANDOM		0b001000100010u
#define FILTER_CHECKSUM		0b000100010001u

Fuses::Fuses()
    : m_codes(0), m_minLimitCodes(NUMBER_OF_PUZZELS), m_incorrect(0), m_puzzles{false}
{
    LoadFromFile();
}


const unsigned Fuses::GetActiveFuses() const {
    return
            (m_minLimitCodes - (m_codes - m_incorrect));
}

const unsigned& Fuses::GetIncorrectCodes() const{
    return m_incorrect;
}

void Fuses::SetMinCodes(unsigned nCodes) {
    m_minLimitCodes = nCodes;
}

bool Fuses::CheckCode(unsigned code) {
    m_codes++;
    if (!ValidateCode(code)) {
        m_incorrect++;
        SaveToFile();
        return false;
    }

    SaveToFile();
    return true;
}

bool Fuses::ValidateCode(unsigned code) {
    unsigned idCode = code & FILTER_ID;
    unsigned random = code & FILTER_RANDOM;
    unsigned checksum = code & FILTER_CHECKSUM;
    unsigned idLower = idCode &  0b000000001100u;
    unsigned idMiddle = idCode & 0b000011000000u;
    unsigned idUpper = idCode &  0b110000000000u;
    unsigned id = (idUpper >> 6u) | (idMiddle >> 4u) | (idLower >> 2u);

    if (!CheckChecksum(idCode, random, checksum)) {
        return false;
    }
    if (m_puzzles[id]) {
        return false; // Puzzle already done
    }

    m_puzzles[id] = true;
    return true;
}

bool Fuses::CheckChecksum(unsigned idCode, unsigned random, unsigned checksumCode) {
    unsigned correctChecksum;
    idCode >>= 2u;
    random >>= 1u;

    correctChecksum = ~(idCode + random);
    correctChecksum = correctChecksum & FILTER_CHECKSUM;

    return correctChecksum == checksumCode;
}

void Fuses::LoadFromFile() {
    std::ifstream file("./fuses");
    unsigned nPuzzles;

    if (!file) return;

    file >> m_codes;
    file >> m_minLimitCodes;
    file >> m_incorrect;
    file >> nPuzzles;

    if (nPuzzles != NUMBER_OF_PUZZELS) return;
    for (bool &m_puzzle : m_puzzles) {
        file >> m_puzzle;
    }
}

void Fuses::SaveToFile() {
    std::ofstream file("./fuses");
    file << m_codes << std::endl;
    file << m_minLimitCodes << std::endl;
    file << m_incorrect << std::endl;
    file << NUMBER_OF_PUZZELS << std::endl;
    for (bool m_puzzle : m_puzzles) {
        file << m_puzzle << std::endl;
    }
}
