#pragma once
#include <iostream>

enum class Move { L = -1, H, R };
std::ostream& operator<<(std::ostream& os, Move m);
std::istream& operator>>(std::istream& is, Move& m);

struct Command
{
	char s;
	int q;
	Move m;
	bool is_empty()
	{
		return s == '\0';
	}
};
std::ostream& operator<<(std::ostream& os, const Command& c);
std::istream& operator>>(std::istream& is, Command& c);
