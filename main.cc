/**
 * @file main.cc
 * @brief Fichero principal de la calculadora de expresiones en notación polaca inversa de numeros grandes
 * @version 1.0
 * @date 14/02/2023
 * @author: Fabrizzio Perilli Martín
 */

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "../include/BigInt.h"
#include "../include/Rpn.h"

void Help();
void ReadFile(std::string, std::string);
std::pair<std::string, std::string> Split(std::string);
bool CheckValidOperand(std::string, size_t);
bool CheckExpression(std::string);
std::pair<size_t, std::string> SplitExpression(std::string);
template <typename T, typename K>
std::vector<std::pair<std::string, T>> Process(std::vector<std::pair<std::string, std::string>>, std::vector<std::pair<std::string, std::string>>);

template <typename T>
void WriteFile(std::string, std::vector<std::pair<std::string, T>>);

int main(int argc, char **argv)
{
    const std::string kOptionHelp = "--help";
    const int kNumberParam = 3;

    std::cout << "--Calculadora de expresiones en notación polaca inversa--" << std::endl;
    if (argc == kNumberParam)
    {
        std::string namefile_input(argv[1]);
        std::string namefile_output(argv[2]);

        std::cout << "Argumentos correctos. Compruebe el fichero de salida: " << argv[2] << std::endl;
        ReadFile(namefile_input, namefile_output);
    }
    else if ((argc == 2) && (argv[1] == kOptionHelp))
    {
        Help();
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "Error en los parametros. Introduce ./bin/main --help para más información" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Help()
{
    std::cout << "Modo de funcionamiento:" << std::endl;
    std::cout << "./bin/main inputs/fichero_entrada.txt fichero_salida.txt" << std::endl;
}

void ReadFile(std::string file, std::string file_output)
{
    std::ifstream file_input(file);
    std::string line;

    std::vector<std::pair<std::string, std::pair<size_t, std::string>>> operands;
    std::vector<std::pair<std::string, std::string>> operations;

    if (file_input.is_open())
    {
        while (getline(file_input, line))
        {
            std::pair<std::string, std::string> aux_pair = Split(line);
            if (CheckExpression(aux_pair.second))
            {
                std::pair<size_t, std::string> pair_operand = SplitExpression(aux_pair.second);
                std::pair<std::string, std::pair<size_t, std::string>> pair_vector(aux_pair.first, pair_operand);
                operands.push_back(pair_vector);
            }
            else
                operations.push_back(aux_pair);
        }
    }
    else
    {
        std::cout << "Error al abrir el fichero: " << file << ", comprueba si existe el fichero." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Operandos" << std::endl;
    for (size_t i = 0; i < operands.size(); i++)
        std::cout << operands[i].first << "-->" << operands[i].second.first << " , " << operands[i].second.second << std::endl;

    std::cout << "Operaciones" << std::endl;
    for (size_t i = 0; i < operations.size(); i++)
        std::cout << operations[i].first << "--> "<< operations[i].second << std::endl;
    
    
    // if (file_input.is_open())
    // {
    //     while (getline(file_input, line))
    //     {
    //         std::pair<std::string, std::string> aux_pair = Split(line);
    //         if (CheckExpression(aux_pair.second) == 0)
    //             operands.push_back(aux_pair);
    //         else
    //             operations.push_back(aux_pair);
    //     }
    //     // switch (base)
    //     // {
    //     // case 2:
    //     //     WriteFile<BigInt<2>>(file_output, Process<BigInt<2>, BigInt<2>>(operands, operations));
    //     //     break;
    //     // case 8:
    //     //     WriteFile<BigInt<8>>(file_output, Process<BigInt<8>, BigInt<2>>(operands, operations));
    //     //     break;
    //     // case 10:
    //     //     WriteFile<BigInt<10>>(file_output, Process<BigInt<10>, BigInt<2>>(operands, operations));
    //     //     break;
    //     // case 16:
    //     //     WriteFile<BigInt<16>>(file_output, Process<BigInt<16>, BigInt<2>>(operands, operations));
    //     //     break;
    //     // default:
    //     //     std::cout << "Base no válida" << std::endl;
    //     //     break;
    //     // }

    //     file_input.close();
    // }
    // else
    // {
    //     std::cout << "Error al abrir el fichero: " << file << ", comprueba si existe el fichero." << std::endl;
    //     exit(EXIT_FAILURE);
    // }
}

bool CheckExpression(std::string line)
{
    std::regex reg("^[+-]?[0-9A-F]+$");
    std::size_t pos = line.find(",");
    std::string str = line.substr(pos + 2);
    if (std::regex_match(str, reg))
        return true;
    else
        return false;
}

std::pair<std::string, std::string> Split(std::string line)
{
    std::pair<std::string, std::string> pair_str;
    std::size_t pos = line.find(" ");
    pair_str.first = line.substr(0, pos);
    pair_str.second = line.substr(pos + 3);

    return pair_str;
}

std::pair<size_t, std::string> SplitExpression(std::string line)
{
    std::pair<size_t, std::string> pair_str;
    pair_str.first = std::stoi(line.substr(0, line.find(",")));
    pair_str.second = line.substr(line.find(",") + 2);

    return pair_str;
}

template <typename T, typename K>
std::vector<std::pair<std::string, T>> Process(std::vector<std::pair<std::string, std::string>> operands, std::vector<std::pair<std::string, std::string>> operations)
{
    std::vector<std::pair<std::string, T>> board;
    for (size_t i = 0; i < operands.size(); i++)
        board.push_back(std::pair<std::string, T>(operands[i].first, T(operands[i].second)));

    for (size_t i = 0; i < operations.size(); i++)
    {
        Rpn<T, K> rpn(board);
        T t(rpn.Calculate(operations[i].second));
        std::pair<std::string, T> aux = std::make_pair(operations[i].first, t);
        board.push_back(aux);
    }
    return board;
}

template <typename T>
void WriteFile(std::string file, std::vector<std::pair<std::string, T>> board)
{
    std::ofstream file_output(file);
    if (file_output.is_open())
    {
        for (size_t i = 0; i < board.size(); i++)
            file_output << board[i].first << " = " << board[i].second << std::endl;
        file_output.close();
    }
    else
    {
        std::cout << "Error al abrir el fichero: " << file << ", comprueba si existe el fichero." << std::endl;
        exit(EXIT_FAILURE);
    }
}
