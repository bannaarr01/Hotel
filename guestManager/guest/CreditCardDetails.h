#ifndef HOTEL_CREDITCARDDETAILS_H
#define HOTEL_CREDITCARDDETAILS_H

#include <iostream>

class CreditCardDetails {
private:
    std::string holderName;
    std::string ccNumber;
    std::string expiryDate;
    std::string CVV;
public:
    CreditCardDetails(std::string holderName, std::string ccNumber, std::string expiryDate, std::string CVV);

    CreditCardDetails() {}

    std::string getHolderName() const;

    void setHolderName(std::string holderName);

    std::string getCcNumber() const;

    void setCcNumber(std::string ccNumber);

    std::string getExpiryDate() const;

    void setExpiryDate(std::string expiryDate);

    std::string getCVV() const;

    void setCVV(std::string CVV);

    ~CreditCardDetails() = default;
};


#endif //HOTEL_CREDITCARDDETAILS_H
