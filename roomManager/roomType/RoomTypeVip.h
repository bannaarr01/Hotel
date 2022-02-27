#ifndef HOTEL_ROOMTYPEVIP_H
#define HOTEL_ROOMTYPEVIP_H

#include "RoomType.h"

class RoomTypeVip : public RoomType {
private:
    static constexpr const char *roomTypeName = "VIP";

public:
    RoomTypeVip() = default;

    RoomTypeVip(double price);

    virtual std::string getRoomTypeName() const override;

    virtual double getPrice() const override;

    virtual void setPrice(double) override;

    virtual ~RoomTypeVip() = default;

};


#endif //HOTEL_ROOMTYPEVIP_H
