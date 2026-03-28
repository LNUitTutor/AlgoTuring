#include <iostream>
#include <fstream>
#include "Machine.h"

int main()
{
    Machine MT(2);
    MT.setTape("|||");
    MT.setCommand(0, '|', { '|', 0, Move::R }).setCommand(0, '~', { '*', 1, Move::L });
    MT.setCommand(1, '|', { '|', 1, Move::L }).setCommand(1, '~', { '~',-1, Move::R });
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
    MT.printProgram(std::cout);
    std::cin.get();
    MT.setTape("abba"); MT.run(200);
}
