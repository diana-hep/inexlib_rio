// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_signature
#define inlib_signature

#include <string>
#include <cstdio>

namespace inlib {
    namespace file {

        inline bool signature(const std::string& a_file, unsigned char a_head[], unsigned int& a_num) //it is assumed a_head[] can contain a_num chars.
        {
            FILE* file = ::fopen(a_file.c_str(), "rb");

            if (!file) {
                a_num = 0;
                return false;
            }

            a_num = (unsigned int)::fread(a_head, 1, a_num, file);
            ::fclose(file);
            return true;
        }

    }
}

#endif
