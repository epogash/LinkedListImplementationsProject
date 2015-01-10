#include "Catch.hpp"
#include "SSLL.h"
#include <stdexcept>
struct Student {
	public:
		int grade;
		Student() {
			grade = 0;
		}
};
TEST_CASE( "Iterating through elements", "[SSLL_iteration]" ) {
	cop3530::SSLL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	SECTION("Iterating through list, testing *, end, begin, = and preincrement operator"){
		l.push_front('A');
		cop3530::SSLL<char>::iterator iter = l.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != l.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Non equal and equality operators work, testing postincrement operator"){
			l.push_front('A');
			l.push_front('A');
			cop3530::SSLL<char>::iterator iter = l.begin();
			iter++;
			cop3530::SSLL<char>::iterator iter2 = l.begin();
			REQUIRE(iter != iter2);
			iter2++;
			REQUIRE(iter == iter2);
	}
}

TEST_CASE("SSLL_Testing increment operators for exceptions", "[SSLL_incrementing]") {
	cop3530::SSLL<char> l;
	l.push_front('A');
	l.push_front('B');
	SECTION("Preincrement operator throws exception when the node is null") {
		cop3530::SSLL<char>::iterator iter = l.begin();
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
		cop3530::SSLL<char>::iterator iter = l.begin();
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

TEST_CASE( "SSLL_Testing explicit constructor and exception caught with dereference operator when null", "[SSLL_explicit]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	cop3530::SSLL<char>::iterator iter;
	bool caught = false;
	try {
		*iter = 'X';
	} catch(std::logic_error &le) {
		caught = true;
	}
	REQUIRE(caught == true);
}

TEST_CASE( "SSLL_Testing constructor", "[SSLL_constructor]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	cop3530::SSLL<char>::iterator iter = l.begin();
	cop3530::SSLL<char>::iterator iter2(iter);

	REQUIRE(*iter2 == 'X');
}

TEST_CASE( "SSLL_Testing arrow operator", "[SSLL_arrow_operator]" ) {
	cop3530::SSLL<Student> l;
	Student student;
	l.push_front(student);
	cop3530::SSLL<Student>::iterator iter = l.begin();
	REQUIRE(iter->grade == 0);

	SECTION("Throws exception when trying to use with a null node") {
		cop3530::SSLL<Student>::iterator iter2;
		bool caught = false;
		try {
			iter2->grade;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "SSLL_Iterating through elements with const iterator", "[SSLL_const_iteration]" ) {
	cop3530::SSLL<char> l;
	for (int i = 0; i < 60; i++) {
		l.push_front('X');
	}
	l.push_front('A');
	const cop3530::SSLL<char> const_list = l;
	SECTION("Iterating through list, testing *, end, begin, =, and preincrement operator"){
		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
		REQUIRE(*iter == 'A');
		int count = 0;
		while (iter != const_list.end()) {
			++count;
			++iter;
		}
		REQUIRE(count == 61);
	}

	SECTION("Non equal and equality operators work"){
			cop3530::SSLL<char>::const_iterator iter = const_list.begin();
			iter++;
			cop3530::SSLL<char>::const_iterator iter2 = const_list.begin();
			REQUIRE(iter != iter2);
			iter2++;
			REQUIRE(iter == iter2);
	}
}

TEST_CASE( "SSLL_Testing const explicit constructor and exception caught with dereference operator when null", "[SSLL_explicit_const]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	const cop3530::SSLL<char> const_list = l;
	cop3530::SSLL<char>::const_iterator iter;
	bool caught = false;
	try {
		*iter;
	} catch(std::logic_error &le) {
		caught = true;
	}
	REQUIRE(caught == true);
}

TEST_CASE( "SSLL_Testing constructor const", "[SSLL_const_constructor]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	const cop3530::SSLL<char> const_list = l;
	cop3530::SSLL<char>::const_iterator iter = const_list.begin();
	cop3530::SSLL<char>::const_iterator iter2(iter);

	REQUIRE(*iter2 == 'X');
}

TEST_CASE( "SSLL_Testing arrow operator with const iter", "[SSLL_arrow_operator_const_iter]" ) {
	cop3530::SSLL<Student> l;
	Student student;
	l.push_front(student);
	const cop3530::SSLL<Student> const_list = l;
	cop3530::SSLL<Student>::const_iterator iter = const_list.begin();
	REQUIRE(iter->grade == 0);

	SECTION("Throws exception when trying to use with a null node") {
		cop3530::SSLL<Student>::const_iterator iter2;
		bool caught = false;
		try {
			iter2->grade;
		} catch (std::logic_error &le) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE("SSLL_Const iter-Testing increment operators for exceptions", "[SSLL_cont_incrementing]") {
	cop3530::SSLL<char> l;
	l.push_front('A');
	l.push_front('B');
	const cop3530::SSLL<char> const_list = l;
	SECTION("Preincrement operator throws exception when the node is null") {
		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
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
		cop3530::SSLL<char>::const_iterator iter = const_list.begin();
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

TEST_CASE( "Replacing elements", "[SSLL_replace]") {
	cop3530::SSLL<char> l;
	l.push_front('X');

	SECTION("Catch exception when the list is empty and replace is called") {
		bool caught = false;
		l.pop_back();
		try {
			l.replace('A', 0);
		} catch(std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}

	SECTION("Catch exception when replace is called on an invalid element") {
		bool caught = false;
		try {
			l.replace('A', 1);
		} catch (std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}

	SECTION("Returns the original element when an element is replaced") {
		REQUIRE(l.replace('A', 0) == 'X');
	}

	SECTION("Replaces the only element if the size is 1") {
		l.replace('A', 0);
		REQUIRE(l.pop_back() == 'A');
	}

	SECTION("Correctly replaces the head element when there is more than 1 element") {
		l.push_front('X');
		l.replace('A', 0);
		REQUIRE(l.pop_front() == 'A');
	}

	SECTION("Correctly replaces the tail element when there is more than 1 element") {
		l.push_front('X');
		l.replace('A', 1);
		REQUIRE(l.pop_back() == 'A');
	}
}

TEST_CASE( "Inserting elements", "[SSLL_insert]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');

	SECTION("Allow inserting anywhere in the list") {
		l.push_front('X');
		l.push_front('X');
		l.insert('A', 1);
		REQUIRE(l.item_at(1) == 'A');
	}

	SECTION("Inserting at 1 past the last index occupied") {
		l.insert('A', 1);
		REQUIRE(l.item_at(1) == 'A');
	}

	SECTION("Inserting at the head") {
		l.insert('A', 0);
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.item_at(1) == 'X');
	}

	SECTION("Inserting at more than 1 past the last index occupied") {
		bool caught = false;
		try {
			l.insert('A', 2);
		} catch(std::out_of_range& oor) {
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "Pushing Elements to front", "[SSLL_push_front]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Pushing an element") {
		l.push_front('A');
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.item_at(1) == 'X');
	}
	SECTION("Pushing onto empty list") {
		l.pop_front();
		l.push_front('A');
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.size() == 1);
	}
}

TEST_CASE( "Pushing Elements to back", "[SSLL_push_back]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Pushing an element") {
		l.push_back('A');
		REQUIRE(l.item_at(1) == 'A');
		REQUIRE(l.item_at(0) == 'X');
	}
	SECTION("Pushing onto empty list") {
		l.pop_front();
		l.push_back('A');
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.size() == 1);
	}
}

TEST_CASE( "Popping elements from front", "[SSLL_pop_front]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Popping an element") {
		l.push_front('A');
		REQUIRE(l.pop_front() == 'A');
		REQUIRE(l.size() == 1);
		REQUIRE(l.item_at(0) == 'X');
	}
	SECTION("Popping head element") {
		REQUIRE(l.pop_front() == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Popping from empty list") {
		bool caught = false;
		l.pop_front();
		try {
			l.pop_front();
		} catch (std::out_of_range& oor){
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "Popping elements from back", "[SSLL_pop_back]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Popping an element") {
		l.push_front('A');
		REQUIRE(l.pop_back() == 'X');
		REQUIRE(l.size() == 1);
	}
	SECTION("Popping head element") {
		REQUIRE(l.pop_back() == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Popping from empty list") {
		bool caught = false;
		l.pop_back();
		try {
			l.pop_back();
		} catch (std::out_of_range& oor){
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "Removing an element at a position", "[SSLL_remove]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Removing an element") {
		l.push_front('A');
		l.push_front('A');
		REQUIRE(l.remove(0) == 'A');
		REQUIRE(l.item_at(0) == 'A');
		REQUIRE(l.item_at(1) == 'X');
		REQUIRE(l.size() == 2);
	}
	SECTION("Removing head element") {
		REQUIRE(l.remove(0) == 'X');
		REQUIRE(l.size() == 0);
	}

	SECTION("Removing from empty list") {
		bool caught = false;
		l.remove(0);
		try {
			l.remove(0);
		} catch (std::out_of_range& oor){
			caught = true;
		}
		REQUIRE(caught == true);
	}

	SECTION("Removing from 1 past last index") {
		bool caught = false;
		try {
			l.remove(1);
		} catch (std::out_of_range& oor){
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "Retrieving items within the list", "[SSLL_item_at]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Retrieving an element") {
		l.push_front('A');
		REQUIRE(l.item_at(1) == 'X');
	}

	SECTION("Retrieving an element at an invalid position") {
		bool caught = false;
		try {
			l.item_at(1);
		} catch (std::out_of_range& oor){
			caught = true;
		}
		REQUIRE(caught == true);
	}
}

TEST_CASE( "Checking if the list is empty", "[SSLL_is_empty]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Returns true if empty list") {
		l.pop_front();
		REQUIRE(l.is_empty() == true);
	}

	SECTION("Returns false if there are elements in the list") {
		REQUIRE(l.is_empty() == false);
	}
}

TEST_CASE( "Returns the correct size of the list", "[SSLL_size]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Returns the size") {
		REQUIRE(l.size() == 1);
	}

	SECTION("Returns 0 if there are no elements") {
		l.pop_back();
		REQUIRE(l.size() == 0);
	}

	SECTION("Returns 3 if there are 3 elements") {
		l.push_front('X');
		l.push_front('X');
		REQUIRE(l.size() == 3);
	}
}

TEST_CASE( "Clears the entire list", "[SSLL_clear]" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	SECTION("Clears the list") {
		l.push_front('X');
		l.push_front('X');
		l.clear();
		REQUIRE(l.size() == 0);
	}

	SECTION("Returns if there are no elements") {
		l.pop_back();
		l.clear();
		REQUIRE(l.size() == 0);
	}
}

TEST_CASE( "Returns the element at the specified index", "[SSLL_operator[]" ) {
	cop3530::SSLL<char> l;
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
}

TEST_CASE( "Returns the const element at the specified index", "[SSLL_operator[]_const" ) {
	cop3530::SSLL<char> l;
	l.push_front('X');
	const cop3530::SSLL<char> const_list = l;
	SECTION("Returns the head element") {
		REQUIRE(const_list[0] == 'X');
	}

	SECTION("Returns the element at the index") {
		l.push_front('X');
		l.push_front('A');
		l.push_front('X');
		const cop3530::SSLL<char> const_list2 = l;
		REQUIRE(const_list2[1] == 'A');
	}

	SECTION("Correctly throws exception with invalid indices") {
		bool caught = false;
			l.pop_front();
			const cop3530::SSLL<char> const_list3 = l;
			try {
				const_list3[0];
			} catch(std::out_of_range& oor) {
				caught = true;
			}
			REQUIRE(caught == true);
		}
}


TEST_CASE( "SSLL_Prints the elements in the correct format", "[SSLL_print" ) {
	//for this method, assertions are not possible, so looking at the output is how I verified it.
	cop3530::SSLL<char> l;
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

TEST_CASE( "SSLL_Determines if the element is contained in the list", "[SSLL_contains]" ) {
	cop3530::SSLL<char> l;
	SECTION("Determines if an element is in the list") {
		for (int i = 0; i < 60; i++) {
			l.push_front('X');
		}
		l.push_back('A');
		REQUIRE(l.contains('A', equals));
		REQUIRE(!l.contains('B', equals));
	}

	SECTION("Returns false if the list is empty") {
		REQUIRE(!l.contains('A', equals));
	}
}
