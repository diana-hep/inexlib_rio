// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_idir
#define inlib_wroot_idir

#include "seek.h"

namespace inlib {
    namespace wroot {
        class ifile;
        class iobject;
    }
}

namespace inlib {
    namespace wroot {

        class idir {
        public:
            virtual ~idir() {}
        public:
            virtual ifile& file() = 0;
            virtual seek seek_directory() const = 0;
            virtual void append_object(iobject*) = 0; //for tree.
        };

    }
}

#endif
