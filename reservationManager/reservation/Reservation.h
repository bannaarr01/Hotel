#ifndef HOTEL_RESERVATION_H
#define HOTEL_RESERVATION_H

#include "../../interface/IPrintable.h"
#include "../../roomManager/RoomManager.h"
#include "../../guestManager/GuestManager.h"
//#include <ctime>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

class Reservation : public IPrintable {
public:
    enum ReservationStatus {
        CONFIRMED, WAIT_LIST, CHECKED_IN, EXPIRED
    };

    Reservation() = default;

    Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                int adultCount, int childrenCount, Guest &guest);

    std::string getReservationNumber() const;

//    void setReservationNumber(std::string);

    std::string getCheckInDate() const;

    void setCheckInDate(std::string);

    std::string getCheckOutDate() const;

    void setCheckOutDate(std::string);

    int getAdultCount() const;

    void setAdultCount(int);

    int geChildrenCount() const;

    void setChildrenCount(int);

    ReservationStatus getReservationStatus() const;

    void getReservationStatus(ReservationStatus);

    bool getIsCreditCardBilled() const;

    void setCreditCardBilled(bool);

    bool getHasPaid() const;

    void setHasPaid(bool);

    std::vector<Guest> getGuests() const;

    void setGuests(std::vector<Guest> &);

    std::vector<Room> getRooms() const;

    void setRooms(std::vector<Room> &);

//    std::vector<std::string> getRoomNumber();

//    CreditCardDetails getCreditCardDetails();

//    void setCreditCardDetails(CreditCardDetails);

//    bool getCreditCardBilled() const;

//    void setCreditCardBilled(CreditCardDetails);

    void removeRoom();

    Guest addGuest();

//    void removeGuest(Guest);

    virtual void print(std::ostream &os) const override;

    auto updateReservation() {
        return [this](Room::RoomAvailabilityStatus newRoomAvailabilityStatus, double newPrice,
                      bool newIsWifi, std::string newCheckInDate, std::string newCheckOutDate,
                      int newAdultCount, int newChildrenCount) {

            auto roomUpdate = room.updateRoomDetails();
            roomUpdate(newRoomAvailabilityStatus, newPrice, newIsWifi); //updating room
            checkInDate = newCheckInDate;
            checkOutDate = newCheckOutDate;
            adultCount = newAdultCount;

//            std::string newAddress, std::string newCountry, std::string newContact,
//                std::string newHolderName, std::string newCcNumber, std::string newExpiryDate,
//                std::string newCVV
//            //updating guest details
//            auto guestUpdate = guest.changeGuestDetails();
//            guestUpdate(newAddress, newCountry, newContact);
//
//            //Updating guest CC
//            auto guestUpdateCC = guest.changeGuestCcDetails();
//            guestUpdateCC(newHolderName, newCcNumber, newExpiryDate, newCVV);


        };
    }


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
