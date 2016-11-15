// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_press_func
#define inlib_press_func

#include <ostream>

namespace inlib {

    typedef bool (*compress_func)(std::ostream&, unsigned int, unsigned int, const char*, unsigned int, char*, unsigned int&);

    typedef bool (*decompress_func)(std::ostream&, unsigned int, const char*, unsigned int, char*, unsigned int&);

}

#endif
