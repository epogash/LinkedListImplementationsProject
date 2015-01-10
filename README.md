# LinkedListImplementationsProject
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
-Dave Small (Data Structures and Algorithms Teacher)
