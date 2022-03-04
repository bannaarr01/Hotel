#ifndef HOTEL_PAYMENTMANAGER_H
#define HOTEL_PAYMENTMANAGER_H

#include "../ioManager/IoManager.h"
#include "../reservationManager/ReservationManager.h"
#include <set>
#include <algorithm>

class PaymentManager {
private:
    IoManager ioManager;
    static constexpr const char *fileName = "../data/reservations.csv";
    std::set<Reservation> reservationsObjSet;
public:
    void paymentMenu();

    void processPayment(Reservation &reservation);

    void getReservationDetails();
};


#endif //HOTEL_PAYMENTMANAGER_H
