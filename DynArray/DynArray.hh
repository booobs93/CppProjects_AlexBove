#pragma once
#include <ostream>

class DynArray
{
public:
	// constructors
	DynArray (void);													// constructs the class by default
	DynArray (size_t size);												// creates the array with a defined size
	DynArray (size_t size, const int &value);							// creates and initializes the elements of the array with a value
	DynArray (int *arr, size_t size);									// initializes each element from an external array

	// destructor
	~DynArray (void);													// deletes the memory in the Heap

	// assignment operators
	DynArray& operator= (const DynArray &x);							// copies all the attributes from x to this object

	// iterator methods
	int* begin (void) const;											// returns an iterator to the first element
	int* end   (void) const;											// returns an iterator to the last element

	// capacity methods
	void resize			  (size_t n);									// resizes the array so that it contains n elements
	void reserve		  (size_t n);									// requests the capacity to be at least enough to contain n elements
	void shrink			  (void);										// requests the array to reduce its capacity to fit its size
	bool empty			  (void) const;									// returns whether the array size is 0 or not
	size_t capacity		  (void) const;									// returns the size of the currently allocated storage space
	size_t size			  (void) const;									// returns the number of elements in the array
	static size_t maxSize (void);										// returns the maximum number of elements that the array can hold

	// element access methods
	int& operator[]	(size_t n) const;									// returns a reference to the element at position n in the array
	int& at			(size_t n) const;									// returns a reference to the element at position n in the array
	int& front		(void)     const;									// returns a reference to the first element in the array
	int& back		(void)     const;									// returns a reference to the last element in the array
	int* data		(void)     const;									// returns a direct pointer to the memory array that stores the elements

	// modifiers methods
	void assign (size_t n, const int& val);								// assigns and replaces the current contents modifying its size accordingly
	void push	(const int &val);										// adds a new element at the end of the array, after its current last element
	void pop	(void);													// removes the last element effectively reducing the array size by one
	void insert	(size_t position, const int &val);						// a new element is inserted before the element at the specified position
	void erase	(size_t position);										// removes from the array a single element
	void erase	(size_t first, size_t last);							// removes from the array a range of elements
	void swap	(DynArray &x);											// exchanges the content of the array by the content of x
	void clear	(void);													// removes all elements from the array leaving it with a size of 0

	// relational operators
	friend bool operator== (const DynArray& lhs, const DynArray& rhs);	// checks if 2 arrays are equal
	friend bool operator!= (const DynArray& lhs, const DynArray& rhs);	// checks if 2 arrays are not equal
	friend bool operator<  (const DynArray& lhs, const DynArray& rhs);	// checks if array lhs is smaller than rhs
	friend bool operator<= (const DynArray& lhs, const DynArray& rhs);	// checks if array lhs is smaller or equal than rhs
	friend bool operator>  (const DynArray& lhs, const DynArray& rhs);	// checks if array lhs is greater than rhs
	friend bool operator>= (const DynArray& lhs, const DynArray& rhs);	// checks if array lhs is greater or equal than rhs

	// input/output operators
	friend std::ostream& operator<< (std::ostream &out, const DynArray &x); // prints out the contents of the array object

private:
	// static constants
	static const size_t DYN_ARRAY_DEFAULT_SIZE { 8 };					// initial constant size of the array memory
	static const size_t DYN_ARRAY_MAX_SIZE	   { 1073741823 };			// maximum constant size that the array memory can hold

	// attributes
	size_t	m_capacity;													// actual size of the allocated memory
	size_t  m_size;														// current number of elements in the array
	int	   *m_data;														// pointer to the memory allocated in the Heap

	// utils methods
	static const size_t& min (const size_t &lhs, const size_t &rhs);	// returns the smaller size of lhs and rhs
	static void fill         (int *first, int *last, int value);		// assigns the given value to the elements in the range [first, last)
	static void copy         (int *first, int *last, int *dest);		// copies all elements in the range [first, last) to dest
};