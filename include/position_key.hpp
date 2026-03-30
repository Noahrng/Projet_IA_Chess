#ifndef POSITION_KEY_HPP
#define POSITION_KEY_HPP

#include <cstdint>
#include <array>

struct PositionKey
{
    // 64 cases × 4 bits = 256 bits = 4 × uint64_t
    // Chaque case encode : 0=vide, 1-6=blanc, 7-12=noir
    std::array<uint64_t, 4> data;
    bool white_turn;

    bool operator==(const PositionKey& other) const
    {
        return data == other.data && white_turn == other.white_turn;
    }
};

#endif