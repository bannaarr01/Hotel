
#ifndef HOTEL_RESERVEDDATE_H
#define HOTEL_RESERVEDDATE_H

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace rsd {
    struct ReservedDate {
        std::string checkInDate;
        std::string checkOutDate;

        void to_json(json &j, const ReservedDate &rsvDate);

        void from_json(const json &j, ReservedDate &rsvDate);
    };
}

#endif //HOTEL_RESERVEDDATE_H
