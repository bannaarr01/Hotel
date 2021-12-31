#ifndef HOTEL_ERRORWRITINGTOFILEEXCEPTION_H
#define HOTEL_ERRORWRITINGTOFILEEXCEPTION_H


class ErrorWritingToFileException : public std::exception {
public:
    ErrorWritingToFileException() noexcept = default;

    ~ErrorWritingToFileException() = default;

    virtual const char *what() const noexcept {
        return "\033[1;31m 🔴 Error writing to file...🧨 \033[0m";

    }
};

#endif //HOTEL_ERRORWRITINGTOFILEEXCEPTION_H
