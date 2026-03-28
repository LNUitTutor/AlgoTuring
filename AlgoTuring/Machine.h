#pragma once
#include <map>
#include <string>
#include <set>
#include <Windows.h>
#include "Command.h"

using Row = std::map<char, Command>;

class Program
{
	unsigned states_count;
	Row* table;
public:
	Program() :states_count(0), table(nullptr) {}
	explicit Program(unsigned n) :states_count(n)
	{
		table = new Row[n];
	}
	void clear();
	~Program() { clear(); }
	Program& setStatesCount(unsigned n);
	unsigned getStatesCount() const { return states_count; }
	Program& setCommand(unsigned state, char letter, const Command& cmd);
	Command getCommand(unsigned state, char letter) const;
	void printOn(std::ostream& os) const;
	std::set<char> getOuterABC() const;
};

const int BlackOnWhite = 0xF0;
const int WhiteOnBlack = 0x0F;

class Machine
{
	int position;
	std::string tape;
	int state;
	Program prg;
	HANDLE hConsole;
public:
	// Який символ для машини порожній
	static const char EmptySymbol = '~';

	explicit Machine(unsigned n) :position(1), state(0), prg(n), tape(2, '~')
	{ 
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, BlackOnWhite);
		system("cls");
	}
	Machine(unsigned n, int pos) :position(pos), state(0), prg(n), tape(2, '~')
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, BlackOnWhite);
		system("cls");
	}

	// Задає інформаційну стрічку, облямовує її порожніми символами
	void setTape(std::string str) { tape = str.insert(0, 1, EmptySymbol) + EmptySymbol; }

	// Друкує поточну конфігурацію
	void printOn(std::ostream& os);

	// Задає одну команду програми (state,letter)->Command
	Machine& setCommand(unsigned state, char letter, const Command& cmd);

	// Задає нову кількість станів, витирає стару програму, повертає q_0, position = 0
	Machine& setStatesCount(unsigned n);

	// Встановлює позицію голівки машини
	Machine& setPosition(int pos);

	// Відновлює початковий стан q_0
	Machine& reset();

	// Виконує програму, починаючи з поточної конфігурації
	bool run(unsigned max_step);

	// Повертає слово, записане на інформаційній стрічці
	std::string getResultWord() const;

	// Друкує функціональну схему машини
	void printProgram(std::ostream& os) const;

	// Завантажує програму з потоку
	void loadProgram(std::istream& is);
};