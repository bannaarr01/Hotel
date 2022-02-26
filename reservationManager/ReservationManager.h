#ifndef HOTEL_RESERVATIONMANAGER_H
#define HOTEL_RESERVATIONMANAGER_H


#include "../guestManager/GuestManager.h"
#include "../ioManager/IoManager.h"
#include "../ui/UI.h"
#include "reservation/Reservation.h"
#include "../roomManager/RoomManager.h"
#include "ManageOverlap.h"
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
#include <map>


class ReservationManager {
private:
    IoManager ioManager;
    //UI ui;
    rsd::ReservedDate rsvDates;
    std::string fileName{"../data/reservations.csv"};
    std::string fileName2{"../data/rooms.newformat"};
    std::vector<Reservation> reservations;
    std::set<Reservation> reservationsObjSet;
    Reservation reservation;
    std::vector<Room> roomsObjVec;
    std::vector<Room> result;
    std::set<Guest> guestObjSet;

public:

    void reservationMenu();

    std::map<std::string, std::string> checkRoomDates(Room &room);

    void chooseAndDisplayRooms();


    std::vector<Room> findAvailableRoom(std::string &roomType, std::string &roomAvailability);

    Room checkRoom(std::string &&roomType, std::string &&roomAvailability);


//    Reservation initReservation(Room &room, Guest &guest, std::string &checkInDate, std::string &checkOutDate,
//                                int &adultCount, int &childrenCount);

    void subUpdateRoom(Room &room, std::string &checkInDate, std::string &checkOutDate);

    Guest existingGuest();

    bool checkOverlap(Room &room, std::string &checkInDate, std::string &checkOutDate);

    std::set<Reservation>
    getGuestReservation(Guest &guest, std::set<Reservation> &reservationsObjSt);

    bool copyCsvToReservationsObjSet(std::set<Reservation> &reservationsObjSt);

    void createReservation(Room &room, Guest &guest, int &numOfRooms, std::string &checkInDate,
                           std::string &checkOutDate,
                           int &adultCount, int &childrenCount, bool &done);

    void manageReservation();

    void confirmReservationStatus();

    void changeReservationPaymentStatus();

    void updateReservation(Reservation &reservation);


    void updateReservationCreditCard();

    void updateReservationRoom();

    void updateReservationGuestInfo();

//    void reservationCheckIn(); //check in
//    void reservationCheckOut(); //check out

    void pintExpiredReservations() const;

    void printReservations() const;


};


#endif //HOTEL_RESERVATIONMANAGER_H
