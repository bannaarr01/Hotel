#ifndef HOTEL_ROOM_H
#define HOTEL_ROOM_H

#include <iostream>
#include "../../interface/IPrintable.h"
#include "../roomType/RoomType.h"
#include "../roomType/RoomTypeSingle.h"
#include "../roomType/RoomTypeDouble.h"
#include "../roomType/RoomTypeDeluxe.h"
#include "../roomType/RoomTypeVip.h"
#include "nlohmann/json.hpp"
#include <memory>
#include <vector>
#include <iomanip>

class Room : public IPrintable {
public:
    enum RoomAvailabilityStatus {
        VACANT = 1, OCCUPIED = 2, RESERVED = 3, UNDER_MAINTENANCE = 4
    };
    enum BedType {
        SINGLE = 1, DOUBLE = 2, MASTER = 3
    };

    Room() = default;

    Room(std::vector<Room> &room) {
    }

    Room(std::string roomNumber, RoomAvailabilityStatus roomAvailabilityStatus, BedType bedType,
         bool isWifiEnabled, std::shared_ptr<RoomType> &roomTypePtr);

    std::string getRoomNumber() const;

    void setRoomNumber(std::string roomNo);

    RoomAvailabilityStatus getRoomAvailabilityStatus() const;

    void setRoomAvailabilityStatus(RoomAvailabilityStatus);

    BedType getBedType() const;

    void setBedType(BedType);

    bool getWifiEnabled() const;

    void setWifiEnabled(bool);

    void setRoomTypeSingle(double);

    void setRoomTypeDouble(double);

    void setRoomTypeDeluxe(double);

    void setRoomTypeVip(double);

    std::shared_ptr<RoomType> getRoomType() const;

    std::string roomAvailabilityStatusToString(RoomAvailabilityStatus roomAvailabilityStatus) const;


    std::string bedTypeToString(BedType bedType) const;


    auto updateRoomDetails() {
        return [this](RoomAvailabilityStatus newRoomAvailabilityStatus, double price,
                      bool newIsWifiEnabled) {
            roomAvailabilityStatus = newRoomAvailabilityStatus;
            roomTypePtr->setPrice(price);
            isWifiEnabled = newIsWifiEnabled;
        };
    }

    virtual void print(std::ostream &os) const override;

    auto convertToJsonFormat() const {
        nlohmann::json j;
        j["Room"] = {{"room no",      roomNumber},
                     {"status",       roomAvailabilityStatusToString(roomAvailabilityStatus)},
                     {"wifi enabled", ((isWifiEnabled == 0) ? "No" : "Yes")},
                     {"room type",    roomTypePtr->getRoomTypeName()},
                     {"price",        roomTypePtr->getPrice()}
        };

        return j.dump(4);
    }

    bool operator==(const Room &rhs) const;

    bool operator<(const Room &rhs) const;

    virtual ~Room() = default;

private:
    std::string roomNumber;
    RoomAvailabilityStatus roomAvailabilityStatus;
    BedType bedType;
    bool isWifiEnabled;
    std::shared_ptr<RoomType> roomTypePtr;
};


#endif //HOTEL_ROOM_H
