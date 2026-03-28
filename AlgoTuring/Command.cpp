#include "Command.h"

std::ostream& operator<<(std::ostream& os, Move m)
{
	switch (m)
	{
	case Move::L: os << 'L'; break;
	case Move::H: os << 'H'; break;
	case Move::R: os << 'R'; break;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Move& m)
{
	char n; is >> n;
	switch (toupper(n))
	{
	case 'L': m = Move::L; break;
	case 'R': m = Move::R; break;
	default: m = Move::H;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Command& c)
{
	if (c.s == '\0')
		os << "       ";
	else if (c.q >= 0)
		os << c.s << " q_" << c.q << ' ' << c.m;
	else
		os << c.s << " q_F " << c.m;
	return os;
}

std::istream& operator>>(std::istream& is, Command& c)
{
	is >> c.s >> c.q >> c.m;
	return is;
}
