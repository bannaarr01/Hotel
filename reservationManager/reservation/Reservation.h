#ifndef HOTEL_RESERVATION_H
#define HOTEL_RESERVATION_H


#include "../../interface/IPrintable.h"
#include "../../guestManager/guest/Guest.h"
#include "../../roomManager/room/Room.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>
#include <string>

class Reservation : public IPrintable {
public:
    enum ReservationStatus {
        CONFIRMED, WAIT_LIST, CHECKED_IN, EXPIRED
    };

    Reservation() {}

    Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                int adultCount, int childrenCount, Guest &guest);

    std::string getReservationNumber() const;

    std::string getCheckInDate() const;

    Guest getGuestDetails() const;

    virtual void print(std::ostream &os) const override;

    virtual ~Reservation() = default;

private:
    boost::uuids::uuid u = boost::uuids::random_generator()();
    std::string reservationNumber;
    std::string checkInDate;
    std::string checkOutDate;
    int adultCount;
    int childrenCount;
    ReservationStatus reservationStatus;
    bool isCreditCardBilled;
    bool hasPaid;
    std::vector<Guest> guests;
    std::vector<Room> rooms;
    Guest guest;
    Room room;
};


#endif //HOTEL_RESERVATION_H
