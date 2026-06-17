#pragma once
// Student_info.h

#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <iostream>
#include <string>
#include <vector>

#include "Vec.h" // 우리 만든 Vec 클래스
#include "Core.h"

using namespace std;

class Student_info {
private:
	Core* cp;

public:
	// 생성자!
	Student_info() : cp(0) { }; // 빈 Student_info 객체를 생성
	Student_info(istream& is) : cp(0) { read(is); }; // 스트림을 읽어 Student_info 객체를 생성

	// Core 위해 추가
	Student_info(const Student_info&);
	Student_info& operator=(const Student_info&); // & 추가!!
	~Student_info() { delete cp; }

	string get_name() const {
		if (cp) return cp->getName();
		else throw runtime_error("Uninitialized student!");
	}
	/*
	double get_midterm() const {
		if (cp) return cp->getMidterm();
		else throw runtime_error("Uninitialized student!");
	}
	double get_final() const {
		if (cp) return cp->getFinal();
		else throw runtime_error("Uninitialized student!");
	}
	*/
	// vector<double> get_hw() const { return homework; }

	// void set_name(string n) { name = n; } // 에런 추가 

	istream& read(istream&);
	double grade() const {
		if (cp) return cp->grade();
		else throw runtime_error("Uninitialized student!");
	};

	static bool compare(const Student_info& s1,
		const Student_info& s2) {
		return s1.get_name() < s2.get_name();
	}
};

#endif