
#include <iostream>
#include <stdexcept>
namespace cop3530 {
template<typename T>
class PSLL {
private:
	struct Node {
		Node* next;
		T data;
	}; // end struct Node


	Node* head;
	Node* tail;
	Node* poolHead;
	void deallocatePool() {
		size_t listSize = this->size();
		if(listSize >= 100) {
			int poolCount = 0;
			Node* temp = poolHead;
			while(temp) {
				poolCount++;
				temp = temp->next;
			}
			delete temp;
			if(poolCount > static_cast<float>(listSize) / 2.0f) {
				while(poolCount > static_cast<float>(listSize) / 2.0f) {
					temp = poolHead;
					poolHead = poolHead->next;
					delete temp;
					poolCount--;
				}
			}
		}
	}

public:

	class PSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;

		// but not these typedefs...
		typedef PSLL_Iter self_type;
		typedef PSLL_Iter& self_reference;

	private:
		Node* here;

	public:
		explicit PSLL_Iter(Node* start = NULL) :
				here(start) {
		}
		PSLL_Iter(const PSLL_Iter& src) :
				here(src.here) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return here->data;
		}

		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return &here->data;
		}

		self_reference operator=(const PSLL_Iter& src) {
			if (*this == src) {
				return *this;
			}
			here = src.here;
			return *this;
		}

		self_reference operator++() {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			here = here->next;
			return *this;
		} // preincrement

		self_type operator++(int) {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			PSLL_Iter results(*this);
			here = here->next;
			return results;
		} // postincrement

		bool operator==(const PSLL_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const PSLL_Iter& rhs) const {
			return here != rhs.here;
		}
	}; // end SSLL_Iter
	class PSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef PSLL_Const_Iter self_type;
		typedef PSLL_Const_Iter& self_reference;

	private:
		const Node* here;

	public:
		explicit PSLL_Const_Iter(Node* start = NULL) :
				here(start) {
		}
		PSLL_Const_Iter(const PSLL_Const_Iter& src) :
				here(src.here) {
		}

		reference operator*() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return here->data;
		}
		pointer operator->() const {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			return &here->data;
		}

		self_reference operator=(const PSLL_Const_Iter& src) {
			if (*this == src) {
				return *this;
			}
			here = src.here;
			return *this;
		}

		self_reference operator++() {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			here = here->next;
			return *this;
		} // preincrement

		self_type operator++(int) {
			if (!here) {
				throw std::logic_error("Can't dereference with a null node");
			}
			PSLL_Const_Iter results(*this);
			here = here->next;
			return results;
		} // postincrement

		bool operator==(const PSLL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const PSLL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
	}; // end SSLL_Iter

	typedef std::size_t size_t;
	typedef T value_type;
	typedef PSLL_Iter iterator;
	typedef PSLL_Const_Iter const_iterator;

	iterator begin() {
		return PSLL_Iter(head);
	}
	iterator end() {

		return PSLL_Iter();
	}

	const_iterator begin() const {
		return PSLL_Const_Iter(head);
	}
	const_iterator end() const {
		return PSLL_Const_Iter();
	}

	PSLL() {
		head = NULL;
		tail = NULL;
		poolHead = NULL;
	}

	PSLL( const PSLL& src ) {
		head = NULL;
		tail = NULL;
		poolHead = src.poolHead;
		Node* temp = src.head;
		while(temp) {
			push_back(temp->data);
			temp = temp->next;
		}
	}

	~PSLL() {
		Node* temp = head;
		while (temp) {
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
		head = NULL;
		Node* poolTemp = poolHead;
		while (poolTemp) {
			Node* next = poolTemp->next;
			delete poolTemp;
			poolTemp = next;
		}
		poolHead = NULL;
	}

	PSLL& operator=(const PSLL& src) {
		if (&src == this) // check for self-assignment
			return *this; // do nothing

		delete this;
		Node* temp = src.head;
		while (temp) {
			push_back(temp->data);
			temp = temp->next;
		}
		return *this;
	}

	T replace(const T& element, int position) {
		if (size() == 0 || position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't replace a value if the list is empty");
		}
		int i = 0;
		Node* temp = head;
		if (size() == 1) {
			T data = temp->data;
			temp->data = element;
			return data;
		}
		if (position == 0) {
			T data = temp->data;
			temp->data = element;
			return data;
		}
		while (temp && temp->next && i < position) {
			temp = temp->next; //advance to the node with the element that is being replaced
			i++;
		}
		T data = temp->data;
		temp->data = element;
		return data; //return the original node's data
	}

	//--------------------------------------------------
	void insert(const T& element, int position) {
		if (position > size() || position < 0) {
			throw std::out_of_range(
					"Can't replace a value if the list is empty");
		}
		int i = 0;
		Node* newNode;
		if (!poolHead) {
			newNode = new Node();
		} else {
			newNode = poolHead;
			poolHead = poolHead->next;
			newNode->next = NULL;
		}
		newNode->data = element;
		Node* temp = head;
		if (position == 0) {
			newNode->next = head;
			head = newNode;
			return;
		}
		while (temp && temp->next && i < position - 1) {
			temp = temp->next;
			i++;
		}
		newNode->next = temp->next; //set the next node of the node to be inserted to the element at the position of insertion
		temp->next = newNode; //set the node to be inserted to be next, which ends up being the index of the position parameter
	}

	//--------------------------------------------------
	void push_front(const T& element) {
		Node* newNode;
		if (!poolHead) {
			newNode = new Node();
		} else {
			newNode = poolHead;
			poolHead = poolHead->next;
			newNode->next = NULL;
		}
		newNode->data = element;
		if (!head) {
			head = newNode;
			tail = newNode;
			newNode->next = NULL;
		} else {
			newNode->next = head;
			head = newNode;
		}
	}

	//--------------------------------------------------
	void push_back(const T& element) {
		Node* newNode;
		if (!poolHead) {
			newNode = new Node();
		} else {
			newNode = poolHead;
			poolHead = poolHead->next;
			newNode->next = NULL;
		}
		newNode->data = element;
		if (!head) {
			head = newNode;
			tail = newNode;
			newNode->next = NULL;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	//--------------------------------------------------
	T pop_front() {
		if (!head) {
			throw std::out_of_range("Can't pop a value if the list is empty");
		}
		if (size() == 1) {
			Node* nodeToBeRemoved = head;
			nodeToBeRemoved->next = poolHead;
			poolHead = nodeToBeRemoved;
			T data = head->data;
			head = NULL;
			tail = NULL;
			return data;
		}

		T data = head->data;
		Node* temp = head;
		head = head->next;

		temp->next = poolHead;
		poolHead = temp; //add the deleted element to the pool
		deallocatePool();
		return data;
	}

	//--------------------------------------------------
	T pop_back() {
		if (!head) {
			 throw std::out_of_range("Can't pop a value if the list is empty");
		}
		if(size() == 1) {
			Node* nodeToBeRemoved = head;
			nodeToBeRemoved->next = poolHead;
			poolHead = nodeToBeRemoved;
			T data = head->data;
			head = NULL;
			tail = NULL;
			return data;
		}
		T data = tail->data;
		Node* temp = head;
		while (temp->next && temp->next->next) { //advance to the node that is the node before the last node
			temp = temp->next;
		}
		Node* nodeToBeRemoved = temp->next;
		nodeToBeRemoved->next = poolHead;
		poolHead = nodeToBeRemoved; //add the deleted element to the pool

		temp->next = NULL; //set the one before the last node to link to null
		tail = temp; //set the tail to the temp node, which is the new last node
		deallocatePool();
		return data; //return the data of the original last node
	}

	//--------------------------------------------------
	T remove(int position) {
		if (!head || position < 0 || position >= size()) {
			throw std::out_of_range(
					"Can't remove a value if the list is empty");
		}
		int i = 0;
		Node* temp = head;
		if (size() == 1) {
			T data = head->data;
			head = NULL;
			tail = NULL;
			return data;
		}
		if (position == 0) {
			T data = head->data;
			head = head->next;
			return data;
		}
		while (temp->next && i < position - 1) {
			temp = temp->next; //advance to the position 1 less than the node to be removed
			i++;
		}
		T data = temp->next->data; //store the data of the node to be removed

		Node* nodeToRemove = temp->next;
		nodeToRemove->next = poolHead;
		poolHead = nodeToRemove; //add the deleted element to the pool

		temp->next = temp->next->next; //set the next node to be the next node of the node that is being removed
		if (position == size() - 1) {
			tail = temp; //if the last element is removed, set the tail to be the new last element
		}
		deallocatePool();
		return data;
	}

	//--------------------------------------------------
	T item_at(int position) const {
		if (position < 0 || position >= size()) {
			throw std::out_of_range("Can't find a value at an invalid index");
		}
		Node* temp = head;
		int i = 0;
		while (i < position) {
			temp = temp->next;
			i++;
		}
		return temp->data;
	}

	//--------------------------------------------------
	bool is_empty() const {
		if (!head) {
			return true;
		}
		return false;
	}

	//--------------------------------------------------
	size_t size() const {
		if (!head) {
			return 0;
		}
		size_t size = 1;
		Node* temp = head;
		while (temp->next) {
			size++;
			temp = temp->next;
		}
		return size;
	}

	//--------------------------------------------------
	void clear() {
		if (!head) {
			return;
		}
		if (size() == 1) {
			Node* nodeToRemove = head;
			nodeToRemove->next = poolHead;
			poolHead = nodeToRemove; //add the deleted element to the pool
			head = NULL;
			tail = NULL;
			return;
		}
		Node* temp = head;
		temp = temp->next;
		while (temp) {
			Node* nodeToRemove = head;
			nodeToRemove->next = poolHead;
			poolHead = nodeToRemove; //add the deleted element to the pool
			head = temp;
			temp = temp->next;
		}
		head = NULL;
		tail = NULL;
		deallocatePool();
	}

	//--------------------------------------------------
	bool contains(const T& element, bool equals(const T& a, const T& b)) const {
		Node* temp = head;
		while (temp) {
			if (equals(element, temp->data)) {
				return true;
			}
			temp = temp->next;
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
		out << "[";
		while (temp) {
			out << temp->data;
			if (temp->next) {
				out << ",";
			}
			temp = temp->next;
		}
		out << "]" << std::endl;
		return out;
	}
	T& operator[](int i) {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't get a value at an invalid index");
		}
		Node* temp = head;
		for (int j = 0; j < i; j++) {
			temp = temp->next;
		}
		return temp->data;
	}

	T const& operator[](int i) const {
		if (i < 0 || i >= size()) {
			throw std::out_of_range("Can't get a value at an invalid index");
		}
		Node* temp = head;
		for (int j = 0; j < i; j++) {
			temp = temp->next;
		}
		return temp->data;
	}
};
}
