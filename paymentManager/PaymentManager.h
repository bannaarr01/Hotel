#ifndef HOTEL_PAYMENTMANAGER_H
#define HOTEL_PAYMENTMANAGER_H

#include "../ioManager/IoManager.h"
#include "../reservationManager/ReservationManager.h"
#include <set>
#include <algorithm>

class PaymentManager {
private:
    IoManager ioManager;
    std::set<Reservation> reservationsObjSet;
public:
    void paymentMenu();

    void processPayment(Reservation &reservation);

    void getReservationDetails();
};


#endif //HOTEL_PAYMENTMANAGER_H
