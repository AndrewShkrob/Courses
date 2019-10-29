#pragma once

#include <memory>

namespace RAII {
    template <class Provider>
    class Booking {
    private:
        int booking_id;
        Provider *booking_provider;
    public:
        Booking(Provider *provider, int id) : booking_id(id), booking_provider(provider) {}

        Booking(const Booking &) = delete;

        Booking(Booking &&booking) {
            *this = std::move(booking);
        }

        Booking &operator=(const Booking &) = delete;

        Booking &operator=(Booking &&booking) {
            booking_id = booking.booking_id;
            booking_provider = booking.booking_provider;
            booking.booking_provider = nullptr;
            return *this;
        }

        ~Booking() {
            if (booking_provider)
                booking_provider->CancelOrComplete(*this);
        }
    };
}