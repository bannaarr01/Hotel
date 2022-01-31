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
        WAIT_LIST = 1, CONFIRMED = 2, CHECKED_IN = 3, EXPIRED = 4
    };

    Reservation() {}

//    Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
//                int adultCount, int childrenCount, Guest &guest);


    Reservation(std::vector<Room> &rooms, std::string checkInDate, std::string checkOutDate,
                int adultCount, int childrenCount, std::vector<Guest> &guests);

    std::string getReservationNumber() const;

    std::string getCheckInDate() const;

    std::vector<Guest> getGuests() const;

    std::vector<Room> getRooms() const;

    ReservationStatus getReservationStatus() const;

    void addRoom(Room &room);

    bool operator==(const Reservation &rhs) const;

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
//    Guest guest;
//    Room room;
};


#endif //HOTEL_RESERVATION_H
