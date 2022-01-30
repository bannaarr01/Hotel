
#include "Reservation.h"

Reservation::Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                         int adultCount, int childrenCount, Guest &guest)
        : room{room}, checkInDate{checkInDate}, checkOutDate{checkOutDate}, adultCount{adultCount},
          childrenCount{childrenCount}, guest{guest} {
    reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
    reservationStatus = Reservation::ReservationStatus::WAIT_LIST;
}


void Reservation::print(std::ostream &os) const {
    os << reservationNumber << "," << room << "," << checkInDate << "," << checkOutDate << "," << reservationStatus
       << "," << adultCount
       << "," << childrenCount << "," << guest;
}

std::string Reservation::getReservationNumber() const {
    return reservationNumber;
}

std::string Reservation::getCheckInDate() const {
    return checkInDate;
}

Guest Reservation::getGuestDetails() const {
    return guest;
}

Reservation::ReservationStatus Reservation::getReservationStatus() const {
    return reservationStatus;
}


Reservation::Reservation(std::vector<Room> &rooms, std::string checkInDate, std::string checkOutDate, int adultCount,
                         int childrenCount, Guest &guest) : rooms{rooms}, checkInDate{checkInDate},
                                                            checkOutDate{checkOutDate}, adultCount{adultCount},
                                                            childrenCount{childrenCount}, guest{guest} {
    reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
    reservationStatus = Reservation::ReservationStatus::WAIT_LIST;
}


