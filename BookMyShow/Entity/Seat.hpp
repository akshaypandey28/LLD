#pragma once

#include <string>
#include "../Enums/SeatStatus.hpp"
#include "../Enums/SeatType.hpp"

using namespace std;

class Seat {
private:
    int id;
    int row;
    int col;
    SeatType type;
    SeatStatus status;

public:
    Seat(const int& id, int row, int col, SeatType type) {
        this->id = id;
        this->row = row;
        this->col = col;
        this->type = type;
        this->status = SeatStatus::AVAILABLE;
    }

    const int& getId() const {
        return id;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    SeatType getType() const {
        return type;
    }

    SeatStatus getStatus() const {
        return status;
    }

    void setStatus(SeatStatus s) {
        this->status = s;
    }
};
