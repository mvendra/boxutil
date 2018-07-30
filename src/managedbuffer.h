
#ifndef __managedbuffer_h__
#define __managedbuffer_h__

template <typename T>
class ManagedBuffer final {

public:

    ManagedBuffer(unsigned const int len):buffer{new T[len]}, length{len}{}
    ManagedBuffer(T *pointer, unsigned const int len):buffer{pointer}, length{len}{}
    ~ManagedBuffer(){ delete [] buffer; }

    ManagedBuffer(const ManagedBuffer&) = delete;
    ManagedBuffer(ManagedBuffer&&) = delete;
    ManagedBuffer& operator=(const ManagedBuffer&) = delete;
    ManagedBuffer& operator=(ManagedBuffer&&) = delete;

    T *buffer;
    unsigned int length;

private:

};

#endif // __managedbuffer_h__
