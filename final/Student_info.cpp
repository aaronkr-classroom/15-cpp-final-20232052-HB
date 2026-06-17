// Student_info.cpp
#include <iostream>

#include "Student_info.h"
#include "Core.h"
#include "Grad.h"
#include "grade.h"
#include "Intl.h"

using namespace std;

// 생성자!
// 빈 생성자
Student_info::Student_info(const Student_info& s) : cp(0) {
	if (s.cp) cp = s.cp->clone();
}

istream& Student_info::read(istream& is) {
	delete cp; // 이전 객체 있으면 삭제

	char ch;
	is >> ch;	// record 타입 입력

	// record 타입 확인
	if (ch == 'U') {
		cp = new Core(is);
	}
	else if (ch == 'G') {
		cp = new Grad(is);
	}
	else {
		cp = new Intl(is);
	}

	return is;
}

Student_info& Student_info::operator=(const Student_info& s) {
	if (&s != this) {
		delete cp;
		if (s.cp)
			cp = s.cp->clone();
		else
			cp = 0;
	}
	return *this;
}

// cin을 일어 Student_info를 초기화
// Student_info::Student_info(istream& is) { read(is); }
/*
bool compare(const Student_info& x, const Student_info& y) {
	return x.get_name() < y.get_name(); // A < Z일 때 참 반환, Z < A일 때 거짓 반환
}

double Student_info::grade() const {
	return ::grade(get_midterm(), get_final(), get_hw());
}
*/
istream& read_hw(istream& in, Vec<double>& hw) {
	if (in) {
		// 이전 내용을 제거
		hw.clear();

		// 입력을 위한 변수
		double x; // cin에서 사용하기

		// 입력받은 점수의 합은 sum
		while (in >> x) {
			hw.push_back(x);
		}

		// 다음 학생의 점수 입력 작업을 고려해 스트림을 지움
		in.clear();
	}
	return in;
}