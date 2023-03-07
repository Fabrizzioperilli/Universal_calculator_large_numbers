/**
 * @file BigIntException.h
 * @title Calculadora de expresiones en notación polaca inversa
 * @brief Declaración de las clases de excepciones de BigInt
 * @version 1.0
 * @date 6/03/2023
 * @author: Fabrizzio Perilli Martín
 */

#pragma once
#include <exception>

#include <exception>
#include <string>

#include <exception>
#include <string>

class BigIntException : public std::exception
{
private:
    std::string m_file;
    int m_line;

public:
    BigIntException(const char *file, int line) : m_file(file), m_line(line) {}

    virtual const char *what() const noexcept
    {
        return "BigIntException";
    }

    virtual std::string getErrorMessage() const noexcept
    {
        return "";
    }

    std::string getLocation() const noexcept
    {
        std::string location = "Archivo: ";
        location += m_file;
        location += ", línea: ";
        location += std::to_string(m_line);
        return location;
    }
};

class BigIntBadDigit : public BigIntException
{
private:
    char m_badDigit;

public:
    BigIntBadDigit(char badDigit, const char *file, int line) : BigIntException(file, line), m_badDigit(badDigit) {}

    const char *what() const noexcept
    {
        return "BigIntBadDigit";
    }

    std::string getErrorMessage() const noexcept
    {
        std::string errorMessage = "Se encontró un dígito no válido: ";
        errorMessage += m_badDigit;
        return errorMessage;
    }
};

class BigIntDivisionByZero : public BigIntException
{
public:
    BigIntDivisionByZero(const char *file, int line) : BigIntException(file, line) {}

    const char *what() const noexcept
    {
        return "BigIntDivisionByZero";
    }

    std::string getErrorMessage() const noexcept
    {
        return "Se intentó realizar una división por cero";
    }
};

class BigIntBaseNotImplemented : public BigIntException
{
private:
    int m_base;

public:
    BigIntBaseNotImplemented(int base, const char *file, int line) : BigIntException(file, line), m_base(base) {}

    const char *what() const noexcept
    {
        return "BigIntBaseNotImplemented";
    }

    std::string getErrorMessage() const noexcept
    {
        std::string errorMessage = "La base ";
        errorMessage += std::to_string(m_base);
        errorMessage += " no está implementada";
        return errorMessage;
    }
};
