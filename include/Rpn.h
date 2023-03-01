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

template <class T, class K>
class Rpn
{
public:
  Rpn();
  Rpn(std::vector<std::pair<std::string, T>> &);
  ~Rpn();
  T Calculate(const std::string &);
  void SetOperand(std::pair<std::string, T>);

private:
  std::stack<K> stack_;
  bool isOperator_(const std::string &);
  bool isOperand_(const std::string &);
  K operate_(const K &, const K &, const std::string &);
  std::vector<std::string> Split_(std::string);
  std::vector<std::pair<std::string, T>> operands_;
};

template <class T, class K>
Rpn<T, K>::Rpn() {}

template <class T, class K>
Rpn<T, K>::Rpn(std::vector<std::pair<std::string, T>> &operands)
{
  operands_ = operands;
}

template <class T, class K>
Rpn<T, K>::~Rpn() {}

template <class T, class K>
void Rpn<T, K>::SetOperand(std::pair<std::string, T> operand)
{
  operands_.push_back(operand);
}

template <class T, class K>
T Rpn<T, K>::Calculate(const std::string &line)
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

      K op1 = stack_.top();
      stack_.pop();
      K op2 = stack_.top();
      stack_.pop();
      stack_.push(operate_(op1, op2, token));
    }
    else if (isOperand_(token))
    {
      for (auto operand : operands_)
        if (operand.first == token)
        {
          if (typeid(T) == typeid(K))
            stack_.push(operand.second);
          else
          {
            K aux_k = operand.second.operator K();
            stack_.push(aux_k);
          }
          break;
        }
    }
    else
    {
      std::cout << "Error: Operando no válido" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  K result_k = stack_.top();
  stack_.pop();
  T result_t = result_k.operator T();
  return result_t;
}

template <class T, class K>
bool Rpn<T, K>::isOperator_(const std::string &op)
{
  if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "%" || op == "_" || op == "++" || op == "--" || op == ">")
    return true;
  else
    return false;
}

template <class T, class K>
K Rpn<T, K>::operate_(const K &op1, const K &op2, const std::string &operat)
{
  if (operat == "+")
    return op2 + op1;
  else if (operat == "-")
    return op2 - op1;
  else if (operat == "*")
    return op2 * op1;
  else if (operat == "/")
    return op2 / op1;
  else if (operat == "%")
    return op2 % op1;
  else if (operat == "^")
    return pow(op2, op1);
  else if (operat == "_")
    return -K(op1);
  else if (operat == "++")
    return ++K(op1);
  else if (operat == "--")
    return --K(op1);
  else
  {
    std::cout << "Error: Operador no válido" << std::endl;
    exit(EXIT_FAILURE);
  }
}

template <class T, class K>
std::vector<std::string> Rpn<T, K>::Split_(std::string line)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream iss(line);

  while (iss >> token)
    tokens.push_back(token);

  return tokens;
}

template <class T, class K>
bool Rpn<T, K>::isOperand_(const std::string &op)
{
  for (auto operand : operands_)
    if (operand.first == op)
      return true;

  return false;
}