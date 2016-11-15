// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rtausmed
#define inlib_rtausmed

// flat in ]0,1[ ???

#include "rtausmeui.h"
#include "S_STRING.h"

#include <cmath>

namespace inlib {

    class rtausmed : public rtausmeui {
        typedef rtausmeui parent;
    public:
        INLIB_SCLASS(inlib::rtausmed)
    public:
        rtausmed(unsigned int a_seed = 4357): parent(a_seed) {}
        virtual ~rtausmed() {}
    public:
        rtausmed(const rtausmed& a_from): parent(a_from) {}
        rtausmed& operator=(const rtausmed& a_from)
        {
            parent::operator=(a_from);
            return *this;
        }
    protected:
        static double two_to_minus_32()
        {
            static const double s_v = std::ldexp(1.0, -32);
            return s_v;
        }
    public:
        double shoot()
        {
            return double(parent::shoot()) * two_to_minus_32();
        }
    };

}

#endif
