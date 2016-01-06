#ifndef __ARRAY_2D_H__
#define __ARRAY_2D_H__

#include <vector>

// A fixed-size, two dimensional array container. 
//
template< typename T >
class Array2D
{
    public:
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;

        typedef typename std::vector< T >::iterator iterator;
        typedef typename std::vector< T >::const_iterator const_iterator;

        // Constructs a 2D array with the specified dimensions.
        Array2D(size_type rows, size_type cols);
        // Constructs a 2D array with the specified dimensions and initializes 
        // all the elements to 'value'.
        Array2D(size_type rows, size_type cols, const T& value);
        // Constructs a 2D array that is a copy of 'other'.
        Array2D(const Array2D& other);

        // Returns an iterator to the beginning of the row. No bounds checking.
        iterator operator[](size_type row);
        const_iterator operator[](size_type row) const;

        // Returns the dimensions of the array.
        size_type rows() const;
        size_type cols() const;
        // Returns the total number of elements in the array.
        size_type size() const;

        void print() const;

        // The iterators go through each element in a row before proceeding
        // to the row below it.
        // Returns an iterator to the beginning of the first row.
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        // Returns an iterator to the element after the last row.
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

    private:
        // Dimensions of the array.
        size_type numRows, numCols;

        // Underlying container for the array
        std::vector< T > data;
};

#include "array2d.tpp"

#endif
