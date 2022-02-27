#ifndef HOTEL_GUEST_H
#define HOTEL_GUEST_H

#include "../../interface/IVisitor.h"
#include "../../interface/IPrintable.h"
#include <algorithm>
#include <memory>
#include "iomanip"
#include <fstream>
#include "nlohmann/json.hpp"

class Guest : public IVisitor, public IPrintable {
private:
//    static int guestId;
    std::string name;
    std::string address;
    std::string country;
    std::string nationality;
    std::string gender;
    std::string contact;
    IdDetails id;
    CreditCardDetails creditCard;
public:
    Guest(std::string name, std::string address, std::string country,
          std::string nationality, std::string gender, std::string contact,
          IdDetails id, CreditCardDetails creditCard);

    Guest() {}

    Guest(std::vector<Guest> &g) {
    }

    virtual std::string getName() const override;

    virtual void setName(std::string name) override;

    virtual std::string getAddress() const override;

    virtual void setAddress(std::string address) override;

    virtual std::string getCountry() const override;

    virtual void setCountry(std::string country) override;

    virtual std::string getNationality() const override;

    virtual void setNationality(std::string nationality) override;

    virtual std::string getGender() const override;

    virtual void setGender(std::string gender) override;

    virtual std::string getContact() const override;

    virtual void setContact(std::string contact) override;

    virtual IdDetails getId() const override;

    virtual void setId(IdDetails::IDType idType, std::string idNumber, std::string expiryDate) override;

    virtual CreditCardDetails getCreditCard() const override;

    void setCreditCard(std::string holderName, std::string ccNumber, std::string expiryDate, std::string CVV) override;

    virtual void print(std::ostream &os) const override;

    std::string getIdTypeStr(IdDetails::IDType idType) const;

    auto convertToJsonFormat() const {
        nlohmann::json j;


        j["Guest"] = {{"name",                                                               name},
                      {"gender",                                                             gender},
                      {(id.getIdType() == 1) ? "passport number" : "driving license number", id.getIdNumber()},
                      {"country",                                                            country},
                      {"contact",                                                            contact}
        };

        return j.dump(4);
        //}
    }

    auto changeGuestDetails() {
        return [this](std::string newAddress, std::string newCountry, std::string newContact) {
            address = newAddress;
            country = newCountry;
            contact = newContact;
        };
    }

    auto changeGuestCcDetails() {
        return [this](std::string &newHolderName, std::string &newCcNumber, std::string &newExpiryDate,
                      std::string &newCVV) {
            creditCard.setHolderName(newHolderName);
            creditCard.setCcNumber(newCcNumber);
            creditCard.setExpiryDate(newExpiryDate);
            creditCard.setCVV(newCVV);
        };
    }

    auto changeGuestIdDetails() {
        return [this](std::string newIdNumber, IdDetails::IDType newIdType, std::string newExpiryDate) {
            id.setIdNumber(newIdNumber);
            id.setIdType(newIdType);
            id.setExpiryDate(newExpiryDate);
        };
    }


    bool operator<(const Guest &rhs) const;

    bool operator==(const Guest &rhs) const;

    virtual ~Guest() = default;


};


#endif //HOTEL_GUEST_H
