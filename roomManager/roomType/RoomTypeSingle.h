#ifndef HOTEL_ROOMTYPESINGLE_H
#define HOTEL_ROOMTYPESINGLE_H

#include "RoomType.h"

class RoomTypeSingle : public RoomType {
private:
    static constexpr const char *roomTypeName = "SINGLE";
public:
    RoomTypeSingle() = default;

    RoomTypeSingle(double price);

    virtual std::string getRoomTypeName() const override;

    virtual double getPrice() const override;

    virtual void setPrice(double) override;

    virtual ~RoomTypeSingle() = default;
};


#endif //HOTEL_ROOMTYPESINGLE_H
