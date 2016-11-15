// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rtausmef
#define inlib_rtausmef

#include "rtausmeui.h"
#include "S_STRING.h"

#include <cmath>

namespace inlib {

    class rtausmef : public rtausmeui {
        typedef rtausmeui parent;
    public:
        INLIB_SCLASS(inlib::rtausmef)
    public:
        rtausmef(unsigned int a_seed = 4357): parent(a_seed) {}
        virtual ~rtausmef() {}
    public:
        rtausmef(const rtausmef& a_from): parent(a_from) {}
        rtausmef& operator=(const rtausmef& a_from)
        {
            parent::operator=(a_from);
            return *this;
        }
    protected:
        static float two_to_minus_32()
        {
            static const float s_v = ::ldexpf(1, -32);
            return s_v;
        }
    public:
        float shoot()
        {
            return float(parent::shoot()) * two_to_minus_32();
        }
    };

}

#endif
