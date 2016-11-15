// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

// It needs to be linked with csz/inflate.c
// then this program is put in inlib.

//inlib_build_use inlib csz inlib zlib

#include <inlib/mem.h>
#include <inlib/args.h>
#include <inlib/rroot/file.h>
#include <inlib/rroot/streamers.h>
#include <inlib/rroot/rall.h>
#include <inlib/zlib.h>

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    #ifdef INLIB_MEM
    inlib::mem::set_check_by_class(true);
    {
    #endif //INLIB_MEM
        inlib::args args(argc, argv);
        std::string file;

        if (!args.file(file)) {
            std::cout << " give a file at the CERN-ROOT format." << std::endl;
            return EXIT_FAILURE;
        }

        bool verbose = args.is_arg("-verbose");
        inlib::rroot::file rfile(std::cout, file, verbose);
        #ifdef EXLIB_DONT_HAVE_ZLIB
        #else
        rfile.add_unziper('Z', inlib::decompress_buffer);
        #endif
        bool sinfos = args.is_arg("-sinfos");
        std::string kbuf;
        args.find("-kbuf", kbuf, "");

        if (kbuf.size()) {
            inlib::rroot::key* k = rfile.dir().find_key(kbuf);

            if (!k) {
                std::cout << kbuf << " not a key in file root directory." << std::endl;
                return EXIT_FAILURE;
            }

            unsigned int sz;
            char* buf = k->get_object_buffer(sz); //we don't have ownership of buf.

            if (!buf) {
                std::cout << " can't get data buffer of " << k->object_name() << "." << std::endl;
                return EXIT_FAILURE;
            }

            std::cout << "size of decompressed data buffer " << sz << std::endl;
        } else {
            const std::vector<inlib::rroot::key*>& keys = rfile.dir().keys();
            inlib::rroot::dump(std::cout, rfile, keys, true, 0);
            bool ls = args.is_arg("-ls");
            bool dump = args.is_arg("-dump");

            if (ls || dump) inlib::rroot::read(std::cout, rfile, keys, true, ls, dump, 0);

            if (sinfos) inlib::rroot::read_sinfos(rfile);
        }

        #ifdef INLIB_MEM
    }
    inlib::mem::balance(std::cout);
        #endif //INLIB_MEM
    return EXIT_SUCCESS;
}
