// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_mnmx
#define inlib_mnmx

namespace inlib {

    template <class T>
    inline T mn(const T& a, const T& b)
    {
        return (a < b ? a : b);
    }

    template <class T>
    inline T mx(const T& a, const T& b)
    {
        return (a > b ? a : b);
    }

}

#endif
