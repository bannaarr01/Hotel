#include "ReservationManager.h"


void ReservationManager::createReservation() {
    auto newReservation = ioManager.askInputToMakeReservation();
    reservations.push_back(newReservation);
    std::cout << newReservation << std::endl;
    std::string searchGuestId{newReservation.getGuestDetails().getId().getIdNumber()};
    std::string searchCheckInDate{newReservation.getCheckInDate()};

    std::ifstream inFile{fileName, std::ios::in};
    std::ofstream outFile{fileName, std::ios::app};
    std::string line{};
    bool result{false};
    try {
        if (!inFile) {
            throw ErrorOpeningFileException{};
        }
        if (!outFile) {
            throw ErrorWritingToFileException{};
        }
        while (inFile >> line) {
            //check if the name and id exist
            if (numberOfTimes(searchCheckInDate, searchGuestId, line))
                result = true;
        }
        if (result) {
            //if exist throw an exception
            throw AlreadyExistException{};
        } else {
            //if not, dereference the pointer and insert the details
            outFile << newReservation << std::endl;
            std::cout << "🟢 Reservation successfully created ✅" << std::endl;
        }
    } catch (const AlreadyExistException ex) {
        std::cout << ex.what() << std::endl;
    } catch (const ErrorOpeningFileException ex) {
        std::cout << ex.what() << std::endl;
    } catch (const ErrorWritingToFileException ex) {
        std::cout << ex.what() << std::endl;
    }
    //closing both files
    inFile.close();
    outFile.close();
}

