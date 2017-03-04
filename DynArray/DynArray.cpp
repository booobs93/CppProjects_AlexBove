#include "DynArray.hh"

/******************
 *	CONSTRUCTORS 
 *****************/

/**
 @brief Constructor by default.
*/
DynArray::DynArray(void) {
	// By default the capacity is the minimum
	m_capacity = DynArray::DYN_ARRAY_DEFAULT_SIZE;
	// There a e no elements within the array
	m_size = 0;
	m_data = nullptr;
}

/**
 @brief Constructor with initial capacity.
 @param size The initial array capacity.
*/
DynArray::DynArray(size_t size) {
	if (size > DYN_ARRAY_MAX_SIZE) {
		m_capacity = DYN_ARRAY_MAX_SIZE;
	}
	else {
		m_capacity = size;
	}
	// There a e no elements within the array
	m_size = 0;
	// But the array must be initialized
	m_data = static_cast<int*>(malloc(m_capacity * sizeof(int)));
	// Alternative: m_data = new int[m_capacity];
	memset(m_data, 0, m_capacity*sizeof(int));
}

DynArray::DynArray(size_t size, const int &value) {
	if (size > DYN_ARRAY_MAX_SIZE) {
		m_capacity = DYN_ARRAY_MAX_SIZE;
	}
	else {
		m_capacity = size;
	}
	m_size = m_capacity;
	m_data = static_cast<int*>(malloc(m_capacity * sizeof(int)));
	// Alternative: m_data = new int[m_capacity]{value};
	for (int i = 0; i < m_capacity; i++) {
		m_data[i] = value;
	}
}

DynArray::DynArray(int *arr, size_t size) {
	if (size > DYN_ARRAY_MAX_SIZE) {
		m_capacity = DYN_ARRAY_MAX_SIZE;
	}
	else {
		m_capacity = size;
	}
	m_size = m_capacity;
	m_data = static_cast<int*>(malloc(m_capacity * sizeof(int)));
	for (int i = 0; i < m_capacity; i++) {
		m_data[i] = arr[i];
	}
}

/**************
 * DESTRUCTORS
 *************/
DynArray::~DynArray(void) {
	free(m_data);
	// Alternative (if m_data is created using m_data = new int[]{value}) : delete[](m_data);
}

/********************
* OPERATORS OVERRIDE
********************/
DynArray& DynArray::operator=(const DynArray &x) {
	// Free preallocated memory if necessary
	if (nullptr != m_data) {
		free(m_data);
	}

	m_capacity = x.capacity();
	m_size = x.size();
	m_data = static_cast<int*>(malloc(m_capacity * sizeof(int)));
	for (int i = 0; i < m_size; i++) {
		m_data[i] = x.at(i);
	}
}

/*******************
 * ITERATOR METHODS
 ******************/
int* DynArray::begin(void) const {
	if (m_size > 0) {
		return &m_data[0];
	}
	else {
		return nullptr;
	}
}

int* DynArray::end(void) const {
	if (m_size > 0) {
		return &m_data[m_size - 1];
	}
	else {
		return nullptr;
	}
}

/*******************
 * CAPACITY METHODS
 ******************/
void DynArray::resize(size_t n) {
	if (n == m_size || nullptr == m_data) {
		return;
	}
	if (n > m_capacity) {
		if (n > DYN_ARRAY_MAX_SIZE) {
			m_capacity = DYN_ARRAY_MAX_SIZE;
		}
		else {
			m_capacity = n;
		}
		m_data = static_cast<int*>(realloc(m_data, n * sizeof(int)));
	}
	m_size = n;
	// Initialize the last empty positions (growing case)
	for (int i = m_size; i < m_capacity; i++) {
		m_data[i] = 0;
	}
}

void DynArray::reserve(size_t n) {
	// Free any previous allocated memory
	if (nullptr != m_data) {
		free(m_data);
	}
	DynArray(n);
}

void DynArray::shrink(void) {
	// Only shrink the array if there is any empty position
	if (nullptr != m_data && m_size < m_capacity) {
		m_capacity = m_size;
		m_data = static_cast<int*>(realloc(m_data, m_capacity * sizeof(int)));
	}
}

bool DynArray::empty(void) const {
	return m_size == 0;
}

size_t DynArray::capacity(void) const {
	return m_capacity;
}

size_t DynArray::size(void) const {
	return m_size;
}

size_t DynArray::maxSize(void) {
	return DynArray::DYN_ARRAY_MAX_SIZE;
}

/*************************
 * ELEMENT ACCESS METHODS
 *************************/
int & DynArray::operator[](size_t n) const
{
	return m_data[n];
}

int & DynArray::at(size_t n) const
{
	return m_data[n];
}

int & DynArray::front(void) const
{
	return m_data[0];
}

int & DynArray::back(void) const
{
	return m_data[m_size - 1];
}

int * DynArray::data(void) const
{
	return m_data;
}

/********************
* MODIFIER METHODS
*******************/
void DynArray::assign(size_t n, const int & val)
{
	if (nullptr != m_data) {
		resize(n);
		for (int i = 0; i < m_size; i++) {
			m_data[i] = val;
		}
	}
}

void DynArray::push(const int & val)
{
	if (nullptr != m_data) {
		if (m_size == m_capacity) {
			resize(m_capacity + 1);
		}
		m_data[m_size - 1] = val;
	}
}

void DynArray::pop(void)
{
	m_data[m_size - 1] = 0;
	m_size--;
}

void DynArray::insert(size_t position, const int & val)
{
	if (nullptr != m_data) {
		// If the position is beyond the size, push it at the end
		if (position >= m_size) {
			push(val);
		}
		else {
			if (m_size == m_capacity) {
				resize(m_capacity + 1);
			}
			for (int i = m_size - 1; i > position; i--) {
				m_data[i] = m_data[i - 1];
			}
			m_data[position] = val;
			m_size++;
		}
	}
}

void DynArray::erase(size_t position)
{
	if (nullptr != m_data) {
		for (int i = position; i < m_size - 1; i++) {
			m_data[i] = m_data[i + 1];
		}
		m_data[m_size - 1] = 0;
		m_size--;
	}
}

void DynArray::erase(size_t position, size_t last)
{
	if (nullptr != m_data) {
		for (int i = position; i < last && i < m_size; i++) {
			m_data[i] = m_data[i + 1];
		}
		m_data[m_size - 1] = 0;
		m_size--;
	}
}

void DynArray::swap(DynArray & x)
{
	DynArray aux = x;
	// Dump our data into x
	x.clear();
	x.reserve(m_capacity);
	for (int i = 0; i < m_size; i++) {
		x.push(m_data[i]);
	}
	// Dump x dat stored in aux into us
	clear();
	reserve(aux.capacity());
	for (int i = 0; i < x.size(); i++) {
		push(x.at(i));
	}
}

void DynArray::clear(void)
{
	if (nullptr != m_data) {
		for (int i = 0; i < m_size; i++) {
			m_data[i] = 0;
		}
		m_size = 0;
	}
}

/***************
 * UTIL METHODS
 **************/
const size_t & DynArray::min(const size_t & lhs, const size_t & rhs)
{
	if (lhs <= rhs) {
		return lhs;
	}
	else {
		return rhs;
	}
}

void DynArray::fill(int * first, int * last, int value)
{
	if (nullptr != first && nullptr != last) {
		size_t cnt = 0;
		while ((first + cnt) != last) {
			*(first + cnt) = value;
			cnt += sizeof(int);
		}
	}
}

void DynArray::copy(int * first, int * last, int * dest)
{
	if (nullptr != first && nullptr != last && nullptr != dest) {
		size_t cnt = 0;
		while ((first + cnt) != last) {
			*(dest + cnt) = *(first + cnt);
			cnt += sizeof(int);
		}
	}
}

/***********************
 * RELATIONAL OPERATORS
 **********************/
bool operator==(const DynArray & lhs, const DynArray & rhs)
{
	return lhs.capacity() == rhs.capacity() && 
		lhs.size() == rhs.size() &&
		memcmp(lhs.data(), rhs.data(), lhs.size() * sizeof(int)) == 0;
}

bool operator!=(const DynArray & lhs, const DynArray & rhs)
{
	return !(lhs == rhs);
}

bool operator<(const DynArray & lhs, const DynArray & rhs)
{
	return lhs.size() < rhs.size();
}

bool operator<=(const DynArray & lhs, const DynArray & rhs)
{
	return lhs.size() <= rhs.size();
}

bool operator>(const DynArray & lhs, const DynArray & rhs)
{
	return lhs.size() > rhs.size();
}

bool operator>=(const DynArray & lhs, const DynArray & rhs)
{
	return lhs.size() >= rhs.size();
}

std::ostream & operator<<(std::ostream & out, const DynArray & x)
{
	if (nullptr != x.m_data) {
		for (int i = 0; i < x.m_size; i++) {
			out << "[" << i << "] = " << x.m_data[i] << std::endl;
		}
	}
}
