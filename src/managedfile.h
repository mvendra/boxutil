
#ifndef __BOXUTIL_MANAGEDFILE_H__
#define __BOXUTIL_MANAGEDFILE_H__

#include "sysutil.h"
#include <string>

namespace boxutil {

class ManagedFile final {

public:

    ManagedFile() = delete;
    ManagedFile(const std::string &_filename):filename{_filename}{}
    ~ManagedFile(){ FileDelete(filename); }

    ManagedFile(const ManagedFile&) = delete;
    ManagedFile(ManagedFile&&) = delete;
    ManagedFile& operator=(const ManagedFile&) = delete;
    ManagedFile& operator=(ManagedFile&&) = delete;

private:

    std::string filename;

};

} // ns: boxutil

#endif // __BOXUTIL_MANAGEDFILE_H__
