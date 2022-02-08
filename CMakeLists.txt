cmake_minimum_required(VERSION 3.20)
project(Hotel)

set(CMAKE_CXX_STANDARD 17)
message(STATUS "start running cmake...")
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Boost 1.76.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Hotel main.cpp
        guestManager/GuestManager.cpp guestManager/GuestManager.h
        ioManager/IoManager.cpp ioManager/IoManager.h
        reservationManager/ReservationManager.cpp
        reservationManager/ReservationManager.h
        roomManager/RoomManager.cpp roomManager/RoomManager.h
        paymentManager/PaymentManager.cpp paymentManager/PaymentManager.h
        roomManager/room/Room.cpp roomManager/room/Room.h
        roomManager/roomType/RoomType.cpp roomManager/roomType/RoomType.h
        roomManager/roomType/RoomTypeSingle.cpp roomManager/roomType/RoomTypeSingle.h
        roomManager/roomType/RoomTypeDouble.cpp roomManager/roomType/RoomTypeDouble.h
        roomManager/roomType/RoomTypeDeluxe.cpp roomManager/roomType/RoomTypeDeluxe.h
        roomManager/roomType/RoomTypeVip.cpp roomManager/roomType/RoomTypeVip.h
        interface/IVisitor.cpp interface/IVisitor.h
        guestManager/guest/Guest.cpp guestManager/guest/Guest.h
        guestManager/guest/CreditCardDetails.cpp guestManager/guest/CreditCardDetails.h
        guestManager/guest/IdDetails.cpp guestManager/guest/IdDetails.h
        overallManager/OverallManager.cpp overallManager/OverallManager.h
        interface/IPrintable.cpp interface/IPrintable.h paymentManager/payment/PaymentDetails.cpp
        paymentManager/payment/PaymentDetails.h paymentManager/payment/Promotion.cpp
        paymentManager/payment/Promotion.h exception/InvalidEntryException.h
        exception/AlreadyExistException.h exception/ErrorOpeningFileException.h
        exception/ErrorWritingToFileException.h ui/UI.cpp ui/UI.h hotelUtil/HotelUtil.cpp
        hotelUtil/HotelUtil.h reservationManager/reservation/Reservation.cpp reservationManager/reservation/Reservation.h reservationManager/ManageOverlap.cpp reservationManager/ManageOverlap.h)

target_link_libraries(Hotel PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Hotel PRIVATE ${Boost_LIBRARIES})