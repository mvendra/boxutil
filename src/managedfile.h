
#ifndef __managedfile_h__
#define __managedfile_h__

#include "sysutil.h"
#include <string>

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

#endif // __managedfile_h__
