#pragma once

#include "studentsdll_global.h"

class STUDENTSDLL_EXPORT Seat {
public:
    Seat();
    Seat(int, int);
    Seat(const Seat &);
    ~Seat();
    inline void setRank(int, int);
    inline int getRank();
    inline int getRow();
    inline int getColumn();
    inline bool operator<(const Seat &other) const {
        return this->rank < other.rank;
    }

private:
    int row, column, rank;
};