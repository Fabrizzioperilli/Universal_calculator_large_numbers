#pragma once
#include <exception>

#include <exception>
#include <string>

class BigIntException : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "BigIntException";
    }

    virtual std::string getErrorMessage() const noexcept {
        return "";
    }
};

class BigIntBadDigit : public BigIntException {
private:
    char m_badDigit;

public:
    BigIntBadDigit(char badDigit) : m_badDigit(badDigit) {}

    const char* what() const noexcept {
        return "BigIntBadDigit";
    }

    std::string getErrorMessage() const noexcept {
        std::string errorMessage = "Se encontró un dígito no válido: ";
        errorMessage += m_badDigit;
        return errorMessage;
    }
};

class BigIntDivisionByZero : public BigIntException {
public:
    const char* what() const noexcept {
        return "BigIntDivisionByZero";
    }

    std::string getErrorMessage() const noexcept {
        return "Se intentó realizar una división por cero";
    }
};

class BigIntBaseNotImplemented : public BigIntException {
private:
    int m_base;

public:
    BigIntBaseNotImplemented(int base) : m_base(base) {}

    const char* what() const noexcept {
        return "BigIntBaseNotImplemented";
    }

    std::string getErrorMessage() const noexcept {
        std::string errorMessage = "La base ";
        errorMessage += std::to_string(m_base);
        errorMessage += " no está implementada";
        return errorMessage;
    }
};

