// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rroot_rall
#define inlib_rroot_rall

#include "streamers"
#include "fac"
#include "tree"

//#define INLIB_RROOT_NOT_OSC

#ifndef INLIB_RROOT_NOT_OSC
    #include "osc"
#endif

namespace inlib {
    namespace rroot {

        inline inlib::rroot::TDirectory* find_dir(inlib::rroot::directory& a_dir, const std::string& a_name)
        {
            std::ostream& out = a_dir.file().out();
            inlib::rroot::key* k = a_dir.find_key(a_name);

            if (!k) {
                //out << "inlib::rroot::find_dir :"
                //    << " " << a_name << " not a key."
                //    << std::endl;
                return 0;
            }

            if (k->object_class() != inlib::rroot::TDirectory_cls()) {
                out << "inlib::rroot::find_dir :"
                    << " key " << a_name << " not a TDirectory."
                    << std::endl;
                return 0;
            }

            uint32 sz;
            char* buf = k->get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out  << "inlib::rroot::find_dir :"
                     << " can't get directory data buffer."
                     << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_dir.file().byte_swap(), sz, buf, k->key_length(), false);
            inlib::rroot::TDirectory* tdir = new inlib::rroot::TDirectory(a_dir.file());

            if (!tdir) return 0;

            if (!tdir->stream(b)) {
                out << "inlib::rroot::find_dir :"
                    << " can't stream TDirectory."
                    << std::endl;
                return 0;
            }

            return tdir;
        }

        inline bool read_key(std::ostream& a_out, inlib::rroot::key& a_key, bool a_dump)
        {
            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                a_out << "inlib::rroot::read_key :"
                      << " can't get data buffer of " << a_key.object_name() << "."
                      << std::endl;
                return false;
            }

            //a_out << "inlib::rroot::read_key :"
            //      << " get data buffer size " << sz << "."
            //      << std::endl;
            inlib::rroot::buffer b(a_out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);

            if (a_key.object_class() == inlib::rroot::TH1F_cls()) {
                inlib::histo::h1d* h = inlib::rroot::TH1F_stream(b);

                if (!h) {
                    a_out << "inlib::rroot::read_key :"
                          << " TH1F streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h->hprint(a_out);
                }

                delete h;
            } else if (a_key.object_class() == inlib::rroot::TH1D_cls()) {
                inlib::histo::h1d* h = inlib::rroot::TH1D_stream(b);

                if (!h) {
                    a_out << "inlib::rroot::read_key :"
                          << " TH1D streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h->hprint(a_out);
                }

                delete h;
            } else if (a_key.object_class() == inlib::rroot::TH2F_cls()) {
                inlib::histo::h2d* h = inlib::rroot::TH2F_stream(b);

                if (!h) {
                    a_out << "inlib::rroot::read_key :"
                          << " TH2F streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h->hprint(a_out);
                }

                delete h;
            } else if (a_key.object_class() == inlib::rroot::TH2D_cls()) {
                inlib::histo::h2d* h = inlib::rroot::TH2D_stream(b); //we get ownership of h.

                if (!h) {
                    a_out << "inlib::rroot::read_key :"
                          << " TH2D streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h->hprint(a_out);
                }

                delete h;
            } else if (a_key.object_class() == inlib::rroot::TH3D_cls()) {
                inlib::histo::h3d* h = inlib::rroot::TH3D_stream(b); //we get ownership of h.

                if (!h) {
                    a_out << "inlib::rroot::read_key :"
                          << " TH3D streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h->hprint(a_out);
                }

                delete h;
            } else if (a_key.object_class() == inlib::rroot::TProfile_cls()) {
                inlib::histo::p1d* p = inlib::rroot::TProfile_stream(b);

                if (!p) {
                    a_out << "inlib::rroot::read_key :"
                          << " TProfile streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) p->hprint(a_out);
                }

                delete p;
            } else if (a_key.object_class() == inlib::rroot::TProfile2D_cls()) {
                inlib::histo::p2d* p = inlib::rroot::TProfile2D_stream(b);

                if (!p) {
                    a_out << "inlib::rroot::read_key :"
                          << " TProfile2D streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) p->hprint(a_out);
                }

                delete p;
            } else if (a_key.object_class() == TTree_cls()) {
                inlib::rroot::fac fac(a_key.file());
                inlib::rroot::tree tree(a_key.file(), fac);

                if (!tree.stream(b)) {
                    a_out << "inlib::rroot::read_key :"
                          << " TTree streaming failed"
                          << std::endl;
                } else {
                    //tree->dump(a_out);
                    if (a_dump) {
                        tree.dump(a_out, "", "  ");
                        uint64 entries = tree.entries();
                        /*
                        {for(uint32 j=0;j<10;j++){ //to test memory.
                         for(uint32 i=0;i<entries;i++){
                           uint32 n;
                           if(!tree.find_entry(i,n)) {
                             a_out << " can't find entry " << i
                                   << std::endl;
                           }
                         }
                         }}
                         */
                        {
                            for (uint32 i = 0; i < 5; i++) {
                                if (!tree.show(a_out, i)) {
                                    a_out << " show failed for entry " << i
                                          << std::endl;
                                }
                            }
                        }
                        {
                            for (uint64 i = mx<int64>(5, entries - 5); i < entries; i++) {
                                if (!tree.show(a_out, (uint32)i)) {
                                    a_out << " show failed for entry " << i
                                          << std::endl;
                                }
                            }
                        }
                    }
                }

                #ifndef INLIB_RROOT_NOT_OSC
            } else if (a_key.object_class() == inlib::osc::s_h1d()) {
                inlib::histo::h1d h("", 10, 0, 1);

                if (!from_osc(b, inlib::osc::s_h1d(), h)) {
                    a_out << "inlib::rroot::read_key :"
                          << " " << inlib::osc::s_h1d() << " streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h.hprint(a_out);
                }
            } else if (a_key.object_class() == inlib::osc::s_h2d()) {
                inlib::histo::h2d h("", 10, 0, 1, 10, 0, 1);

                if (!from_osc(b, inlib::osc::s_h2d(), h)) {
                    a_out << "inlib::rroot::read_key :"
                          << " " << inlib::osc::s_h2d() << " streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h.hprint(a_out);
                }
            } else if (a_key.object_class() == inlib::osc::s_h3d()) {
                inlib::histo::h3d h("", 10, 0, 1, 10, 0, 1, 10, 0, 1);

                if (!from_osc(b, inlib::osc::s_h3d(), h)) {
                    a_out << "inlib::rroot::read_key :"
                          << " " << inlib::osc::s_h3d() << " streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h.hprint(a_out);
                }
            } else if (a_key.object_class() == inlib::osc::s_p1d()) {
                inlib::histo::p1d h("", 10, 0, 1);

                if (!from_osc(b, inlib::osc::s_p1d(), h)) {
                    a_out << "inlib::rroot::read_key :"
                          << " " << inlib::osc::s_p1d() << " streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h.hprint(a_out);
                }
            } else if (a_key.object_class() == inlib::osc::s_p2d()) {
                inlib::histo::p2d h("", 10, 0, 1, 10, 0, 1);

                if (!from_osc(b, inlib::osc::s_p2d(), h)) {
                    a_out << "inlib::rroot::read_key :"
                          << " " << inlib::osc::s_p2d() << " streaming failed"
                          << std::endl;
                } else {
                    if (a_dump) h.hprint(a_out);
                }

                #endif
            } else if (a_key.object_class() == inlib::rroot::TDirectory_cls()) {
                //we should not pass here.
            } else {
                a_out << "inlib::rroot::read_key :"
                      << " dont't know how to read key with object class "
                      << inlib::sout(a_key.object_class())
                      << std::endl;
            }

            return true;
        }

        inline inlib::histo::h1d* key_to_h1d(inlib::rroot::key& a_key)
        {
            std::ostream& out = a_key.file().out();

            if ((a_key.object_class() != inlib::rroot::TH1D_cls()) &&
                (a_key.object_class() != inlib::rroot::TH1F_cls())
               ) {
                out << "inlib::rroot::from(h1d) :"
                    << " key not a TH1D and not a TH1F."
                    << std::endl;
                return 0;
            }

            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out << "inlib::rroot::from(h1d) :"
                    << " can't get data buffer of " << a_key.object_name() << "."
                    << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);

            if (a_key.object_class() == inlib::rroot::TH1D_cls()) {
                return inlib::rroot::TH1D_stream(b);
            } else {
                return inlib::rroot::TH1F_stream(b);
            }
        }

        inline inlib::histo::h2d* key_to_h2d(inlib::rroot::key& a_key)
        {
            std::ostream& out = a_key.file().out();

            if (a_key.object_class() != inlib::rroot::TH2D_cls()) {
                out << "inlib::rroot::from(h1d) :"
                    << " key not a TH2D."
                    << std::endl;
                return 0;
            }

            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out << "inlib::rroot::from(h2d) :"
                    << " can't get data buffer of " << a_key.object_name() << "."
                    << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);
            return inlib::rroot::TH2D_stream(b);
        }

        inline inlib::histo::h3d* key_to_h3d(inlib::rroot::key& a_key)
        {
            std::ostream& out = a_key.file().out();

            if (a_key.object_class() != inlib::rroot::TH3D_cls()) {
                out << "inlib::rroot::from(h1d) :"
                    << " key not a TH3D."
                    << std::endl;
                return 0;
            }

            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out << "inlib::rroot::from(h3d) :"
                    << " can't get data buffer of " << a_key.object_name() << "."
                    << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);
            return inlib::rroot::TH3D_stream(b);
        }

        inline inlib::histo::p1d* key_to_p1d(inlib::rroot::key& a_key)
        {
            std::ostream& out = a_key.file().out();

            if (a_key.object_class() != inlib::rroot::TProfile_cls()) {
                out << "inlib::rroot::from(p1d) :"
                    << " key not a TProfile."
                    << std::endl;
                return 0;
            }

            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out << "inlib::rroot::from(p1d) :"
                    << " can't get data buffer of " << a_key.object_name() << "."
                    << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);
            return inlib::rroot::TProfile_stream(b);
        }

        inline inlib::histo::p2d* key_to_p2d(inlib::rroot::key& a_key)
        {
            std::ostream& out = a_key.file().out();

            if (a_key.object_class() != inlib::rroot::TProfile2D_cls()) {
                out << "inlib::rroot::from(p2d) :"
                    << " key not a TProfile2D."
                    << std::endl;
                return 0;
            }

            unsigned int sz;
            char* buf = a_key.get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                out << "inlib::rroot::from(p2d) :"
                    << " can't get data buffer of " << a_key.object_name() << "."
                    << std::endl;
                return 0;
            }

            inlib::rroot::buffer b(out, a_key.file().byte_swap(), sz, buf, a_key.key_length(), false);
            return inlib::rroot::TProfile2D_stream(b);
        }

        inline void read(std::ostream& a_out,
                         inlib::rroot::ifile& a_file,
                         const std::vector<inlib::rroot::key*>& a_keys,
                         bool a_recursive,
                         bool a_ls,
                         bool a_dump,
                         unsigned int a_spaces)
        {
            {
                std::vector<inlib::rroot::key*>::const_iterator it;

                for (it = a_keys.begin(); it != a_keys.end(); ++it) {
                    inlib::rroot::key& k = *(*it);

                    if (k.object_class() != inlib::rroot::TDirectory_cls()) {
                        if (a_ls || a_dump) {
                            {
                                for (unsigned int index = 0; index < a_spaces; index++) a_out << " ";
                            }
                            std::string label = k.object_name();
                            a_out << "object : " << sout(label)
                                  << ", class : " << k.object_class()
                                  << std::endl;
                            //k.dump(a_out);
                        }

                        if (!read_key(a_out, k, a_dump)) return;
                    }
                }
            }
            {
                std::vector<inlib::rroot::key*>::const_iterator it;

                for (it = a_keys.begin(); it != a_keys.end(); ++it) {
                    inlib::rroot::key& k = *(*it);

                    if (k.object_class() == inlib::rroot::TDirectory_cls()) {
                        if (a_ls || a_dump) {
                            {
                                for (unsigned int index = 0; index < a_spaces; index++) a_out << " ";
                            }
                            std::string label = k.object_name();
                            a_out << "directory : " << label << std::endl;
                        }

                        if (!a_recursive) continue;

                        inlib::uint32 sz;
                        char* buf = k.get_object_buffer(sz);

                        if (!buf) {
                            a_out  << "read :"
                                   << " can't get directory data buffer."
                                   << std::endl;
                        } else {
                            inlib::rroot::buffer b(a_out, a_file.byte_swap(), sz, buf, k.key_length(), false);
                            inlib::rroot::TDirectory dir(a_file);

                            if (!dir.stream(b)) {
                                a_out << "read :"
                                      << " can't stream TDirectory."
                                      << std::endl;
                            } else {
                                const std::vector<inlib::rroot::key*>& keys = dir.keys();
                                read(a_out, a_file, keys, a_recursive, a_ls, a_dump, a_spaces + 1);
                            }
                        }
                    }
                }
            }
        }

    }
}

#endif
