/**
 * @file Rpn.h
 * @brief Calculadora de expresiones en notación polaca inversa
 * @version 1.0
 * @date 14/02/2023
 * @author Fabrizzio Perilli Martín
 */
#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
#include "BigInt.h"

template <class T>
class Rpn
{
public:
  Rpn();
  Rpn(std::vector<std::pair<std::string, T>> &);
  ~Rpn();
  T Calculate(const std::string &);
  void SetOperand(std::pair<std::string, T>);

private:
  std::stack<T> stack_;
  bool isOperator_(const std::string &);
  bool isOperand_(const std::string &);
  T operate_(const T &, const T &, const std::string &);
  std::vector<std::string> Split_(std::string);
  std::vector<std::pair<std::string, T>> operands_;
};

template <class T>
Rpn<T>::Rpn() {}

template <class T>
Rpn<T>::Rpn(std::vector<std::pair<std::string, T>> &operands)
{
  operands_ = operands;
}

template <class T>
Rpn<T>::~Rpn() {}

template <class T>
void Rpn<T>::SetOperand(std::pair<std::string, T> operand)
{
  operands_.push_back(operand);
}

template <class T>
T Rpn<T>::Calculate(const std::string &line)
{
  std::vector<std::string> tokens = Split_(line);

  for (auto token : tokens)
  {
    if (isOperator_(token))
    {
      if (stack_.size() < 1)
      {
        std::cout << "Error: Pila vacía" << std::endl;
        exit(EXIT_FAILURE);
      }

      T op1 = stack_.top();
      stack_.pop();
      T op2 = stack_.top();
      stack_.pop();
      stack_.push(operate_(op1, op2, token));
    }
    else if (isOperand_(token))
    {
      for (auto operand : operands_)
        if (operand.first == token)
        {
          stack_.push(operand.second);
          break;
        }
    }
    else
    {
      std::cout << "Error: Operando no válido" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return stack_.top();
}

template <class T>
bool Rpn<T>::isOperator_(const std::string &op)
{
  if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "%" || op == "_" || op == "++" || op == "--" || op == ">")
    return true;
  else
    return false;
}

template <class T>
T Rpn<T>::operate_(const T &op1, const T &op2, const std::string &operat)
{
  if (operat == "+")
    return op2->Add(op1);
  else if (operat == "-")
    return op2->Subtract(op1);
  else if (operat == "*")
    return op2->Multiply(op1);
  else if (operat == "/")
    return op2->Divide(op1);
  else if (operat == "%")
    return op2->Module(op1);
  else if (operat == "^")
    return op2->Pow(op1);
  else
  {
    std::cout << "Error: Operador no válido" << std::endl;
    exit(EXIT_FAILURE);
  }
}

template <class T>
std::vector<std::string> Rpn<T>::Split_(std::string line)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(line);

  while (iss >> token)
    tokens.push_back(token);

  return tokens;
}

template <class T>
bool Rpn<T>::isOperand_(const std::string &op)
{
  for (auto operand : operands_)
    if (operand.first == op)
      return true;

  return false;
}