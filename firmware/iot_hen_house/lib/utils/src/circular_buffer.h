#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstdio>
#include <memory>

template <class T>
class circular_buffer
{
public:
    explicit circular_buffer(size_t size);

    /// Put e new item inside the buffer
    void put(T item);

    /// Get the first element from the circular buffer
    T get();

    /// Set the head point to the tail pointer, from here you overwrite all the existing element
    void reset();

    /**
     *  Check if the buffer is empty 
     *   - True: is empty 
     *   - False: is not empty
     */
    bool empty() const;
    bool full() const;
    size_t capacity() const;
    size_t size() const;

private:
    std::unique_ptr<T[]> buf_;
    size_t head_ = 0;
    size_t tail_ = 0;
    const size_t max_size_;
    bool full_ = 0;
};

//Implementation
template <class T>
circular_buffer<T>::circular_buffer(size_t size) : buf_(std::unique_ptr<T[]>(new T[size])), max_size_(size) {}

template <class T>
void circular_buffer<T>::put(T item)
{
    buf_[head_] = item;

    if (full_)
    {
        tail_ = (tail_ + 1) % max_size_;
    }

    head_ = (head_ + 1) % max_size_;

    full_ = head_ == tail_;
}

template <class T>
T circular_buffer<T>::get()
{

    if (empty())
    {
        return T();
    }

    //Read data and advance the tail (we now have a free space)
    auto val = buf_[tail_];
    full_ = false;
    tail_ = (tail_ + 1) % max_size_;

    return val;
}

template <class T>
void circular_buffer<T>::reset()
{
    head_ = tail_;
    full_ = false;
}

template <class T>
bool circular_buffer<T>::empty() const
{
    //if head and tail are equal, we are empty
    return (!full_ && (head_ == tail_));
}

template <class T>
bool circular_buffer<T>::full() const
{
    //If tail is ahead the head by 1, we are full
    return full_;
}

template <class T>
size_t circular_buffer<T>::capacity() const
{
    return max_size_;
}

template <class T>
size_t circular_buffer<T>::size() const
{
    size_t size = max_size_;

    if (!full_)
    {
        if (head_ >= tail_)
        {
            size = head_ - tail_;
        }
        else
        {
            size = max_size_ + head_ - tail_;
        }
    }

    return size;
}

#endif