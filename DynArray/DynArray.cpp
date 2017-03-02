#include "..\..\..\..\Documents\Visual Studio 2015\Projects\CppProjects_AlexBove\DynArray\DynArray.hh"

DynArray::DynArray(void){
	m_capacity = DYN_ARRAY_DEFAULT_SIZE;
	m_size = 0;
	m_data = new int(m_capacity);
}

DynArray::DynArray(int * arr, size_t size){
	m_capacity = size;
	m_size = size;
	m_data = new int(m_capacity);
}







