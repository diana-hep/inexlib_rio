// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_stype
#define inlib_stype

//used in rroot leaf template.

#include "typedefs.h"

#include <string>

namespace inlib {

    inline const std::string& stype(unsigned char)
    {
        static const std::string s_v("unsigned char");
        return s_v;
    }

    inline const std::string& stype(char)
    {
        static const std::string s_v("char");
        return s_v;
    }

    inline const std::string& stype(unsigned short)
    {
        static const std::string s_v("unsigned short");
        return s_v;
    }

    inline const std::string& stype(short)
    {
        static const std::string s_v("short");
        return s_v;
    }

    inline const std::string& stype(int)
    {
        static const std::string s_v("int");
        return s_v;
    }

    inline const std::string& stype(unsigned int)
    {
        static const std::string s_v("unsigned int");
        return s_v;
    }

    inline const std::string& stype(float)
    {
        static const std::string s_v("float");
        return s_v;
    }

    inline const std::string& stype(double)
    {
        static const std::string s_v("double");
        return s_v;
    }

    inline const std::string& stype(bool)
    {
        static const std::string s_v("bool");
        return s_v;
    }

    // for inlib::mcol<T> :
    inline const std::string& stype(int64)
    {
        static const std::string s_v("inlib::int64");
        return s_v;
    }
    inline const std::string& stype(uint64)
    {
        static const std::string s_v("inlib::uint64");
        return s_v;
    }
    inline const std::string& stype(const std::string&)
    {
        static const std::string s_v("std::string");
        return s_v;
    }

    // for introspection templated fields or class methods :
    template <class T>
    inline const std::string& stype(const T&)
    {
        return T::s_class();
    }

    inline bool stemplate(const std::string& a_s, std::string& a_inc)
    {
        // If a_s is of the form "xxx<yyy>zzz<ttt>uuuu", at end a_inc contains "yyy".
        // It returns true if something had been found, else false.
        a_inc = a_s;
        std::string::size_type pos = a_inc.find('<');

        if (pos == std::string::npos) {
            a_inc.clear();
            return false;
        }

        a_inc = a_inc.substr((pos + 1), a_inc.size() - (pos + 1));
        std::string::size_type _pos = a_inc.find('>');

        if (_pos == std::string::npos) {
            a_inc.clear();
            return false;
        }

        a_inc = a_inc.substr(0, _pos);
        return true;
    }

}

#include <vector>

namespace inlib {

    // for sg::entries mf_vec< std::vector<std::string> ,std::string> opts;
    inline const std::string& stype(const std::vector<std::string>&)
    {
        static const std::string s_v("std::vector<std::string>");
        return s_v;
    }

}

#endif
