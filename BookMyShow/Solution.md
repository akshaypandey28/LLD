# Movie Ticket Booking System (LLD)

## Problem Statement

Design and implement a C++ Movie Ticket Booking System that allows users to book movie tickets, select seats, manage shows, and handle theater scheduling. The system should support movies, cinemas, screens, shows, seats, bookings, payments, and pricing strategies.

---

## Requirements

1. **Movie Management:**
   - Store movie information (ID, title, duration)
   - Manage movie schedules and shows
   - Track movie availability and notifications

2. **Cinema and Theater Management:**
   - Manage cinema information (name, location)
   - Handle multiple screens per cinema
   - Track screen capacity and available seats

3. **Show Management:**
   - Schedule shows for movies on specific screens
   - Manage show timings and pricing strategy
   - Report available shows and seat availability

4. **Seat Management:**
   - Track seat availability and status
   - Handle seat selection and booking
   - Manage different seat types: Regular, Premium, Recliner

5. **Booking Management:**
   - Process ticket bookings with payment
   - Handle booking confirmation and cancellation
   - Maintain booking history and status

---

## Core C++ Entities

### 1. MovieTicketBookingSystem
- **Fields:** `vector<Movie*> movies`, `vector<Cinema*> cinemas`, `vector<Show*> shows`, `vector<Booking*> bookings`
- **Methods:**
  - `addMovie(int id, const string& title, int duration)`
  - `addCinema(const string& name, const string& location)`
  - `addShow(int id, Movie* movie, Screen* screen, const string& startTime, PricingStrategy* pricingStrategy)`
  - `bookTicket(User* user, Show* show, vector<Seat*> seats, Payment* payment)`
  - `cancelBooking(Booking* booking)`
  - `getAvailableShows(Movie* movie)`

### 2. Movie
- **Fields:** `int id`, `string title`, `int durationInMinutes`
- **Methods:**
  - `const int& getId() const`
  - `const string& getTitle() const`
  - `int getDurationInMinutes() const`

### 3. Cinema
- **Fields:** `int id`, `string name`, `string location`, `vector<Screen*> screens`
- **Methods:**
  - `void addScreen(Screen* screen)`
  - `const vector<Screen*>& getScreens() const`
  - `int getCapacity() const`

### 4. Screen
- **Fields:** `int id`, `vector<Seat*> seats`
- **Methods:**
  - `void addSeat(Seat* seat)`
  - `const vector<Seat*>& getSeats() const`

### 5. Show
- **Fields:** `int id`, `Movie* movie`, `Screen* screen`, `string startTime`, `PricingStrategy* pricingStrategy`
- **Methods:**
  - `Movie* getMovie() const`
  - `Screen* getScreen() const`
  - `const string& getStartTime() const`
  - `PricingStrategy* getPricingStrategy() const`

### 6. User
- **Fields:** `int id`, `string name`, `string email`
- **Methods:**
  - `const int& getId() const`
  - `const string& getName() const`
  - `const string& getEmail() const`

### 7. Seat
- **Fields:** `int id`, `int row`, `int col`, `SeatType type`, `SeatStatus status`
- **Methods:**
  - `SeatType getType() const`
  - `SeatStatus getStatus() const`
  - `void setStatus(SeatStatus s)`

### 8. Booking
- **Fields:** `int id`, `User* user`, `vector<Seat*> seats`, `Show* show`, `Payment* payment`, `double totalAmount`
- **Methods:**
  - `void confirmBooking()`
  - `const vector<Seat*>& getSeats() const`
  - `Payment* getPayment() const`
  - `double getTotalAmount() const`

### 9. Payment
- **Fields:** `int id`, `double amount`, `PaymentStatus status`
- **Methods:**
  - `double getAmount() const`
  - `PaymentStatus getStatus() const`

### 10. Pricing Strategy
- **Abstract:** `PricingStrategy`
- **Concrete:** `WeekdayPricingStrategy`, `WeekendPricingStrategy`
- **Methods:**
  - `double calculatePrice(const vector<Seat*>& seats) override`

---

## Example C++ Usage

```cpp
MovieTicketBookingSystem* system = MovieTicketBookingSystem::getInstance();

Movie* movie = system->addMovie(1, "Inception", 148);
Cinema* cinema = system->addCinema("Cineplex Downtown", "Downtown");
Screen* screen = new Screen(1);

// add seats to screen
screen->addSeat(new Seat(101, 0, 0, SeatType::REGULAR));
// ...

cinema->addScreen(screen);
PricingStrategy* pricing = new WeekdayPricingStrategy();
Show* show = system->addShow(1, movie, screen, "10:00 AM", pricing);

User* user = new User("John Doe", "john@example.com");
vector<Seat*> seats = {screen->getSeats()[0], screen->getSeats()[1]};
Payment* payment = new Payment(1, 300.0, PaymentStatus::COMPLETED);
Booking* booking = system->bookTicket(user, show, seats, payment);
```

---

## Demo

The demo is implemented in `MovieBookingDemo.hpp` and shows:
- creating movies, cinemas, screens, seats, and shows
- booking seats with payment
- canceling a booking
- checking available shows and seat availability

---

## Extending the C++ Framework

- Add a payment gateway integration for real payment processing
- Add a seat selection UI or console menu
- Add dynamic pricing tiers and discounts
- Add advanced show scheduling and theater management
- Add user notifications and review submission

---

## Design Patterns Used

- **Singleton Pattern:** `MovieTicketBookingSystem`
- **Builder Pattern:** `BookingBuilder`
- **Observer Pattern:** `MovieSubject` / `MovieObserver`
- **Strategy Pattern:** `PricingStrategy`

---

## Exception Handling (Planned)

- `SeatNotAvailableException` when booking an unavailable seat
- `InvalidShowException` for invalid show selection
- `BookingFailedException` when booking creation fails
- `CancellationFailedException` when cancellation cannot complete

---