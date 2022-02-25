
#include "ReservedDate.h"

void rsd::ReservedDate::from_json(const json &j, rsd::ReservedDate &rsvDate) {
    j.at("checkInDate").get_to(rsvDate.checkInDate);
    j.at("checkOutDate").get_to(rsvDate.checkOutDate);
}

void rsd::ReservedDate::to_json(json &j, const rsd::ReservedDate &rsvDate) {
    j = json{{"checkInDate",  rsvDate.checkInDate},
             {"checkOutDate", rsvDate.checkOutDate}};
}
