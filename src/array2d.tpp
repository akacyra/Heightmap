#include "array2d.h"

using std::vector;

#include <iostream>

template< typename T >
void Array2D< T >::print() const
{
    std::cout << "[" << std::endl;
    for(int i = 0; i < numRows; i++) {
        std::cout << "  [ ";
        for(int j = 0; j < numCols; j++) {
            std::cout << data[j + i * numCols] << ", ";
        }
        std::cout << "]," << std::endl;
    }
    std::cout << "]" << std::endl;
} // print()

template< typename T >
Array2D< T >::Array2D(size_type rows, size_type cols)
    : numRows(rows), numCols(cols), data(rows * cols)
{
} // Constructor

template< typename T >
Array2D< T >::Array2D(size_type rows, size_type cols, const T& value)
    : numRows(rows), numCols(cols), data(rows * cols, value)
{
} // Constructor

template< typename T >
Array2D< T >::Array2D(const Array2D& other)
{
    numRows = other.numRows;
    numCols = other.numCols;
    data = other.data;
} // Copy constructor

template< typename T >
typename Array2D< T >::iterator Array2D< T >::operator[](size_type row)
{
    return data.begin() + row * numCols;
} // operator[]

template< typename T >
typename Array2D< T >::const_iterator Array2D< T >::operator[](size_type row) const
{
    return data.cbegin() + row * numCols;
} // operator[]

template< typename T >
typename Array2D< T >::size_type Array2D< T >::size() const
{
    return data.size();
} // size()

template< typename T >
typename Array2D< T >::size_type Array2D< T >::rows() const
{
    return numRows;
} // rows()

template< typename T >
typename Array2D< T >::size_type Array2D< T >::cols() const
{
    return numCols;
} // cols()

template< typename T >
typename Array2D< T >::iterator Array2D< T >::begin()
{
    return data.begin();
} // begin()

template< typename T >
typename Array2D< T >::const_iterator Array2D< T >::begin() const
{
    return data.begin();
} // begin()

template< typename T >
typename Array2D< T >::const_iterator Array2D< T >::cbegin() const
{
    return data.cbegin();
} // cbegin()

template< typename T >
typename Array2D< T >::iterator Array2D< T >::end()
{
    return data.end();
} // end()

template< typename T >
typename Array2D< T >::const_iterator Array2D< T >::end() const
{
    return data.end();
} // end()

template< typename T >
typename Array2D< T >::const_iterator Array2D< T >::cend() const
{
    return data.end();
} // end()
