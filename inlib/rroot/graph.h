// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rroot_graph
#define inlib_rroot_graph

#include "../scast.h"
#include "buffer.h"

#include "cids.h"

namespace inlib {
    namespace rroot {

        class graph : public virtual iro {
            static const std::string& s_store_class()
            {
                static const std::string s_v("TGraph");
                return s_v;
            }
        public:
            static const std::string& s_class()
            {
                static const std::string s_v("inlib::rroot::graph");
                return s_v;
            }
        public: //iro
            virtual void* cast(const std::string& a_class) const
            {
                if (void* p = cmp_cast<graph>(this, a_class)) return p;

                return 0;
            }
            virtual const std::string& s_cls() const
            {
                return s_class();
            }
        public:
            static cid id_class()
            {
                return graph_cid();
            }
            virtual void* cast(cid a_class) const
            {
                if (void* p = cmp_cast<graph>(this, a_class)) {
                    return p;
                } else return 0;
            }
        public:
            virtual iro* copy() const
            {
                return new graph(*this);
            }
            virtual bool stream(buffer& a_buffer)
            {
                uint32 startpos = a_buffer.length();
                short v;
                unsigned int s, c;

                if (!a_buffer.read_version(v, s, c)) return false;

                a_buffer.set_offset(startpos + c + sizeof(unsigned int));

                if (!a_buffer.check_byte_count(s, c, s_store_class())) return false;

                return true;
            }
        public:
            graph()
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
            }
            virtual ~graph()
            {
                #ifdef INLIB_MEM
                mem::decrement(s_class().c_str());
                #endif
            }
        protected:
            graph(const graph& a_from): iro(a_from) {}
            graph& operator=(const graph&)
            {
                return *this;
            }
        };

    }
}

#endif
