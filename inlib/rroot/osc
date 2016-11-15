// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rroot_osc
#define inlib_rroot_osc

#include "named"
#include "member_reader"
#include "../store/osc_streamers"

namespace inlib {
    namespace rroot {

        template <class H>
        inline bool from_osc(buffer& a_buffer, const std::string& a_cls,
                             H& a_histo)
        {
            //Stream as in a BatchLab/Rio/Data.h :
            unsigned int s, c;
            short v;

            if (!a_buffer.read_version(v, s, c)) return false;

            std::string name;
            std::string title;

            if (!Named_stream(a_buffer, name, title)) return false;

            member_reader mr(a_buffer);

            if (!osc::read(mr, a_histo)) {
                a_buffer.out() << "inlib::rroot::from_osc(" << a_cls << ") :"
                               << " streaming failed."
                               << std::endl;
                return false;
            }

            if (!a_buffer.check_byte_count(s, c, a_cls)) return false;

            return true;
        }

    }
}

#endif
