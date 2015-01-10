
#include <iostream>
#include <stdexcept>

namespace cop3530 {

template<typename T>
class CDAL {
private:
	struct Node {
		Node* next;
		T* data;
		 ~Node(){
			 delete[] data;
		 }
	};

	void addNodeWithArray() {
		numberOfNodes++;
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		Node* newNode = new Node();
		newNode->next = NULL;
		newNode->data = new T[50];
		temp->next = newNode;
	}
	void deallocateHalfOfArrays() {
		int numberOfUsedNodes = 1;
		int tempMaxIndex = maxIndex;
		while (tempMaxIndex > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			tempMaxIndex -= 50; //subtract the total amount of elements in the array
			numberOfUsedNodes++; //increase the amount of nodes to progress
		}
		int numberOfUnusedNodes = numberOfNodes - numberOfUsedNodes;
		while (numberOfUnusedNodes > static_cast<float>(numberOfNodes) / 2.0f) {
			int numberToDeallocate = numberOfUnusedNodes / 2;
			Node* temp = head;
			for(int i = 0; i < numberOfUsedNodes - 1; i++) {
				temp = temp->next; //advance to one position before the node to be removed
			}
			for (int i = 0; i < numberToDeallocate; i++) {
				Node* nodeToDelete = temp->next;
				temp->next = temp->next->next;
				delete nodeToDelete;
				numberOfNodes--;
				numberOfUnusedNodes--;
			}
		}
	}
	int maxIndex;
	Node* head;
	T* array;
	int numberOfNodes;
public:

	class CDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef CDAL_Iter self_type;
		typedef CDAL_Iter& self_reference;

	private:
		Node* here;
		int currentIndex;

	public:
		explicit CDAL_Iter(Node* start = NULL, int index = 0) :
				here(start), currentIndex(index) {
		}
		CDAL_Iter(const CDAL_Iter& src) :
				here(src.here), currentIndex(src.currentIndex) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return here->data[currentIndex];
		}

		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return &here->data[currentIndex];
		}

		self_reference operator=(const CDAL_Iter& src) {
			if (*this == src) {
				return *this;
			}
			here = src.here;
			currentIndex = src.currentIndex;
			return *this;
		}

		self_reference operator++() {
			++currentIndex;
			if (currentIndex == 50 && here->next) {
				here = here->next;
				currentIndex = 0;
			}
			return *this;
		} // preincrement

		self_type operator++(int) {
			CDAL_Iter results(*this);
			++(*this);
			return results;
		} // postincrement

		bool operator==(const CDAL_Iter& rhs) const {
			return here == rhs.here && currentIndex == rhs.currentIndex;
		}

		bool operator!=(const CDAL_Iter& rhs) const {
			return !(here == rhs.here && currentIndex == rhs.currentIndex);
		}
	}; // end SSLL_Iter
	class CDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef CDAL_Const_Iter self_type;
		typedef CDAL_Const_Iter& self_reference;

	private:
		const Node* here;
		int currentIndex;

	public:
		explicit CDAL_Const_Iter(Node* start = NULL, int index = 0) :
				here(start), currentIndex(index) {
		}
		CDAL_Const_Iter(const CDAL_Const_Iter& src) :
				here(src.here), currentIndex(src.currentIndex) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return here->data[currentIndex];
		}
		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return &here->data[currentIndex];
		}

		self_reference operator=(const CDAL_Const_Iter& src) {
			if (*this == src) {
				return *this;
			}
			here = src.here;
			currentIndex = src.currentIndex;
			return *this;
		}

		self_reference operator++() {
			++currentIndex;
			if (currentIndex == 50 && here->next) {
				here = here->next;
				currentIndex = 0;
			}
			return *this;
		} // preincrement

		self_type operator++(int) {
			CDAL_Const_Iter results(*this);
			++(*this);
			return results;
		} // postincrement

		bool operator==(const CDAL_Const_Iter& rhs) const {
			return here == rhs.here && currentIndex == rhs.currentIndex;
		}

		bool operator!=(const CDAL_Const_Iter& rhs) const {
			return !(here == rhs.here && currentIndex == rhs.currentIndex);
		}
	}; // end SSLL_Iter

	typedef std::size_t size_t;
	typedef T value_type;
	typedef CDAL_Iter iterator;
	typedef CDAL_Const_Iter const_iterator;

	iterator begin() {
		return CDAL_Iter(head, 0);
	}

	iterator end() {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return CDAL_Iter(temp, maxIndex % 50);
	}

	const_iterator begin() const {
		return CDAL_Const_Iter(head, 0);
	}
	const_iterator end() const {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return CDAL_Const_Iter(temp, maxIndex % 50);
	}

	CDAL() {
		head = new Node();
		this->array = new T[50];
		head->data = this->array;
		head->next = NULL;
		maxIndex = 0;
		numberOfNodes = 1;
	}

	CDAL( const CDAL& src ) {
		head = new Node();
		this->array = new T[50];
		head->data = this->array;
		head->next = NULL;
		maxIndex = 0;
		numberOfNodes = 1;
		for(int i = 0; i < src.maxIndex; i++) {
			push_back(src.item_at(i));
		}
	}

	~CDAL() {
		Node* temp = head;
		while (temp != NULL) {
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
		head = NULL;
	}

	CDAL& operator=(const CDAL& src) {
		if (&src == this) // check for self-assignment
			return *this; // do nothing
		delete this;
		head = new Node();
		this->array = new T[50];
		head->data = this->array;
		head->next = NULL;
		maxIndex = 0;
		numberOfNodes = 1;
		for (int i = 0; i < src.maxIndex; i++) {
			push_back(src.item_at(i));
		}
		return *this;
	}

	T replace(const T& element, int position) {
		if (size() == 0 || position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't replace a value if the list is empty");
		}
		int nodeCount = 0;
		while (position > 49) { //while the position is greater than the amount of indices in array(inclusive of 0)
			position -= 50; //subtract the total amount of elements in the array
			nodeCount++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodeCount; i++) {
			temp = temp->next; //increment to correct node
		}
		T* arrayWithPosition = temp->data;
		T data = arrayWithPosition[position];
		arrayWithPosition[position] = element;
		return data;
	}

	//--------------------------------------------------
	void insert(const T& element, int position) {
		if (position > size() || position < 0) {
			throw std::out_of_range(
					"Can't replace a value if the list is empty");
		}
		if (maxIndex != 0 && maxIndex % 49 == 0) {
			addNodeWithArray();
		}
		int indexToInsert = position;
		int nodesToProgress = 0;
		while (indexToInsert > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			indexToInsert -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodesToProgress; i++) {
			temp = temp->next;
		}
		T* arrayToInsert = temp->data;

		int i = maxIndex;
		maxIndex++;
		int startIndexForMoving = maxIndex;
		while (startIndexForMoving > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			startIndexForMoving -= 50; //subtract the total amount of elements in the array
		}

		int numberOfNodesToMove = numberOfNodes - nodesToProgress;
		while (i >= position) {
			if (startIndexForMoving == 0) {
				Node* temp = head;
				for (int i = 0; i < numberOfNodesToMove + nodesToProgress - 2;
						i++) { //go to second to last node
					temp = temp->next;
				}
				T* arrayAtPreviousNode = temp->data;
				temp = temp->next;
				T* arrayAtNextNode = temp->data;
				arrayAtNextNode[0] = arrayAtPreviousNode[49];
				startIndexForMoving = 49;
				numberOfNodesToMove--;
			} else {
				Node* temp = head;
				for (int i = 0; i < numberOfNodesToMove + nodesToProgress - 1;
						i++) { //go to last node
					temp = temp->next;
				}
				T* arrayAtLastNode = temp->data;
				arrayAtLastNode[startIndexForMoving] =
						arrayAtLastNode[startIndexForMoving - 1];
				startIndexForMoving--;
			}
			i--;
		}
		arrayToInsert[indexToInsert] = element;
	}

	//--------------------------------------------------
	void push_front(const T& element) {
		if (maxIndex != 0 && maxIndex % 49 == 0) {
			addNodeWithArray();
		}
		int indexToInsert = 0;
		Node* temp = head;
		T* arrayToInsert = temp->data;
		int i = maxIndex;
		maxIndex++;
		int startIndexForMoving = maxIndex;
		while (startIndexForMoving > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			startIndexForMoving -= 50; //subtract the total amount of elements in the array
		}

		int numberOfNodesToMove = numberOfNodes;
		temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		while (i >= 0) {
			if (startIndexForMoving == 0) {
				Node* temp = head;
				for (int i = 0; i < numberOfNodesToMove - 2; i++) { //go to second to last node
					temp = temp->next;
				}
				T* arrayAtPreviousNode = temp->data;
				temp = temp->next;
				T* arrayAtNextNode = temp->data;
				arrayAtNextNode[0] = arrayAtPreviousNode[49];
				startIndexForMoving = 49;
				numberOfNodesToMove--;
			} else {
				Node* temp = head;
				for (int i = 0; i < numberOfNodesToMove - 1; i++) { //go to last node
					temp = temp->next;
				}
				T* arrayAtLastNode = temp->data;
				arrayAtLastNode[startIndexForMoving] =
						arrayAtLastNode[startIndexForMoving - 1];
				startIndexForMoving--;
			}
			i--;
		}
		arrayToInsert[indexToInsert] = element;
	}

	//--------------------------------------------------
	void push_back(const T& element) {
		if (maxIndex != 0 && maxIndex % 49 == 0) {
			addNodeWithArray();
		}
		int indexToInsert = maxIndex;
		maxIndex++;
		int nodesToProgress = 0;
		while (indexToInsert > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			indexToInsert -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodesToProgress; i++) {
			temp = temp->next;
		}
		T* arrayToInsert = temp->data;
		arrayToInsert[indexToInsert] = element;
	}

	//--------------------------------------------------
	T pop_front() {
		//NEED TO SHIFT ELEMENTS LEFT -NOTE MAX INDEX IS 1 MORE THAN ARRAY AMOUNT
		if(!head || maxIndex == 0) {
			 throw std::out_of_range("Can't pop a value if the list is empty");
		}
		T data = head->data[0];
		int i = 0;
		Node* temp = head;
		Node* nextNode;
		int currentCount = 0;
		while (currentCount < maxIndex) {
			if(i == 49) {
				nextNode = temp->next;
				T dataToShiftLeft = nextNode->data[0];
				temp->data[49] = dataToShiftLeft;
				temp = temp->next;
				i = 0;
			} else {
				temp->data[i] = temp->data[i + 1];
				i++;
			}
			currentCount++;
		}
		maxIndex--;
		deallocateHalfOfArrays();
		return data;
	}

	//--------------------------------------------------
	T pop_back() {
		if(!head || maxIndex == 0)  {
			 throw std::out_of_range("Can't pop a value if the list is empty");
		}
		maxIndex--;
		int indexToPop = maxIndex;
		int nodesToProgress = 0;
		while (indexToPop > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			indexToPop -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodesToProgress; i++) {
			temp = temp->next;
		}
		T* arrayToPop = temp->data;
		T data = arrayToPop[indexToPop];
		deallocateHalfOfArrays();
		return data;
	}

	//--------------------------------------------------
	T remove(int position) {
		if (!head || position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't remove a value if the list is empty");
		}
		int indexToRemove = position;
		int currentCount = position;
		int nodesToProgress = 0;
		while (indexToRemove > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			indexToRemove -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodesToProgress; i++) {
			temp = temp->next;
		}
		T* arrayToRemove = temp->data;
		T dataToRemove = arrayToRemove[indexToRemove];
		int i = indexToRemove;
		Node* nextNode;
		while (currentCount < maxIndex) {
			if (i == 49) {
				nextNode = temp->next;
				T dataToShiftLeft = nextNode->data[0];
				temp->data[49] = dataToShiftLeft;
				temp = temp->next;
				i = 0;
			} else {
				temp->data[i] = temp->data[i + 1];
				i++;
			}
			currentCount++;
		}
		maxIndex--;
		deallocateHalfOfArrays();
		return dataToRemove;
	}

	//--------------------------------------------------
	T item_at(int position) const {
		if (position < 0 || position >= size()) {
			throw std::out_of_range("Can't find a value at an invalid index");
		}
		int nodesToProgress = 0;
		while (position > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			position -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int i = 0; i < nodesToProgress; i++) {
			temp = temp->next;
		}
		T* arrayAtPosition = temp->data;
		return arrayAtPosition[position];
	}

	//--------------------------------------------------
	bool is_empty() const {
		if(!head || maxIndex == 0) {
			return true;
		}
		return false;
	}

	//--------------------------------------------------
	size_t size() const {
		if (!head) {
			return 0;
		}
		size_t size = maxIndex;
		return size;
	}

	//--------------------------------------------------
	void clear() {
		if (!head) {
			return;
		}
		maxIndex = 0;
		deallocateHalfOfArrays();
	}

	//--------------------------------------------------
	bool contains(const T& element, bool equals(const T& a, const T& b)) const {
		Node* temp = head;
		int i = 0;
		int currentCount = 0;
		while (currentCount < maxIndex) {
			if (i == 49) {
				if(equals(temp->data[i], element)) {
					return true;
				}
				temp = temp->next;
				i = 0;
			} else {
				if (equals(temp->data[i], element)) {
					return true;
				}
				i++;
			}
			currentCount++;
		}
		return false;
	}

	//--------------------------------------------------
	std::ostream& print(std::ostream& out) const {
		if (size() == 0) {
			out << "<empty list>" << std::endl;
			return out;
		}
		Node* temp = head;
		int i = 0;
		int currentCount = 0;
		out << "[";
		while (currentCount < maxIndex) {
			if (i == 49) {
				out << temp->data[i];;
				temp = temp->next;
				i = 0;
			} else {
				out << temp->data[i];
				i++;
			}
			if(currentCount+1 != maxIndex) {
				out  << ",";
			}
			currentCount++;
		}
		out << "]" <<std::endl;
		return out;
	}

	T& operator[](int i) {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't find a value at an invalid index");
		}
		int nodesToProgress = 0;
		while (i > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			i -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int j = 0; j < nodesToProgress; j++) {
			temp = temp->next;
		}
		T* arrayAtPosition = temp->data;
		return arrayAtPosition[i];
	}

	T const& operator[](int i) const {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't find a value at an invalid index");
		}
		int nodesToProgress = 0;
		while (i > 49) { //while the current is greater than the amount of indices in array(inclusive of 0)
			i -= 50; //subtract the total amount of elements in the array
			nodesToProgress++; //increase the amount of nodes to progress
		}
		Node* temp = head;
		for (int j = 0; j < nodesToProgress; j++) {
			temp = temp->next;
		}
		T* arrayAtPosition = temp->data;
		return arrayAtPosition[i];
	}

};
}
