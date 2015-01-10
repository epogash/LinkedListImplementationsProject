#include <iostream>
#include <stdexcept>

namespace cop3530 {

template<typename T>
class SDAL {
private:
	T* increaseArray(T array[]) {
		int newSize = arraySize * 1.5;
		T* largerArray = new T[newSize];
		for (int i = 0; i < newSize; i++) {
			largerArray[i] = array[i];
		}
		delete[] array;
		arraySize = newSize;
		return largerArray;
	}
	T* decreaseArray(T array[]) {
		int newSize = arraySize * 0.5;
		T* smallerArray = new T[newSize];
		for (int i = 0; i < newSize; i++) {
			smallerArray[i] = array[i];
		}
		delete[] array;
		arraySize = newSize;
		return smallerArray;
	}
	T* array;
	int arraySize;
	int currentCount;
public:

	class SDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		// inheriting from std::iterator<std::forward_iterator_tag, T>
		// automagically sets up these typedefs...
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		// but not these typedefs...
		typedef SDAL_Iter self_type;
		typedef SDAL_Iter& self_reference;

	private:
		T* here;
		const SDAL* sdal;
	public:
		explicit SDAL_Iter(T* start = NULL, SDAL* list = NULL) :
				here(start), sdal(list) {
		}
		SDAL_Iter(const SDAL_Iter& src) :
				here(src.here), sdal(src.sdal) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null array");
			}
			return *here;
		}

		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't use operator with a null array");
			}
			return here;
		}

		self_reference operator=(const SDAL_Iter& src) {
			if (*this == src) {
				return *this;
			}
			sdal = src.sdal;
			here = src.here;
			return *this;
		}

		self_reference operator++() {
			if(!(here < sdal->array + sdal->currentCount)) {
				throw std::logic_error("cannot increment a null array slot");
			}
			++here;
			return *this;
		} // preincrement

		self_type operator++(int) {
			if(!(here < sdal->array + sdal->currentCount)) {
				throw std::logic_error("cannot increment a null array slot");
			}
			SDAL_Iter results(*this);
			++here;
			return results;
		} // postincrement

		bool operator==(const SDAL_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const SDAL_Iter& rhs) const {
			return here != rhs.here;
		}
	}; // end SSLL_Iter
	class SDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		// inheriting from std::iterator<std::forward_iterator_tag, T>
		// automagically sets up these typedefs...
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		// but not these typedefs...
		typedef SDAL_Const_Iter self_type;
		typedef SDAL_Const_Iter& self_reference;

	private:
		const T* here;
		const SDAL* sdal;
	public:
		explicit SDAL_Const_Iter(T* start = NULL, const SDAL* list = NULL) :
				here(start), sdal(list){
		}
		SDAL_Const_Iter(const SDAL_Const_Iter& src) :
				here(src.here), sdal(src.sdal) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null array");
			}
			return *here;
		}
		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null array");
			}
			return here;
		}

		self_reference operator=(const SDAL_Const_Iter& src) {
			if (*this == src) {
				return *this;
			}
			sdal = src.sdal;
			here = src.here;
			return *this;
		}

		self_reference operator++() {
			if(!(here < sdal->array + sdal->currentCount)) {
				throw std::logic_error("cannot increment a null array slot");
			}
			++here;
			return *this;
		} // preincrement

		self_type operator++(int) {
			if(!(here < sdal->array + sdal->currentCount)) {
				throw std::logic_error("cannot increment a null array slot");
			}
			SDAL_Const_Iter results(*this);
			++here;
			return results;
		} // postincrement

		bool operator==(const SDAL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const SDAL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
	}; // end SDAL_Iter

	typedef std::size_t size_t;
	typedef T value_type;
	typedef SDAL_Iter iterator;
	typedef SDAL_Const_Iter const_iterator;

	iterator begin() {
		return SDAL_Iter(array, this);
	}
	iterator end() {
		return SDAL_Iter(array + currentCount, this);
	}

	const_iterator begin() const {
		return SDAL_Const_Iter(array, this);
	}
	const_iterator end() const {
		return SDAL_Const_Iter(array + currentCount, this);
	}

	SDAL() {
		array = new T[50];
		arraySize = 50;
		currentCount = 0;
	}

	SDAL(const SDAL& src) {
		currentCount = src.currentCount;
		array = new T[src.arraySize];
		arraySize = src.arraySize;
		int i = 0;
		while (i < src.currentCount) {
			array[i] = src.array[i];
			i++;
		}
	}

	SDAL(int size) {
		array = new T[size];
		arraySize = size;
		currentCount = 0;
	}

	SDAL& operator=(const SDAL& src) {
		if (&src == this) // check for self-assignment
			return *this; // do nothing

		delete[] array;
		array = new T[src.arraySize];
		currentCount = src.currentCount;
		arraySize = src.arraySize;
		int i = 0;
		while (i < src.currentCount) {
			array[i] = src.array[i];
			i++;
		}
		return *this;
	}

	//--------------------------------------------------
	~SDAL() {
		delete[] array;
	}

	T replace(const T& element, int position) {
		if (position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't replace a value if the position is not a valid index");
		}
		T data = array[position];
		array[position] = element;
		return data;
	}

	//--------------------------------------------------
	void insert(const T& element, int position) {
		if (position < 0 || position > size()) {
			throw std::out_of_range("Can't insert at an invalid index");
		}
		int i = arraySize - 1;
		while (i > position) {
			array[i] = array[i - 1];
			i--;
		}
		array[position] = element;
		if (currentCount == arraySize - 1) {
			array = increaseArray(array);
		}
		currentCount++;
	}

	//--------------------------------------------------
	void push_front(const T& element) {
		int i = arraySize - 1;
		while (i > 0) {
			array[i] = array[i - 1];
			i--;
		}
		array[0] = element;
		if (currentCount == arraySize - 1) {
			array = increaseArray(array);
		}
		currentCount++;
	}

	//--------------------------------------------------
	void push_back(const T& element) {
		array[currentCount] = element;
		if (currentCount == arraySize - 1) {
			array = increaseArray(array);
		}
		currentCount++;
	}

	//--------------------------------------------------
	T pop_front() {
		if (size() == 0) {
			throw std::out_of_range("Can't pop a value if the list is empty");
		}
		T data = array[0];
		int i = 0;
		while (i < arraySize) {
			array[i] = array[i + 1];
			i++;
		}
		currentCount--;
		if (currentCount < static_cast<float>(arraySize) / 2.0f
				&& arraySize >= 100) {
			array = decreaseArray(array);
		}
		return data;
	}

	//--------------------------------------------------
	T pop_back() {
		if (size() == 0) {
			throw std::out_of_range("Can't pop a value if the list is empty");
		}
		T data = array[currentCount - 1];
		currentCount--;
		if (currentCount < static_cast<float>(arraySize) / 2.0f
				&& arraySize >= 100) {
			array = decreaseArray(array);
		}
		return data;
	}

	//--------------------------------------------------
	T remove(int position) {
		if (position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't remove a value if the list is empty");
		}
		T data = array[position];
		int i = position;
		while (i < currentCount - 1) {
			array[i] = array[i + 1];
			i++;
		}
		currentCount--;
		if (currentCount < static_cast<float>(arraySize) / 2.0f
				&& arraySize >= 100) {
			array = decreaseArray(array);
		}
		return data;
	}

	//--------------------------------------------------
	T item_at(int position) const {
		if (position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't remove a value if the list is empty");
		}
		return array[position];
	}

	//--------------------------------------------------
	bool is_empty() const {
		if (currentCount == 0) {
			return true;
		}
		return false;
	}

	//--------------------------------------------------
	size_t size() const {
		size_t size = currentCount;
		return size;
	}

	//--------------------------------------------------
	void clear() {
		for (int i = 0; i < arraySize; i++) {
			array[i] = 0;
		}
		currentCount = 0;
		while (currentCount < static_cast<float>(arraySize) / 2.0f
				&& arraySize >= 100) {
			array = decreaseArray(array);
		}
	}

	//--------------------------------------------------
	bool contains(const T& element, bool equals(const T& a, const T& b)) const {
		for (int i = 0; i < arraySize; i++) {
			if (equals(array[i], element)) {
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------
	std::ostream& print(std::ostream& out) const {
		if (currentCount == 0) {
			out << "<empty list>" << std::endl;
			return out;
		}
		out << "[";
		for (int i = 0; i < currentCount; i++) {
			out << array[i];
			if (currentCount != i + 1) {
				out << ",";
			}
		}
		out << "]" << std::endl;
		return out;
	}

	T& operator[](int i) {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't get a value at an invalid index");
		}
		return array[i];
	}

	T const& operator[](int i) const {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't get a value at an invalid index");
		}
		return array[i];
	}

};
}
