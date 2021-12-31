#ifndef HOTEL_IDDETAILS_H
#define HOTEL_IDDETAILS_H

#include <iostream>

class IdDetails {
public:
    enum IDType {
        PASSPORT = 1, DRIVING_LICENSE = 2
    };

    IdDetails(IdDetails::IDType idType, std::string idNumber, std::string expiryDate);

    IdDetails() {}

    IDType getIdType() const;

    void setIdType(IDType idType);

    std::string getIdNumber() const;

    void setIdNumber(std::string idNumber);

    std::string getExpiryDate() const;

    void setExpiryDate(std::string expiryDate);

    ~IdDetails() = default;

private:
    IDType idType;
    std::string idNumber;
    std::string expiryDate;
};


#endif //HOTEL_IDDETAILS_H
