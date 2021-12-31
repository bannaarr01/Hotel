#ifndef HOTEL_ERROROPENINGFILEEXCEPTION_H
#define HOTEL_ERROROPENINGFILEEXCEPTION_H


class ErrorOpeningFileException : public std::exception {

public:
    ErrorOpeningFileException() noexcept = default;

    ~ErrorOpeningFileException() = default;

    virtual const char *what() const noexcept {
        return "\033[1;31m 🔴 Error Opening file...🧨 \033[0m";
    }

};

#endif //HOTEL_ERROROPENINGFILEEXCEPTION_H
