#include "Catch.hpp"
#include "SDAL.h"
#include <stdexcept>
struct Student {
	public:
		int grade;
		Student() {
			grade = 0;
		}
};

TEST_CASE( "SDAL_Testing arrow operator", "[SDAL_arrow_operator]" ) {
	cop3530::SDAL<Student> l;
	Student student;
	l.push_front(student);
	cop3530::SDAL<Student>::iterator iter = l.begin();
	REQUIRE(iter->grade == 0);

	SECTION("Throws exception when trying to use with a null array") {
		cop3530::SDAL<Student>::iterator iter2;
		bool caught = false;
		try{
			iter2->grade;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Iterating through elements", "[SDAL_iteration]" ) {
	cop3530::SDAL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	SECTION("Iterating through list, testing *, end, begin, =, and preincrement operator"){
		l.push_front('A');
		cop3530::SDAL<char>::iterator iter = l.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != l.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Non equal and equality operators work, along with postincrement operator") {
		cop3530::SDAL<char>::iterator iter = l.begin();
		iter++;
		cop3530::SDAL<char>::iterator iter2 = l.begin();
		REQUIRE(iter != iter2);
		iter2++;
		REQUIRE(iter == iter2);
	}
}

TEST_CASE( "SDAL_Testing explicit constructor and exception caught with dereference operator when null", "[SDAL_explicit]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	cop3530::SDAL<char>::iterator iter;
	bool caught = false;
	try {
		*iter = 'X';
	} catch(std::logic_error &le) {
		caught = true;
	}
	REQUIRE(caught == true);
}

TEST_CASE( "SDAL_Testing constructor", "[SDAL_constructor]" ) {
	cop3530::SDAL<char> l;
	Student student;
	l.push_front('X');
	cop3530::SDAL<char>::iterator iter = l.begin();
	cop3530::SDAL<char>::iterator iter2(iter);

	REQUIRE(*iter2 == 'X');
}

TEST_CASE("SDAL_Testing increment operators for exceptions", "[SDAL_incrementing]") {
	cop3530::SDAL<char> l;
	l.push_front('A');
	l.push_front('B');
	SECTION("Preincrement operator throws exception when the node is null") {
		cop3530::SDAL<char>::iterator iter = l.begin();
		++iter;
		++iter;
		bool caught = false;
		try {
			++iter;
		} catch(std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
	SECTION("Postincrement operator throws exception when the node is null") {
		cop3530::SDAL<char>::iterator iter = l.begin();
		++iter;
		++iter;
		bool caught = false;
		try {
			iter++;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Iterating through elements with const iterator", "[SDAL_const_iteration]" ) {
	cop3530::SDAL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	l.push_front('A');
	const cop3530::SDAL<char> const_list = l;
	SECTION("Iterating through list, testing *, end, begin, =, and preincrement operator"){
		cop3530::SDAL<char>::const_iterator iter = const_list.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != const_list.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Non equal and equality operators work, along with postincrement operatior"){
			cop3530::SDAL<char>::const_iterator iter = const_list.begin();
			iter++;
			cop3530::SDAL<char>::const_iterator iter2 = const_list.begin();
			REQUIRE(iter != iter2);
			iter2++;
			REQUIRE(iter == iter2);
	}
}

TEST_CASE( "SDAL_Testing arrow operator with const iter", "[SDAL_arrow_operator_const_iter]" ) {
	cop3530::SDAL<Student> l;
	Student student;
	l.push_front(student);
	const cop3530::SDAL<Student> const_list = l;
	cop3530::SDAL<Student>::const_iterator iter = const_list.begin();
	REQUIRE(iter->grade == 0);

	SECTION("Throws exception when trying to use with a null array") {
		cop3530::SDAL<Student>::iterator iter2;
		bool caught = false;
		try{
			iter2->grade;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Testing const explicit constructor and exception caught with dereference operator when null", "[SDAL_explicit_const]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	const cop3530::SDAL<char> const_list = l;
	cop3530::SDAL<char>::const_iterator iter;
	bool caught = false;
	try {
		*iter;
	} catch(std::logic_error &le) {
		caught = true;
	}
	REQUIRE(caught == true);
}

TEST_CASE( "SDAL_Testing constructor const", "[SDAL_const_constructor]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	const cop3530::SDAL<char> const_list = l;
	cop3530::SDAL<char>::const_iterator iter = const_list.begin();
	cop3530::SDAL<char>::const_iterator iter2(iter);

	REQUIRE(*iter2 == 'X');

	SECTION("Throws exception when trying to use with a null array") {
		cop3530::SDAL<Student>::const_iterator iter;
		bool caught = false;
		try {
			iter->grade;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE("SDAL_Const iter-Testing increment operators for exceptions", "[SDAL_cont_incrementing]") {
	cop3530::SDAL<char> l;
	l.push_front('A');
	l.push_front('B');
	const cop3530::SDAL<char> const_list = l;
	SECTION("Preincrement operator throws exception when the node is null") {
		cop3530::SDAL<char>::const_iterator iter = const_list.begin();
		++iter;
		++iter;
		bool caught = false;
		try {
			++iter;
		} catch(std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
	SECTION("Postincrement operator throws exception when the node is null") {
		cop3530::SDAL<char>::const_iterator iter = const_list.begin();
		++iter;
		++iter;
		bool caught = false;
		try {
			iter++;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Replaces the specified element in the list", "[SDAL_replace]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Replaces the element when it exists") {
		l.push_front('X');
		l.push_front('X');
		REQUIRE(l.replace('A', 0) == 'X');
		REQUIRE(l.size() == 3);
	}
	SECTION("Doesn't replace if the index is greater than or equal to the size") {
		bool caught = false;
		l.push_front('X');
		l.push_front('X');
		try {
			l.replace('A', 3);
		} catch (std::out_of_range& oor) {
			caught = true;
			REQUIRE(l.size() == 3);
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Inserts the specified element in the list", "[SDAL_insert]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Inserts the element at the specified index") {
		l.push_front('X');
		l.push_front('X');
		l.insert('A', 0);
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.item_at(1) == 'X');
		REQUIRE(l.size() == 4);
	}
	SECTION("Doesn't insert if the index is greater than the size") {
		bool caught = false;
		l.push_front('X');
		l.push_front('X');
		try {
			l.insert('A', 4);
		} catch (std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(l.size() == 3);
		REQUIRE(caught == true);
	}
	SECTION("Inserts if the index is equal to the size") {
		l.push_front('X');
		l.push_front('X');
		l.insert('A', 3);
		REQUIRE(l.item_at(3) == 'A');
		REQUIRE(l.size() == 4);
	}
}

TEST_CASE( "SDAL_Pushes the specified element onto the front of list", "[SDAL_push_front]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Pushes the element to the front") {
		l.push_front('X');
		l.push_front('A');
		REQUIRE(l.item_at(0) == 'A');
	}
	SECTION("Pushes the element onto an empty list") {
		bool caught = false;
		l.pop_back();
		l.push_front('A');
		REQUIRE(l.item_at(0) == 'A');
	}
}

TEST_CASE( "SDAL_Pushes the specified element onto the back of list", "[SDAL_push_back]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Pushes the element to the back") {
		l.push_back('X');
		l.push_back('A');
		REQUIRE(l.item_at(2) == 'A');
	}
	SECTION("Pushes the element onto an empty list") {
		bool caught = false;
		l.pop_back();
		l.push_back('A');
		REQUIRE(l.item_at(0) == 'A');
	}
}

TEST_CASE( "SDAL_Pops the specified element from the front of the list", "[SDAL_pop_front]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Popping an element") {
		l.push_front('A');
		REQUIRE(l.pop_front() == 'A');
		REQUIRE(l.size() == 1);
		REQUIRE(l.item_at(0) == 'X');
	}

	SECTION("Popping the head element") {
		REQUIRE(l.pop_front() == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Popping with more than 50 elements") {
		l.pop_front();
		for (int i = 0; i < 51; i++) {
			l.push_back('X');
		}
		for (int i = 0; i < 51; i++) {
			l.pop_front();
		}
		l.push_back('A');
		REQUIRE(l.size() == 1);
		REQUIRE(l.item_at(0) == 'A');
	}

	SECTION("Popping from an empty list") {
		bool caught = false;
		l.pop_front();
		try{
			l.pop_front();
		} catch(std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Pops the specified element from the back of the list", "[SDAL_pop_back]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Popping an element") {
		l.push_front('A');
		REQUIRE(l.pop_back() == 'X');
		REQUIRE(l.size() == 1);
	}

	SECTION("Popping the head element") {
		REQUIRE(l.pop_back() == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Popping with more than 50 elements") {
		l.pop_front();
		for (int i = 0; i < 51; i++) {
			l.push_front('X');
		}
		for (int i = 0; i < 51; i++) {
			l.pop_back();
		}
		l.push_front('A');
		REQUIRE(l.size() == 1);
		REQUIRE(l.item_at(0) == 'A');
	}

	SECTION("Popping from an empty list") {
		bool caught = false;
		l.pop_front();
		try{
			l.pop_back();
		} catch(std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Removes the specified element from the specified index", "[SDAL_pop_remove]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Removing an element") {
		l.push_front('X');
		l.push_back('A');
		l.push_back('B');
		REQUIRE(l.remove(2) == 'A');
		REQUIRE(l.item_at(2) == 'B');
		REQUIRE(l.size() == 3);
	}

	SECTION("Removing the head element") {
		REQUIRE(l.remove(0) == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Removing from an empty list") {
		bool caught = false;
		l.pop_front();
		try{
			l.remove(0);
		} catch(std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}

	SECTION("Removing 1 past the last index") {
		bool caught = false;
		try {
			l.remove(1);
		} catch (std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}

	SECTION("Removing with more than 50 elements") {
		l.pop_front();
		for (int i = 0; i < 50; i++) {
			l.push_front('X');
		}
		l.push_back('A');
		REQUIRE(l.remove(50) == 'A');
	}
}

TEST_CASE( "SDAL_Finds the item at the specified position in the list", "[SDAL_item_at]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Retrieving an element") {
		l.push_front('A');
		REQUIRE(l.item_at(1) == 'X');
		REQUIRE(l.size() == 2);
	}

	SECTION("Retrieving an element at an invalid position") {
		bool caught = false;
		try {
			l.item_at(1);
		} catch (std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SDAL_Checks if the list is empty", "[SDAL_is_empty]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Returns true if empty list") {
		l.pop_front();
		REQUIRE(l.is_empty() == true);
	}

	SECTION("Returns false if there are elements in the list") {
		REQUIRE(l.is_empty() == false);
	}
}

TEST_CASE( "SDAL_Returns the size of the list", "[SDAL_size]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Returns 0 if there are no elements") {
		l.pop_front();
		REQUIRE(l.size() == 0);
	}

	SECTION("Returns the size") {
		REQUIRE(l.size() == 1);
	}
	SECTION("Returns 3 if there are 3 elements") {
		l.push_front('X');
		l.push_front('X');
		REQUIRE(l.size() == 3);
	}
}

TEST_CASE( "SDAL_Clears the entire list", "[SDAL_clear]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Returns 0 if there are no elements") {
		l.push_front('X');
		l.push_front('X');
		l.clear();
		REQUIRE(l.size() == 0);
	}

	SECTION("Resizes array correctly") {
		for(int i = 0; i < 320; i++) {
			l.push_front('X');
		}
		for (int i = 0; i < 200; i++) {
			l.pop_front();
		}
		l.clear();
		REQUIRE(l.size() == 0);
	}

	SECTION("Returns if there are no elements") {
		l.pop_back();
		l.clear();
		REQUIRE(l.size() == 0);
	}
}

TEST_CASE( "SDAL_Returns the element at the specified index", "[SDAL_operator[]" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	SECTION("Returns the head element") {
		REQUIRE(l[0] == 'X');
	}

	SECTION("Returns the element at the index") {
		l.push_front('X');
		l.push_front('A');
		l.push_front('X');
		REQUIRE(l[1] == 'A');
	}

	SECTION("Correctly throws exception with invalid indices") {
		bool caught = false;
			l.pop_front();
			try {
				l[0];
			} catch(std::out_of_range& oor) {
				caught = true;
			}
			REQUIRE(caught == true);
		}
	SECTION("Retrieves correct element when more than 50 elements exist") {
		bool caught = false;
		l.pop_front();
		for (int i = 0; i < 50; i++) {
			l.push_front('X');
		}
		l.push_back('A');
		REQUIRE(l[50] == 'A');
	}
}

TEST_CASE( "SDAL_Returns the const element at the specified index", "[SDAL_operator[]_const" ) {
	cop3530::SDAL<char> l;
	l.push_front('X');
	const cop3530::SDAL<char> const_list = l;
	SECTION("Returns the head element") {
		REQUIRE(const_list[0] == 'X');
	}

	SECTION("Returns the element at the index") {
		l.push_front('X');
		l.push_front('A');
		l.push_front('X');
		const cop3530::SDAL<char> const_list2 = l;
		REQUIRE(const_list2[1] == 'A');
	}

	SECTION("Correctly throws exception with invalid indices") {
		bool caught = false;
			l.pop_front();
			const cop3530::SDAL<char> const_list3 = l;
			try {
				const_list3[0];
			} catch(std::out_of_range& oor) {
				caught = true;
			}
			REQUIRE(caught == true);
		}

		SECTION("Retrieves correct element when more than 50 elements exist") {
			bool caught = false;
			l.pop_front();
			for (int i = 0; i < 50; i++) {
				l.push_front('X');
			}
			l.push_back('A');
			const cop3530::SDAL<char> const_list4 = l;
			REQUIRE(const_list4[50] == 'A');
		}
}

TEST_CASE( "SDAL_Grows and shrinks as expected", "[SDAL]" ) {
	cop3530::SDAL<char> l;
	for(int i = 0; i < 400; i++) {
		l.push_front('X');
	}
	for(int i = 0; i < 250; i++) {
			l.pop_back();
		}

	REQUIRE(l.size() == 150);
}

TEST_CASE( "SDAL_Prints the elements in the correct format", "[SDAL_print" ) {
	//for this method, assertions are not possible, so looking at the output is how I verified it.
	cop3530::SDAL<char> l;
	for(int i = 0; i < 60;i++){
		l.push_front('X');
	}
	l.push_front('A');
	l.print(std::cout);
}

template <typename T>
bool equals(const T& a, const T& b) {
	if(a == b){
		return true;
	}
	return false;
}
TEST_CASE( "SDAL_Determines if the element is contained in the list", "[SDAL_contains]" ) {
	cop3530::SDAL<char> l;
	SECTION("Determines if an element is in the list") {
		for (int i = 0; i < 60; i++) {
			l.push_front('X');
		}
		l.push_back('A');
		REQUIRE(l.contains('A', equals));
		REQUIRE(!l.contains('B', equals));
	}

	SECTION("Returns false if the list is empty") {
		REQUIRE(!(l.contains('A', equals)));
	}
}

