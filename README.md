# Linked List Implementations Project
This project was done independently for COP 3530 (Data Structures and Algorithms). Each linked list variation was created to adhere to the assignments specification. In addition, each linked list implementation was thoroughly tested using Catch - a C++ unit testing framework. I received an A on this project.

"Simple Singly-Linked List (SSLL)

A basic implementation: whenever an item is added to the list, a new node is allocated to hold it; whenever an item is removed, the node that held it is deallocated.

Pool-using Singly-Linked List (PSLL)

Similar to the SSLL, except the node allocation/deallocation strategy is different. The list maintains a pool of unused nodes. Whenever an item is added to the list, use a node in the pool of free nodes; if there are no free nodes, then a new node is allocated. Whenever an item is removed, the node is added to the pool.

Because we don't want the pool to waste too much memory, whenever the list contains ≥ 100 items AND the pool contains more nodes than half the list size, reduce the number of pool nodes to half the list size (by deallocating the excess).

Simple Dynamic Array-based List (SDAL)

A basic implementation: the initial array size is passed as a parameter to the constructor; if no value is passed then default to a backing array with 50 slots. Whenever an item is added and the backing array is full, allocate a new array 150% the size of the original, copy the items over to the new array, and deallocate the original one.

Because we don't want the list to waste too much memory, whenever the array's size is ≥ 100 slots and fewer than half the slots are used, allocate a new array 50% the size of the original, copy the items over to the new array, and deallocate the original one.

Chained Dynamic Array-based List (CDAL)

This is the one described in the discussion session. The idea again is that a linked-list of arrays is used as the backing store. Each array has 50 slots. The chain starts off containing just a single array. When the last array in the chain is filled, and a new item is inserted, a new array is added to the chain.

Because we don't want the list to waste too much memory, whenever the more than half of the arrays are unused (they would all be at the end of the chain), deallocate half the unused arrays."
- written by Dave Small (Data Structures and Algorithms Teacher)

In addition, the following checklist was used to ensure all methods were implemented:

List variety: Chained Dynamic Array-based List written by Pogash, Eric
COP 3530, 2014F <1085>
"======================================================================
Part I:
======================================================================
My LIST implementation uses the data structure described in the part I
instructions and conforms to the technique required for this list
variety: <yes>

My LIST implementation 100% correctly supports the following methods
as described in part I:

* replace: <yes>
* insert: <yes>
* push_back: <yes>
* push_front: <yes>
* remove: <yes>
* pop_back: <yes>
* pop_front: <yes>
* item_at: <yes>
* is_empty: <yes>
* clear: <yes>
* contains: <yes>
* print: <yes>

======================================================================
Part II:
======================================================================
My LIST implementation 100% correctly supports the following methods
as described in part II:

* size: <yes>
* begin (returning an iterator): <yes>
* end (returning an iterator): <yes>
* begin (returning a const iterator): <yes>
* end (returning an const iterator): <yes>

My LIST implementation 100% correctly supports the following data
members as described in part II:

* size_t
* value_type
* iterator
* const_iterator

My ITERATOR implementation 100% correctly supports the following
methods as described in part II:

* constructor: <yes>
* explicit constructor: <yes>
* operator*: <yes>
* operator->: <yes>
* operator=: <yes>
* operator++ (pre): <yes>
* operator++ (post): <yes>
* operator==: <yes>
* operator!=: <yes>

My ITERATOR implementation 100% correctly supports the following
data members as described in part II:

* value_type: <yes>
* difference_type: <yes>
* reference: <yes>
* pointer: <yes>
* iterator_category: <yes>
* self_type: <yes>
* self_reference: <yes>

My CONST ITERATOR implementation 100% correctly supports the following
methods as described in part II:

* constructor: <yes>
* explicit constructor: <yes>
* operator*: <yes>
* operator->: <yes>
* operator=: <yes>
* operator++ (pre): <yes>
* operator++ (post): <yes>
* operator==: <yes>
* operator!=: <yes>

My CONST ITERATOR implementation 100% correctly supports the following
data members as described in part II:

* value_type: <yes>
* difference_type: <yes>
* reference: <yes>
* pointer: <yes>
* iterator_category: <yes>
* self_type: <yes>
* self_reference: <yes>

======================================================================
Part III:
======================================================================
My LIST implementation 100% correctly supports the following
methods as described in part III:

* operator[]: <yes>
* operator[] const: <yes>

For my LIST's methods 

- I wrote documentation identifying the complete behavior (both normal
  and exceptional) of the method, *AND*

- when something unexpected occurs, the method throws appropriately
  typed exceptions, *AND*

- my implementation behaves 100% precisely as documented, *AND*

- I have proven this by creating a suite of CATCH unit tests for
  the method to verify that the method behaves as documented, *AND*

- the method passes all of those unit tests.

* replace: <yes>
* insert: <yes>
* push_back: <yes>
* push_front: <yes>
* remove: <yes>
* pop_back: <yes>
* pop_front: <yes>
* item_at: <yes>
* is_empty: <yes>
* clear: <yes>
* contains: <yes>
* print: <yes>
* size: <yes>
* begin (returning an iterator): <yes>
* end (returning an iterator): <yes>
* begin (returning a const iterator): <yes>
* end (returning an const iterator): <yes>
* operator[]: <yes>
* operator[] const: <yes>

For my ITERATOR's methods 

- I wrote documentation identifying the complete behavior (both normal
  and exceptional) of the method, *AND*

- when something unexpected occurs, the method throws appropriately
  typed exceptions, *AND*

- my implementation behaves 100% precisely as documented, *AND*

- I have proven this by creating a suite of CATCH unit tests for
  the method to verify that the method behaves as documented, *AND*

- the method passes all of those unit tests.

* constructor: <yes>
* explicit constructor: <yes>
* operator*: <yes>
* operator->: <yes>
* operator=: <yes>
* operator++ (pre): <yes>
* operator++ (post): <yes>
* operator==: <yes>
* operator!=: <yes>

For my CONST ITERATOR's methods 

- I wrote documentation identifying the complete behavior (both normal
  and exceptional) of the method, *AND*

- when something unexpected occurs, the method throws appropriately
  typed exceptions, *AND*

- my implementation behaves 100% precisely as documented, *AND*

- I have proven this by creating a suite of CATCH unit tests for
  the method to verify that the method behaves as documented, *AND*

- the method passes all of those unit tests.

* constructor: <yes>
* explicit constructor: <yes>
* operator*: <yes>
* operator->: <yes>
* operator=: <yes>
* operator++ (pre): <yes>
* operator++ (post): <yes>
* operator==: <yes>
* operator!=: <yes>

My LIST implementation compiles correctly using g++ v4.8.2 on the
OpenBSD VM: <yes>

My UNIT TESTS compiles correctly using g++ v4.8.2 on the 
OpenBSD VM: <yes>

My UNIT TESTS run correctly on the OpenBSD VM: <yes>"
- written by Dave Small
