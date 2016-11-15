// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_itree
#define inlib_wroot_itree

#include "../typedefs"

namespace inlib {
    namespace wroot {
        class idir;
    }
}

namespace inlib {
    namespace wroot {

        class itree {
        public:
            virtual ~itree() {}
        public:
            virtual void add_tot_bytes(uint32) = 0;
            virtual void add_zip_bytes(uint32) = 0;
            virtual idir& dir() = 0;
            virtual const idir& dir() const = 0;
        };

    }
}

#endif
