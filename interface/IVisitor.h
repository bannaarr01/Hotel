#ifndef HOTEL_IVISITOR_H
#define HOTEL_IVISITOR_H

#include <iostream>
#include "../guestManager/guest/CreditCardDetails.h"
#include "../guestManager/guest/IdDetails.h"

class IVisitor {
public:
    virtual std::string getName() const = 0;

    virtual void setName(std::string name) = 0;

    virtual std::string getAddress() const = 0;

    virtual void setAddress(std::string address) = 0;

    virtual std::string getCountry() const = 0;

    virtual void setCountry(std::string country) = 0;

    virtual std::string getNationality() const = 0;

    virtual void setNationality(std::string nationality) = 0;

    virtual std::string getGender() const = 0;

    virtual void setGender(std::string gender) = 0;

    virtual std::string getContact() const = 0;

    virtual void setContact(std::string contact) = 0;

    virtual IdDetails getId() const = 0;

    virtual void setId(IdDetails::IDType idType, std::string idNumber, std::string expiryDate) = 0;

    virtual CreditCardDetails getCreditCard() const = 0;

    virtual void
    setCreditCard(std::string holderName, std::string ccNumber, std::string expiryDate, std::string CVV) = 0;

    virtual ~IVisitor() = default;

};


#endif //HOTEL_IVISITOR_H
