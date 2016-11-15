// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_long_out
#define inlib_long_out

#include "snpf.h"
#include <string>

namespace inlib {

    class long_out : public std::string {
        typedef std::string parent;
    public:
        long_out(const long& a_value)
        {
            char s[512];
            snpf(s, sizeof(s), "%ld", a_value);
            parent::operator+=(s);
        }
    public:
        long_out(const long_out& a_from): parent(a_from) {}
        long_out& operator=(const long_out& a_from)
        {
            parent::operator=(a_from);
            return *this;
        }
    };

}

#endif
