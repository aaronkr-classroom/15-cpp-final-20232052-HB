// main.cpp
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "Intl.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"


bool compare_handles(const Handle<Core>& lhs, const Handle<Core>& rhs) {
	if ( lhs->getType() != rhs->getType() ) {
		return lhs->getType() > rhs->getType();
	}
	return lhs->getName() < rhs->getName(); // grade로 바꾸면 성적순 정렬
}

bool compare_grades_handles(const Handle<Core>& lhs, const Handle<Core>& rhs) {
	return lhs->grade() > rhs->grade();
}

bool compare_Core_ptrs_handles(const Handle<Core>& lhs, const Handle<Core>& rhs) {
	return lhs->getName() < rhs->getName();
}


using namespace std;

int main() {
	vector< Handle<Core> > students; // 객체가 아닌 포인터를 저장 // 띄어쓰기 중요
	Handle<Core> record;
	char ch;
	string::size_type maxlen = 0;

	cout << "Enter student data in the format: "
		<< "U/G/F name midterm final (thesis) (TOEIC) [homework]" << endl << endl
		<< "  - U/G/F (select one) is U for Undergraduate (학부생) or G for Graduate (대학원생) or I for Intl(외국인)" << endl
		<< "  - (thesis) is only applicable for G (대학원생)" << endl
		<< "  - (TOIEC) is only applicable for I (외국인)" << endl
		<< "  - [homework] is a list of int grades without []" << endl << endl
		<< "Press CTRL+Z and ENTER twice to process." << endl << endl;

	// 데이터 읽고 저장하기
	while (cin >> ch) {
		if (cin.eof()) break;  // Check for end of input

		
		if (ch != 'U' && ch != 'G' && ch !='I') {
			
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (ch == 'U')
			record = new Core; // Core 객체 할당
		else if (ch == 'G')
			record = new Grad; // Grad 객체 할당
		else if (ch == 'I') // 기말 때 외국인 추가
			record = new Intl; /// Intl객체 할당
		else
			continue;
		
		// Handle<T>:: -> 연산자 함수 호출 후 가상 함수 호출하기
		record->read(cin);

		maxlen = max(maxlen, record->getName().size()); // 역참조
		students.push_back(record);
	}

	// 포인터로 동작하는 compare 함수를 전달
	sort(students.begin(), students.end(), compare_Core_ptrs_handles);  
	//ㄴ> compare_handles는 U/G/F 분류, compare_grades_handles는 성적 분류, compare_Core_ptrs_handles는 이름 분류

	// 이름과 점수를 출력하기
	for (vector<Core*>::size_type i = 0; i != students.size(); i++) {

		// 💡 4. dynamic_cast를 사용하여 (I) 출력 분기 추가
		if (dynamic_cast<Grad*>(students[i])) {
			cout << "(G) ";
		}
		else if (dynamic_cast<Intl*>(students[i])) {
			cout << "(I) "; // Intl 타입일 경우
		}
		else {
			cout << "(U) ";
		}

		// 함수를 호출하려고 포인터인 students[i]를 역참조
		cout << students[i]->getName()
			<< string(maxlen + 1
				- students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade(); // 역참조
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl; // 예외 출력
		}
	}

	return 0;
}