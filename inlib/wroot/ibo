// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_ibo
#define inlib_wroot_ibo

#include <string>

namespace inlib {
    namespace wroot {
        class buffer;
    }
}

namespace inlib {
    namespace wroot {

        class ibo {
        public:
            virtual ~ibo() {}
        public:
            virtual const std::string& store_cls() const = 0;
            virtual bool stream(buffer&) const = 0;
        };

    }
}

#endif
