#ifndef HOTEL_RESERVATION_H
#define HOTEL_RESERVATION_H


#include "../../interface/IPrintable.h"
#include "../../guestManager/guest/Guest.h"
#include "../../roomManager/room/Room.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>
#include <string>

static boost::uuids::uuid u = boost::uuids::random_generator()();

class Reservation : public IPrintable {
public:
    enum ReservationStatus {
        WAIT_LIST = 1, CONFIRMED = 2, CHECKED_IN = 3, EXPIRED = 4
    };

    Reservation() = default;

    Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                int adultCount, int childrenCount, Guest &guest, bool isCreditCardBilled = false,
                bool hasPaid = false, ReservationStatus reservationStatus = Reservation::ReservationStatus::WAIT_LIST,
                std::string reservationNumber = boost::uuids::to_string(u));


//    Reservation(std::vector<Room> &rooms, std::string checkInDate, std::string checkOutDate,
//                int adultCount, int childrenCount, std::vector<Guest> &guests);

    std::string getReservationNumber() const;

    std::string getCheckInDate() const;

//    std::vector<Guest> getGuests() const;
    Guest getGuest() const;

//    std::vector<Room> getRooms() const;
    Room getRoom() const;

    ReservationStatus getReservationStatus() const;

    void addRoom(Room &room);

    std::string reservationStatusToString(Reservation::ReservationStatus reservationStatus) const;

    bool operator==(const Reservation &rhs) const;

    virtual void print(std::ostream &os) const override;

    bool operator<(const Reservation &rhs) const;

    virtual ~Reservation() = default;

private:
    std::string reservationNumber;
    std::string checkInDate;
    std::string checkOutDate;
    int adultCount;
    int childrenCount;
    ReservationStatus reservationStatus;
    bool isCreditCardBilled;
    bool hasPaid;
//    std::vector<Guest> guests;
//    std::vector<Room> rooms;
    Guest guest;
    Room room;
};


#endif //HOTEL_RESERVATION_H
