//
// Created by Josh on 25/12/2021.
//

#include "IdDetails.h"

IdDetails::IdDetails(IdDetails::IDType idType, std::string idNumber, std::string expiryDate)
        : idType{idType}, idNumber{idNumber}, expiryDate{expiryDate} {

}

IdDetails::IDType IdDetails::getIdType() const {
    return idType;
}

void IdDetails::setIdType(IdDetails::IDType idType) {
    this->idType = idType;
}

std::string IdDetails::getIdNumber() const {
    return idNumber;
}

std::string IdDetails::getExpiryDate() const {
    return expiryDate;
}

void IdDetails::setExpiryDate(std::string expiryDate) {
    this->expiryDate = expiryDate;
}

void IdDetails::setIdNumber(std::string idNumber) {
    this->idNumber = idNumber;
}
