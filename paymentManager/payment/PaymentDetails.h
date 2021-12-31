#ifndef HOTEL_PAYMENTDETAILS_H
#define HOTEL_PAYMENTDETAILS_H

#include "../../ioManager/IoManager.h"
#include "../../roomManager/RoomManager.h"
#include "../../reservationManager/ReservationManager.h"
#include <string>
#include <vector>


class PaymentDetails {
private:
    std::string checkInDate;
    std::string checkOutDate;
    bool isCreditCardBilled;
    std::vector<Room> rooms;
    std::string ccNumber;
    int daysStayed;
    int weekDayCount;
    int weekendCount;
    std::shared_ptr<RoomType> roomTypePtr;
    std::vector<std::string> roomTypeBookedName;

public:
    void retrieveRawDetails(Reservation);

    void processNewDetails(Reservation);

    std::string getCheckInDate() const;

    void setCheckInDate(std::string);

    std::string getCheckOutDate() const;

    void setCheckOutDate(std::string);

    bool getIsCreditCardBilled() const;

    void IsCreditCardBilled(bool);

    std::vector<Room> getRooms() const;

    void setRooms(std::vector<Room>);

    std::string getCcNumber() const;

    void setCcNumber(std::string);

    int getDaysStayed() const;

    void setDaysStayed(int);

    int getWeekDayCount() const;

    void setWeekDayCount(int);

    int getWeekendCount() const;

    void setWeekendCount(int);

    std::shared_ptr<RoomType> getRoomTypePtr();

    void setRoomTypePtr(std::shared_ptr<RoomType>);

    std::vector<std::string> getRoomTypeBookedName() const;

    void setRoomTypeBookedName(std::vector<std::string>);

};


#endif //HOTEL_PAYMENTDETAILS_H
