#pragma once

enum class SeatType {
    REGULAR,
    PREMIUM,
    RECLINER
};

double getSeatTypePrice(SeatType type) {
    switch (type) {
        case SeatType::REGULAR:  return 50.0;
        case SeatType::PREMIUM:  return 80.0;
        case SeatType::RECLINER: return 120.0;
        default: return 50.0;
    }
}
