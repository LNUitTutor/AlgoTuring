#include "Machine.h"

void Program::clear()
{
	delete[] table;
	table = nullptr;
	states_count = 0;
}

Program& Program::setStatesCount(unsigned n)
{
	clear();
	states_count = n;
	table = new Row[n];
	return *this;
}

Program& Program::setCommand(unsigned state, char letter, const Command& cmd)
{
	table[state][letter] = cmd;
	return *this;
}

Command Program::getCommand(unsigned state, char letter) const
{
	if (table[state].find(letter) != table[state].end())
		return table[state][letter];
	return Command();
}

void Program::printOn(std::ostream& os) const
{
	for (unsigned i = 0; i < states_count; ++i)
	{
		for (auto& row : table[i])
			os << "q_" << i << ' ' << row.first
			<< " -> " << row.second << '\n';
	}
}

std::set<char> Program::getOuterABC() const
{
	std::set<char> S;
	for (unsigned i = 0; i < states_count; ++i)
		for (auto& cmd : table[i]) S.insert(cmd.first);
	return S;
}

void Machine::printOn(std::ostream& os)
{
	if (state >= 0) os << "q_" << state << ": '";
	else os << "q_F: '";
	for (int i = 0; i < position; ++i) os << tape[i];
	os << "\033[106m" << tape[position] << "\033[0m";
	for (int i = position + 1; i < tape.length(); ++i) os << tape[i];
	os << "'\n";
}

Machine& Machine::setCommand(unsigned state, char letter, const Command& cmd)
{
	prg.setCommand(state, letter, cmd);
	return *this;
}

Machine& Machine::setStatesCount(unsigned n)
{
	prg.setStatesCount(n);
	setPosition(0);
	reset();
	return *this;
}

Machine& Machine::setPosition(int pos)
{
	position = pos + 1;
	return *this;
}

Machine& Machine::reset()
{
	state = 0;
	return *this;
}

bool Machine::run(unsigned max_step)
{
	printOn(std::cout);
	unsigned step = 0;
	while (state >= 0 && step < max_step)
	{
		Command cmd = prg.getCommand(state, tape[position]);
		if (cmd.is_empty())
		{
			std::cout << "ERROR: unknown command\n";
			return false;
		}
		tape[position] = cmd.s;
		state = cmd.q;
		position += (int)cmd.m;
		if (tape[tape.length() - 1] != EmptySymbol) tape += EmptySymbol;
		else if (tape[0] != EmptySymbol)
		{
			tape.insert(0, 1, EmptySymbol);
			++position;
		}
		++step;
		printOn(std::cout);
	}
	if (step == max_step) std::cout << "ERROR: max of steps executed\n";
}

void Machine::printProgram(std::ostream& os) const
{
	std::set<char> S = prg.getOuterABC();
	os << "     ";
	for (char c : S) os << "|    " << c << "    ";
	os << '\n' << std::string(S.size() * 10 + 5, '-') << '\n';
	for (unsigned i = 0; i < prg.getStatesCount(); ++i)
	{
		os << " q_" << i;
		for (char c : S) os << " | " << prg.getCommand(i, c);
		os << '\n';
	}
}

void Machine::loadProgram(std::istream& is)
{
	unsigned n; is >> n;
	setStatesCount(n);
	do {
		int state; char letter;
		std::string arrow; Command cmd;
		(is >> state >> letter >> arrow >> cmd).get();
		setCommand(state, letter, cmd);
	} while (is);
}
