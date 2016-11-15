// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_iobject
#define inlib_wroot_iobject

#include <string>

namespace inlib {
    namespace wroot {
        class buffer;
    }
}

namespace inlib {
    namespace wroot {

        class iobject {
        public:
            virtual ~iobject() {}
        public:
            virtual const std::string& name() const = 0;
            virtual const std::string& title() const = 0;
            virtual const std::string& store_class_name() const = 0;
            virtual bool stream(buffer&) const = 0;
        };

    }
}

#endif
