#include "Guest.h"

//int Guest::guestId{0};

Guest::Guest(std::string name, std::string address, std::string country,
             std::string nationality, std::string gender,
             std::string contact, IdDetails id, CreditCardDetails creditCard) :
        name{name}, address{address}, country{country}, nationality{nationality},
        gender{gender}, contact{contact}, id(id), creditCard(creditCard) {

}


std::string Guest::getName() const {
    return name;
}

void Guest::setName(std::string name) {
    this->name = name;
}

std::string Guest::getAddress() const {
    return address;
}

void Guest::setAddress(std::string address) {
    this->address = address;
}

std::string Guest::getCountry() const {
    return country;
}

void Guest::setCountry(std::string country) {
    this->country = country;
}

std::string Guest::getNationality() const {
    return nationality;
}

void Guest::setNationality(std::string nationality) {
    this->nationality = nationality;
}

std::string Guest::getGender() const {
    return gender;
}

void Guest::setGender(std::string gender) {
    this->gender = gender;
}

std::string Guest::getContact() const {
    return contact;
}

void Guest::setContact(std::string contact) {
    this->contact = contact;
}

IdDetails Guest::getId() const {
    return id;
}

void Guest::setId(IdDetails::IDType idType, std::string idNumber, std::string expiryDate) {
    id.setIdType(idType);
    id.setIdNumber(idNumber);
    id.setExpiryDate(expiryDate);


}

CreditCardDetails Guest::getCreditCard() const {
    return creditCard;
}

void Guest::setCreditCard(std::string holderName, std::string ccNumber, std::string expiryDate, std::string CVV) {
    creditCard.setHolderName(holderName);
    creditCard.setCcNumber(ccNumber);
    creditCard.setExpiryDate(expiryDate);
    creditCard.setCVV(CVV);
}

std::string Guest::getIdTypeStr(IdDetails::IDType idType) const {
    std::string result;
    switch (idType) {
        case IdDetails::IDType::PASSPORT:
            result = "Passport";
            break;
        case IdDetails::IDType::DRIVING_LICENSE:
            result = "Driving License";
            break;
    };
    return result;
}

bool Guest::operator<(const Guest &rhs) const {
    return this->id.getIdNumber() < rhs.id.getIdNumber();
}

bool Guest::operator==(const Guest &rhs) const {
    return this->id.getIdNumber() == rhs.id.getIdNumber();
}

//auto Guest::convertToJsonFormat() const {
//    return [this]() {
//        nlohmann::json j{
//                {"name",    name},
//                {"address", address},
//                {
//                 "id",      {"idType",   getIdTypeStr(
//                        id.getIdType()),                             "idNumber", id.getIdNumber(),         "idExpiryDate", id.getExpiryDate()}
//                },
//                {
//                 "cc",      {"ccHolder", creditCard.getHolderName(), "ccNumber", creditCard.getCcNumber(), "ccExpiryDate",
//                                                                                                                           creditCard.getExpiryDate(), "ccCVV", creditCard.getCVV()}
//                }
//        };
//        // return j.dump();
//    }
//}

void Guest::print(std::ostream &os) const {
//    os << "Name: " << name << " " << "Address: " << address << " " << "Country: "
//       << country << " "
//       << "Nationality: " << nationality << " " << "Gender: " << gender << " " << "Contact: " << contact << " "
//       << "ID Type: " << getIdTypeStr(id.getIdType()) << " " << "ID Number: " << id.getIdNumber() << " "
//       << "ID Expiry Date: " << id.getExpiryDate() << " " << "CC Holder Name: " << creditCard.getHolderName() << " "
//       << "CC Number: " << creditCard.getCcNumber() << " " << "CC Expiry Date: " << creditCard.getExpiryDate() << " "
//       << "CC CVV: " << creditCard.getCVV();
//    os << name << " " << address << " " << country << " " << nationality << " " << gender << " " << contact << " "
//       << getIdTypeStr(id.getIdType()) << " " << id.getIdNumber() << id.getExpiryDate() << " "
//       << creditCard.getHolderName() << " " << creditCard.getCcNumber() << " " << creditCard.getExpiryDate() << " "
//       << creditCard.getCVV();
//    os << convertToJsonFormat();

    os << name << "," << address << "," << country << "," << nationality << "," << gender << "," << contact << ","
       << getIdTypeStr(id.getIdType()) << "," << id.getIdNumber() << "," << id.getExpiryDate() << ","
       << creditCard.getHolderName() << "," << creditCard.getCcNumber() << "," << creditCard.getExpiryDate() << ","
       << creditCard.getCVV();


}


//auto Guest::changeGuestDetails() {
//    return [this](std::string newName) {
//        name = newName;
//        //  address = newAddress;
//    };
//}

//int Guest::getGuestId() {
//    return ++guestId;
//}



//bool Guest::findById(std::string Id) {
//    return (name == Id);
//}

//bool Guest::operator==(const std::string &Id) const {
//    return (name == Id);
//}





