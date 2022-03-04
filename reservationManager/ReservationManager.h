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
    // rsd::ReservedDate rsvDates;
    std::string fileName{"../data/reservations.csv"};
    std::string fileName2{"../data/rooms.newformat"};
    std::vector<Reservation> reservations;
    std::set<Reservation> reservationsObjSet;
    Reservation reservation;
    std::vector<Room> roomsObjVec;
    std::vector<Room> result;
    std::set<Guest> guestObjSet;

public:
    enum GuestCount {
        VIP_ADULT_MAX = 4, VIP_CHILDREN_MAX = 2,
        DELUXE_ADULT_MAX = 3, DELUXE_CHILDREN_MAX = 2,
        DOUBLE_ADULT_MAX = 2, DOUBLE_CHILDREN_MAX = 2,
        SINGLE_ADULT_MAX = 2, SINGLE_CHILDREN_MAX = 1
    };
    static constexpr const char *DEF_ADULT = "ADULTS";
    static constexpr const char *DEF_CHILDREN = "CHILDREN";
    static constexpr const char *DEF_VIP = "VIP";
    static constexpr const char *DEF_DELUXE = "DELUXE";
    static constexpr const char *DEF_DOUBLE = "DOUBLE";
    static constexpr const char *DEF_SINGLE = "SINGLE";
    static constexpr const char *DEF_STATUS_VACANT = "Vacant";
    static constexpr const char *DEF_CHECK_IN_DATE = "checkInDate";
    static constexpr const char *DEF_CHECK_OUT_DATE = "checkOutDate";

    ReservationManager() = default;

    void reservationMenu();

    std::map<std::string, std::string> checkRoomDates(Room &room);

    void chooseAndDisplayRooms();


    std::vector<Room> findAvailableRoom(std::string &roomType, std::string &roomAvailability);

    Room checkRoom(std::string &&roomType, std::string &&roomAvailability);

    void subUpdateRoom(Room &room, std::string &checkInDate, std::string &checkOutDate);

    Guest existingGuest();

    bool checkOverlap(Room &room, std::string &checkInDate, std::string &checkOutDate);

    std::set<Reservation>
    getGuestReservation(Guest &guest, std::unique_ptr<std::set<Reservation>> rsvObjSet = nullptr);

    bool copyCsvToReservationsObjSet(std::set<Reservation> *rsvObjSet = nullptr);

    void createReservation(Room &room, Guest &guest, int &numOfRooms, std::string &checkInDate,
                           std::string &checkOutDate,
                           int &adultCount, int &childrenCount, bool &done);

    void manageReservation();

    std::vector<Reservation>
    findReservation(std::string &rsvId, std::unique_ptr<std::set<Reservation>> rsvObjSet = nullptr);

    void confirmReservationStatus();

    void changeReservationPaymentStatus();

    void updateReservation(Reservation &reservation);


    void updateReservationCreditCard();

    void updateReservationRoom();

    void updateReservationGuestInfo();

//    void reservationCheckIn(); //check in
//    void reservationCheckOut(); //check out

    void pintExpiredReservations() const;

    void printReservations();


};


#endif //HOTEL_RESERVATIONMANAGER_H
