#include "CreditCardDetails.h"

CreditCardDetails::CreditCardDetails(std::string holderName, std::string ccNumber,
                                     std::string expiryDate, std::string CVV)
        : holderName{holderName}, ccNumber{ccNumber}, expiryDate{expiryDate}, CVV{CVV} {

}

std::string CreditCardDetails::getHolderName() const {
    return holderName;
}

void CreditCardDetails::setHolderName(std::string holderName) {
    this->holderName = holderName;
}

std::string CreditCardDetails::getCcNumber() const {
    return ccNumber;
}

std::string CreditCardDetails::getExpiryDate() const {
    return expiryDate;
}

std::string CreditCardDetails::getCVV() const {
    return CVV;
}

void CreditCardDetails::setCVV(std::string CVV) {
    this->CVV = CVV;
}

void CreditCardDetails::setCcNumber(std::string ccNumber) {
    this->ccNumber = ccNumber;
}

void CreditCardDetails::setExpiryDate(std::string expiryDate) {
    this->expiryDate = expiryDate;
}

