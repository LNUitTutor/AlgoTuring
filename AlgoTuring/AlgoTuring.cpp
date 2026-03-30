#include <iostream>
#include <fstream>
#include "Machine.h"

int main()
{
    Machine MT(2);
    MT.setTape("|||");
    MT.setCommand(0, '|', { '|', 0, Move::R }).setCommand(0, '~', { '*', 1, Move::L });
    MT.setCommand(1, '|', { '|', 1, Move::L }).setCommand(1, '~', { '~',-1, Move::R });
    std::cout << "*** Append by *\n\n";
    MT.printProgram(std::cout); std::cin.get();

    if (MT.run(100)) std::cout << "Excellent!\n";
    else std::cout << "Upps...\n";
    std::cin.get();

    MT.setStatesCount(3).setTape("101");
    MT.setCommand(0, '0', { '0', 0, Move::R })
        .setCommand(0, '1', { '1', 0, Move::R }).setCommand(0, '~', { '~', 1, Move::L });
    MT.setCommand(1, '0', { '1', 2, Move::L })
        .setCommand(1, '1', { '0', 1, Move::L }).setCommand(1, '~', { '1',-1, Move::H });
    MT.setCommand(2, '0', { '0', 2, Move::L })
        .setCommand(2, '1', { '1', 2, Move::L }).setCommand(2, '~', { '~',-1, Move::R });
    std::cout << "*** Binary increment\n\n";
    MT.printProgram(std::cout); std::cin.get();

    if (MT.run(100)) std::cout << "Excellent!\n";
    else std::cout << "Upps...\n";
    std::cin.get();
    if (MT.reset().run(100)) std::cout << "Excellent!\n";
    else std::cout << "Upps...\n";
    std::cin.get();
    if (MT.reset().run(100)) std::cout << "Excellent!\n";
    else std::cout << "Upps...\n";
    std::cin.get();

    std::ifstream fin("Copy.txt");
    MT.loadProgram(fin);
    fin.close();
    std::cout << "*** Copy the word\n\n";
    MT.printProgram(std::cout);
    std::cin.get();
    MT.setTape("abba"); MT.run(200);
    std::cout << " Result = " << MT.getResultWord() << '\n';
    std::cin.get();

    fin.open("Multiply.txt");
    MT.loadProgram(fin);
    fin.close();
    std::cout << "*** Unary multiplication\n\n";
    MT.printProgram(std::cout);
    std::cin.get();
    MT.setTape("111x1111"); MT.run(400);
    std::string result = MT.getResultWord();
    std::cout << " Result = " << result << '\n';
    std::cin.get();

    fin.open("UnaryToDecimal.txt");
    MT.loadProgram(fin);
    fin.close();
    std::cout << "*** Unary To Decimal\n\n";
    MT.printProgram(std::cout);
    std::cin.get();
    MT.setTape(result); MT.run(400);
    std::cout << " Result = " << MT.getResultWord() << '\n';
    std::cin.get();

    fin.open("Euclid.txt");
    MT.loadProgram(fin);
    fin.close();
    std::cout << "*** GCD by Euclid's algorithm\n\n";
    MT.printProgram(std::cout);
    std::cin.get();
    MT.setPosition(21).setTape(std::string(21 + 49, '1')); MT.run(5000);
    std::cout << " Result = " << MT.getResultWord() << '\n';
}
