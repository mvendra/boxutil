
#ifndef __BOXUTIL_MANAGEDBUFFER_H__
#define __BOXUTIL_MANAGEDBUFFER_H__

namespace boxutil {

template <typename T>
class ManagedBuffer final {

public:

    ManagedBuffer(const unsigned int len):buffer{new T[len]}, length{len}{}
    ManagedBuffer(T *pointer, const unsigned int len):buffer{pointer}, length{len}{}
    ~ManagedBuffer(){ delete [] buffer; }

    ManagedBuffer(const ManagedBuffer&) = delete;
    ManagedBuffer(ManagedBuffer&&) = delete;
    ManagedBuffer& operator=(const ManagedBuffer&) = delete;
    ManagedBuffer& operator=(ManagedBuffer&&) = delete;

    T *buffer;
    unsigned int length;

private:

};

} // ns: boxutil

#endif // __BOXUTIL_MANAGEDBUFFER_H__
