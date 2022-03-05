#include "PaymentManager.h"

void PaymentManager::paymentMenu() {
    ReservationManager rm;
    // auto rsvObjSet = &reservationsObjSet);
    if (!rm.copyCsvToReservationsObjSet(&reservationsObjSet)) {
        std::cout << "\033[1;31m🚨 An error has occurred...Please Try again later.[0m️" << std::endl;
        OverallManager::mainMenu();
    }
    //Accept valid range and UI to display
    int selection = ioManager.inputValidation(1, 5, UI::paymentManagerMenu);

    switch (selection) {
        case 1: {
            std::cout << std::string(2, '\n');
            //Process payment for existing Reservation
            getReservationDetails();
            break;
        }
        case 2: {
            std::cout << std::string(2, '\n');
            //Display all active reservations in tabular form
            //printReservations();
            break;
        }
        case 3: {
            std::cout << std::endl;
            //Manage Existing Reservation
            //  manageReservation();
            break;
        }
        case 4: {
            std::cout << std::string(2, '\n');
            //Go back to Main Menu
            OverallManager::mainMenu();
            break;
        }
        case 5: {
            std::cout << std::endl << std::endl;
            //Stop and Exit the System
            std::cout << "\033[1;31mQuitting. . .[0m️";
            break;
        }
    }

}

void PaymentManager::processPayment(Reservation &reservation) {
    reservation.getCheckOutDate();
    reservation.getCheckInDate();
    //Get number of days, Pay, n set status to HAS_PAID n UPLOAD BACK TO DISK
    std::cout << "\n\033[1;36mPROCEED PAYMENT WITH THIS CREDIT CARD DETAILS ? [0m️" << std::endl;
    auto cc = reservation.getGuest().getCreditCard();
    std::cout << "\nCC Holder's Name: " << cc.getHolderName() << std::endl;
    int size = cc.getCcNumber().size();
    std::cout << "CC Number Ending With : ";
    std::cout << std::setw(size) << std::left << std::setfill('*') << ""
              << cc.getCcNumber()[size - 3] << cc.getCcNumber()[size - 2] << cc.getCcNumber()[size - 1]
              << std::endl;
    std::cout << "\n1. YES Proceed\n2. NO - New Credit Card Details" << std::endl;
    int select = ioManager.inputValidationV2(1, 2);
    if (select == 1) {
        //Success for now. . .
        //Enter cvv n exp date to complete
        try {
            std::ofstream outFile{fileName, std::ios::trunc};
            std::string line{};
            auto oldRsDates = reservation;
            auto iterator = reservationsObjSet.begin();
            while (iterator != reservationsObjSet.end()) {
                if (*iterator == reservation) {
                    reservationsObjSet.erase(iterator);
                    reservation.setHasPaid(true);
                    auto confirmedStatus = Reservation::ReservationStatus(2);
                    reservation.setReservationStatus(confirmedStatus);

                    reservationsObjSet.emplace(reservation);
                    // std::sort(reservationsObjSet.begin(), reservationsObjSet.end());
                    if (!outFile) {
                        throw ErrorWritingToFileException{};
                    }
                    for (const auto &elem: reservationsObjSet)
                        outFile << elem << std::endl;
                    outFile.close();
                    iterator = reservationsObjSet.end();
                } else {
                    iterator++; //only increment the iterator if...
                }

            }
        } catch (ErrorWritingToFileException &ex) {
            // std::cout << ex.what() << std::endl;

        }
        std::set<Reservation> toDisplay{reservation};
        UI ui;
        ui.reservationTabularDisplay(toDisplay);
        std::cout << "\033[1;32mYour Reservation has now been CONFIRMED ✅[0m" << std::endl;
    }
    if (select == 2) {
        //Enter New CC Details...
        Guest g;
        std::string newHolderName, newCcNumber, newExpiryDate, newCVV;
        auto changeCC = g.changeGuestCcDetails();
        changeCC(newHolderName, newCcNumber, newExpiryDate, newCVV);
    }


}

void PaymentManager::getReservationDetails() {
    ReservationManager rm;
    Reservation reservation;
    std::cout << "Enter Reservation ID: ";
    std::string revId;
    std::cin >> revId;

    auto rsvObjSet = std::make_unique<std::set<Reservation>>(reservationsObjSet);
    auto resultRsv = rm.findReservation(revId, std::move(rsvObjSet));

    if (!std::empty(resultRsv)) {
        auto rRsv = resultRsv.at(0);
        reservation = rRsv;
        std::cout << "🟢 Reservation Record Found" << std::endl;
        //std::cout << resultRsv.at(0).getRoom() << std::endl;

        // pass control to process payment of the found reservation
        processPayment(reservation);
    } else {
        std::cout << "\n\033[1;31m🔴 Reservation Record NOT Found[0m" << std::endl;
        std::cout << std::endl;
        std::cout << "\033[1;36mSEARCH AGAIN ?[0m" << std::endl;
        std::cout << "1. YES\n2. NO" << std::endl;
        int secondSelect = ioManager.inputValidationV2(1, 2);
        if (secondSelect == 1)
            getReservationDetails();
        else if (secondSelect == 2)
            paymentMenu();
    }

}


