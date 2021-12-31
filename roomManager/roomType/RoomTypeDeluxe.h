#ifndef HOTEL_ROOMTYPEDELUXE_H
#define HOTEL_ROOMTYPEDELUXE_H

#include "RoomType.h"

class RoomTypeDeluxe : public RoomType {
private:
    static constexpr const char *roomTypeName{"DELUXE"};
public:
    RoomTypeDeluxe() = default;

    RoomTypeDeluxe(double price);

    virtual std::string getRoomTypeName() const override;

    virtual double getPrice() const override;

    virtual void setPrice(double) override;

    virtual ~RoomTypeDeluxe() = default;
};


#endif //HOTEL_ROOMTYPEDELUXE_H
