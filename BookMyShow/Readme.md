# BookMyShow - Movie Ticket Booking System

## Overview
A simple C++ low-level design for a movie ticket booking service. It models movies, cinemas, shows, seats, users, bookings, pricing strategies, and notifications using common design patterns.

## Key Components
- `MovieBookingDemo.cpp` - entry point demonstrating booking flow and user notifications.
- `MovieBookingService.hpp` - singleton service for adding cities, movies, cinemas, shows, and users.
- `Entity/` - core domain objects like `Movie`, `Cinema`, `Screen`, `Show`, `Seat`, `Booking`, and `User`.
- `Enums/` - status and type enums such as `SeatType`, `SeatStatus`, and `PaymentStatus`.
- `Observer/` - observer pattern implementation for movie notifications.
- `Strategy/` - pricing and payment strategies.
- `SeatLockManager.hpp` and `BookingManager.hpp` - seat locking and booking coordination.

## Design Patterns Used
- Singleton: `MovieBookingService` ensures one shared service instance.
- Strategy: pricing and payment behaviors are pluggable through `PricingStrategy` and `PaymentStrategy` abstractions.
- Observer: `MovieSubject` / `MovieObserver` support user notifications for movie availability.
- Builder: `BookingBuilder` in `Entity/Booking.hpp` is used by `BookingManager` to construct `Booking` objects cleanly.

## Booking Flow
1. Create cities, movies, screens, seats, and cinemas.
2. Add shows for movies with a pricing strategy.
3. Create a user and attach an observer to the movie.
4. Search for shows, view available seats, lock and book seats.
5. Payment is handled through a concrete payment strategy.

## Notable Features
- Support for `REGULAR`, `PREMIUM`, and `RECLINER` seat types.
- Seat locking with timeout to simulate reservation hold behavior.
- Modular pricing strategies for weekday/weekend pricing.
- Notification support when a movie becomes available.

## How to Build
From the `BookMyShow` folder:

```bash
g++ -std=c++17 MovieBookingDemo.cpp -o MovieBookingDemo
```

Then run:

```bash
./MovieBookingDemo
```

## Notes
- The current demo focuses on architecture and basic booking flow rather than a complete production system.
- Memory management uses raw pointers, so extending this project with smart pointers would improve safety.
- The sample output includes available seats, booking success, and seat status after booking.
