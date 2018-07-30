
#ifndef __managedbuffer_h__
#define __managedbuffer_h__

#include "types.h"

template <typename T>
class ManagedBuffer final {

public:

    ManagedBuffer(const uint32 len):buffer{new T[len]}, length{len}{}
    ManagedBuffer(T *pointer, const uint32 len):buffer{pointer}, length{len}{}
    ~ManagedBuffer(){ delete [] buffer; }

    ManagedBuffer(const ManagedBuffer&) = delete;
    ManagedBuffer(ManagedBuffer&&) = delete;
    ManagedBuffer& operator=(const ManagedBuffer&) = delete;
    ManagedBuffer& operator=(ManagedBuffer&&) = delete;

    T *buffer;
    uint32 length;

private:

};

#endif // __managedbuffer_h__
