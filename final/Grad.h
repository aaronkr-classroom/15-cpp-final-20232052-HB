#pragma once
// Grad.h

#ifndef GUARD_Grad_h
#define GUARD_Grad_h

#include <iostream>

#include "Core.h"

using namespace std;

class Grad : public Core {
public:
	Grad() : thesis(0) { };
	Grad(istream& is) { read(is); };
	double grade() const;
	istream& read(istream&);
	virtual char getType() const { return 'G'; } //
private:
	double thesis; // 졸업 논문
	Grad* clone() const { return new Grad(*this); }
};

#endif