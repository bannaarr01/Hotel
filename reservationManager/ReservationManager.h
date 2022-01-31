#ifndef HOTEL_RESERVATIONMANAGER_H
#define HOTEL_RESERVATIONMANAGER_H


#include "../guestManager/GuestManager.h"
#include "../ioManager/IoManager.h"
#include "reservation/Reservation.h"
#include "../roomManager/RoomManager.h"
#include "../paymentManager/PaymentManager.h"
//#include "../exception/AlreadyExistException.h"
//#include "../exception/ErrorOpeningFileException.h"
//#include "../exception/ErrorWritingToFileException.h"
#include <vector>
#include <string>
#include <stdarg.h>


class ReservationManager {
private:
    IoManager ioManager;
    std::string fileName{"../data/reservations.csv"};
    std::string fileName2{"../data/rooms.csv"};
    std::vector<Reservation> reservations;
    Reservation reservation;
    std::vector<Room> roomsObjVec;
    std::vector<Room> result;

public:

    void reservationMenu();

    void chooseAndDisplayRooms();


    std::vector<Room> findAvailableRoom(std::string &roomType, std::string &roomAvailability);

    Room checkRoom(std::string &&roomType, std::string &&roomAvailability);


    Reservation createReservation(std::vector<Room> &rooms, std::vector<Guest> &guests);

    void subUpdateRoom(Room &room, int n = 2);

    void updateReservation(Reservation &reservation);




    //void create();


    std::vector<Reservation> getReservation() const;
//    void initReservationManager(RoomManager, GuestManager);
//
//    std::vector<Reservation> getReservations() const;
//
//    void setReservations(std::vector<Reservation>);
//
//    void reservationCheckIn(); //check in
//    void reservationCheckOut(); //check out
//
//    void changeReservationCreditCard();
//
//    void removeRoomFromReservation();
//
//    void removeGuestFromReservation();

    // printReservation// call reservation to tabular UI




};


#endif //HOTEL_RESERVATIONMANAGER_H
