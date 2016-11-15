// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_S_STRING
#define inlib_S_STRING

// a few place in which a cpp macro help the readability.

#include <string>

#define INLIB_CLASS_STRING(a_name)\
    static const std::string& s_##a_name() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }

#define INLIB_CLASS_STRING_VALUE(a_name,a_value)\
    static const std::string& s_##a_name() {\
        static const std::string s_v(#a_value);\
        return s_v;\
    }

#define INLIB_GLOBAL_STRING(a_name)\
    inline const std::string& s_##a_name() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }

#define INLIB_GLOBAL_STRING_VALUE(a_name,a_value)\
    inline const std::string& s_##a_name() {\
        static const std::string s_v(#a_value);\
        return s_v;\
    }

#define INLIB_SCLASS(a_name)\
    static const std::string& s_class() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }\
    static void check_class_name() {a_name::s_class();}

#define INLIB_T_SCLASS(a_T,a_name)\
    static const std::string& s_class() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }\
    static void check_class_name() {a_name<a_T>::s_class();}

#define INLIB_T2_SCLASS(a_T1,a_T2,a_name)\
    static const std::string& s_class() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }\
    static void check_class_name() {a_name<a_T1,a_T2>::s_class();}

#define INLIB_T3_SCLASS(a_T1,a_T2,a_T3,a_name)\
    static const std::string& s_class() {\
        static const std::string s_v(#a_name);\
        return s_v;\
    }\
    static void check_class_name() {a_name<a_T1,a_T2,a_T3>::s_class();}

#endif
