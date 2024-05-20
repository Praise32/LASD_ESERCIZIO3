
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    class Iterator {

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~Iterator() = default;

        /* ************************************************************************ */

        // Copy assignment
        Iterator& operator=(const Iterator& var) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        Iterator& operator=(Iterator&& var) noexcept = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Iterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.
        bool operator!=(const Iterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual const Data& operator*() const = 0;    // (non-mutable version; concrete function must throw std::out_of_range when terminated)

        virtual bool Terminated() const noexcept = 0;     // (concrete function should not throw exceptions)

    };

/* ************************************************************************** */

    template <typename Data>
    class MutableIterator : virtual public Iterator<Data>{

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~MutableIterator() = default;

        /* ************************************************************************ */

        // Copy assignment
        MutableIterator& operator=(const MutableIterator& var) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        MutableIterator& operator=(MutableIterator&& var) = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const MutableIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.
        bool operator!=(const MutableIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual Data& operator*() = 0;   // (mutable version; concrete function must throw std::out_of_range when terminated)

    };

/* ************************************************************************** */

    template <typename Data>
    class ForwardIterator : virtual public Iterator<Data>{

    private:

        // ...

    protected:

        // ...

    public:

        // Destructor
        virtual ~ForwardIterator() = default;

        /* ************************************************************************ */

        // Copy assignment
        ForwardIterator& operator=(const ForwardIterator& var) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        ForwardIterator& operator=(ForwardIterator&& var) = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const ForwardIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.
        bool operator!=(const ForwardIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual ForwardIterator& operator++() = 0;  // (concrete function must throw std::out_of_range when terminated)

    };

/* ************************************************************************** */

    template <typename Data>
    class ResettableIterator : virtual public Iterator<Data>{

    private:

        Data* root;

    protected:

        // ...

    public:

        // Destructor
        virtual ~ResettableIterator() = default;

        /* ************************************************************************ */

        // Copy assignment
        ResettableIterator& operator=(const ResettableIterator& var) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        ResettableIterator& operator=(ResettableIterator&& var) = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const ResettableIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.
        bool operator!=(const ResettableIterator& var) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual void Reset() = 0;// (concrete function should not throw exceptions)

    };

/* ************************************************************************** */

}

#endif