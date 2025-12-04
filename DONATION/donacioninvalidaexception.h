#ifndef DONACIONINVALIDAEXCEPTION_H
#define DONACIONINVALIDAEXCEPTION_H

#include <stdexcept>
#include <string>

class DonacionInvalidaException : public std::runtime_error {
public:
    explicit DonacionInvalidaException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif
