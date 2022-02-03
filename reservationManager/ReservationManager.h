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
#include <set>
#include <iterator>
#include <algorithm>
#include <boost/range/adaptors.hpp>


class ReservationManager {
private:
    IoManager ioManager;
    std::string fileName{"../data/reservations.csv"};
    std::string fileName2{"../data/rooms.csv"};
    std::vector<Reservation> reservations;
    std::set<Reservation> reservationsObjSet;
    Reservation reservation;
    std::vector<Room> roomsObjVec;
    std::vector<Room> result;
    std::set<Guest> guestObjSet;

public:

    void reservationMenu();

    void chooseAndDisplayRooms();


    std::vector<Room> findAvailableRoom(std::string &roomType, std::string &roomAvailability);

    Room checkRoom(std::string &&roomType, std::string &&roomAvailability);


    Reservation createReservation(Room &room, Guest &guest);

    void subUpdateRoom(Room &room, int n = 3);

    void updateReservation(Reservation &reservation);

    Guest existingGuest();

    std::set<Reservation>
    getGuestReservation(Guest &guest, std::set<Reservation> &reservationsObjSet);

    bool copyCsvToReservationsObjSet(std::set<Reservation> &reservationsObjSet);

    void createReservation(Room &room, Guest &guest, int &numOfRooms, bool &done);

    //void create();


    // std::vector<Reservation> getReservation() const;
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
