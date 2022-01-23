// Bounds-checking array type

template <class T> 
class BoundedArray {
    size_t size;
    T *contents;
public:
    BoundedArray(size_t size);

    ~BoundedArray();
    BoundedArray(const BoundedArray &);
    BoundedArray & operator= (const BoundedArray &);

    // overloaded [] does most of the work
    T& operator[] (size_t index);
};

template <class T>
BoundedArray<T>::BoundedArray(size_t size)
{
    this->size = size;
    contents = new T[size];
}

template <class T>
BoundedArray<T>::~BoundedArray()
{
    delete [] contents;
}

template <class T>
BoundedArray<T> &
BoundedArray<T>::operator=(const BoundedArray<T> &other)
{
    if(this != &other) {
        delete [] contents;

        size = other.size;
        contents = new T[size];

        for(size_t i = 0; i < size; i++) {
            contents[i] = other.contents[i];
        }
    }

    return *this;
}

template <class T>
T &
BoundedArray<T>::operator[] (size_t index)
{
    if(index > size) {
        throw "out of bounds";
    } else {
        return contents[index];
    }
}
