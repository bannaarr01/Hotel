#ifndef HOTEL_ROOMTYPEDOUBLE_H
#define HOTEL_ROOMTYPEDOUBLE_H

#include "RoomType.h"

class RoomTypeDouble : public RoomType {
private:
    static constexpr const char *roomTypeName = "DOUBLE";
public:
    RoomTypeDouble() = default;

    RoomTypeDouble(double price);

    virtual std::string getRoomTypeName() const override;

    virtual double getPrice() const override;

    virtual void setPrice(double) override;

    virtual ~RoomTypeDouble() = default;
};


#endif //HOTEL_ROOMTYPEDOUBLE_H
