// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_scast
#define inlib_scast

// For implementations of cast methods.

#include "safe_cast.h"
#include "rcmp.h"

namespace inlib {

    template <class TO>
    inline void* cmp_cast(const TO* a_this, const std::string& a_class)
    {
        if (!inlib::rcmp(a_class, TO::s_class())) return 0;

        return (void*)static_cast<const TO*>(a_this);
    }

    template <class TO>
    inline void* cmp_cast(const TO* a_this, cid a_id)
    {
        if (TO::id_class() != a_id) return 0;

        return (void*)static_cast<const TO*>(a_this);
    }

}

#endif
