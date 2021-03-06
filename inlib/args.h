// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_args
#define inlib_args

#include "sout.h"
#include "strip.h"
#include "words.h"
#include "sto.h"
#include "forit.h"
#include "mnmx.h"

#include <ostream>

namespace inlib {

    class args {
    public:
        typedef std::pair<std::string, std::string> arg;
    public:
        args() {}
        args(int a_argc, char* a_argv[])
        {
            for (int index = 0; index < a_argc; index++) {
                std::string s(a_argv[index]);
                std::string::size_type pos = s.find('=');

                if (pos == std::string::npos) {
                    m_args.push_back(arg(s, ""));
                } else {
                    std::string key = s.substr(0, pos);
                    pos++;
                    std::string value = s.substr(pos, s.size() - pos);
                    m_args.push_back(arg(key, value));
                }
            }
        }
        args(const std::vector<std::string>& a_args)
        {
            add(a_args);
        }
        args(const std::vector<arg>& a_args): m_args(a_args) {}
        //args(const std::string& a_args,const std::string& a_sep = " ",bool a_strip = false){
        args(const std::string& a_args, const std::string& a_sep, bool a_strip)
        {
            std::vector<std::string> _args;
            words(a_args, a_sep, false, _args);
            add(_args, a_strip);
        }
        virtual ~args() {}
    public:
        args(const args& a_from): m_args(a_from.m_args) {}
        args& operator=(const args& a_from)
        {
            m_args = a_from.m_args;
            return *this;
        }
    public:
        const std::vector<arg>& get_args() const
        {
            return m_args;
        }

        bool is_arg(const std::string& a_string) const
        {
            inlib_vforcit(arg, m_args, it) {
                if ((*it).first == a_string) return true;
            }
            return false;
        }
        bool is_empty() const
        {
            return m_args.size() ? false : true;
        }
        unsigned int size() const
        {
            return m_args.size();
        }
        unsigned int number() const
        {
            return m_args.size();   //back comp.
        }
        bool find(const std::string& a_key, std::string& a_value, const std::string& a_def = "") const
        {
            inlib_vforcit(arg, m_args, it) {
                if ((*it).first == a_key) {
                    a_value = (*it).second;
                    return true;
                }
            }
            a_value = a_def;
            return false;
        }
        std::vector<std::string> find(const std::string& a_key) const
        {
            std::vector<std::string> vals;
            inlib_vforcit(arg, m_args, it) {
                if ((*it).first == a_key) vals.push_back((*it).second);
            }
            return vals;
        }
        bool find(const std::string& a_string, bool& a_value, const bool& a_def = false) const
        {
            std::string s;

            if (!find(a_string, s)) {
                a_value = a_def;
                return false;
            }

            return to(s, a_value, a_def);
        }
        template <class aT>
        bool find(const std::string& a_string, aT& a_value, const aT& a_def = aT()) const
        {
            std::string _s;

            if (!find(a_string, _s)) {
                a_value = a_def;
                return false;
            }

            return to<aT>(_s, a_value, a_def);
        }
        std::vector<std::string> tovector() const
        {
            // Return a vector of string <name=value>
            std::vector<std::string> vec;
            inlib_vforcit(arg, m_args, it) {
                std::string s;

                if ((*it).second.empty()) {
                    s = (*it).first;
                } else {
                    s = (*it).first;
                    s += "=";
                    s += (*it).second;
                }

                vec.push_back(s);
            }
            return vec;
        }

        bool add(const std::string& a_key, const std::string& a_value = "", bool a_override = true)
        {
            if (a_override) {
                inlib_vforit(arg, m_args, it) {
                    if ((*it).first == a_key) {
                        (*it).second = a_value;
                        return true;
                    }
                }
            }

            if (a_key.empty()) return false;

            m_args.push_back(arg(a_key, a_value));
            return true;
        }

        void add(const std::vector<std::string>& a_args, bool a_strip = false)
        {
            inlib_vforcit(std::string, a_args, it) {
                std::vector<std::string> ws;
                words((*it), "=", false, ws);

                if (ws.size() == 1) {
                    if (a_strip) strip(ws[0], both, ' ');

                    m_args.push_back(arg(ws[0], ""));
                } else if (ws.size() >= 2) {
                    if (a_strip) {
                        strip(ws[0], both, ' ');
                        strip(ws[1], both, ' ');
                    }

                    m_args.push_back(arg(ws[0], ws[1]));
                }
            }
        }

        void add_keyvals(const std::vector<std::string>& a_args, bool a_strip = false)
        {
            //a_args must contain an even number of strings.
            size_t sz_half = a_args.size() / 2;

            if ((2 * sz_half) != a_args.size()) return;

            for (std::vector<std::string>::const_iterator it = a_args.begin(); it != a_args.end(); it += 2) {
                if (a_strip) {
                    std::string key = *it;
                    strip(key, both, ' ');
                    std::string val = *(it + 1);
                    strip(val, both, ' ');
                    m_args.push_back(arg(key, val));
                } else {
                    m_args.push_back(arg(*it, *(it + 1)));
                }
            }
        }

        void add(const std::vector<arg>& a_args)
        {
            inlib_vforcit(arg, a_args, it) m_args.push_back(*it);
        }

        int remove(const std::string& a_key)
        {
            size_t nbeg = m_args.size();

            for (std::vector<arg>::iterator it = m_args.begin(); it != m_args.end();) {
                if (a_key == (*it).first) {
                    it = m_args.erase(it);
                } else {
                    ++it;
                }
            }

            return int(nbeg) - int(m_args.size());
        }

        void remove_first()
        {
            m_args.erase(m_args.begin());
        }

        bool last(std::string& a_key, std::string& a_value) const
        {
            a_key.clear();
            a_value.clear();

            if (m_args.empty()) return false;

            a_key = m_args.back().first;
            a_value = m_args.back().second;
            return true;
        }

        bool prog_name(std::string& a_value) const
        {
            if (m_args.empty()) {
                a_value.clear();
                return false;
            }

            if (m_args[0].second.size()) {
                a_value.clear();
                return false;
            }

            a_value = m_args[0].first;
            return true;
        }

        bool file(std::string& a_file) const
        {
            std::string slast;
            std::string s;

            if ((m_args.size() > 1) //first arg is the program name !
                && last(slast, s)
                && (slast.find('-') != 0)
                && (s.empty())) {
                a_file = slast; //Last argument is not an option.
                return true;
            } else {
                a_file.clear();
                return false;
            }
        }

        std::vector<std::string> files(bool a_skip_first = true) const
        {
            // Get the serie of trailing args not beginning with '-'
            // and without a value (not of the form [-]xxx=yyy).
            // Note that an argument like that in between arguments
            // is NOT taken into account.
            std::vector<std::string> _files;

            if (m_args.empty()) return _files;

            std::vector<arg>::const_iterator it = m_args.begin();

            if (a_skip_first) it++;

            for (; it != m_args.end(); ++it) {
                if (((*it).first.find('-') == 0) || (*it).second.size()) {
                    _files.clear();
                } else {
                    _files.push_back((*it).first);
                }
            }

            return _files;
        }
        bool argcv(int& a_argc, char**& a_argv) const
        {
            // If using with :
            //   int argc;
            //   char** argv;
            //   args.argcv(argc,argv);
            // you can delete with :
            //   args::delete_argcv(argc,argv);
            if (m_args.empty()) {
                a_argc = 0;
                a_argv = 0;
                return true;
            }

            typedef char* _cstr_t;
            _cstr_t* av = new _cstr_t[m_args.size() + 1];

            if (!av) {
                a_argc = 0;
                a_argv = 0;
                return false;
            }

            a_argv = av;

            for (std::vector<arg>::const_iterator it = m_args.begin(); it != m_args.end(); ++it, av++) {
                std::string::size_type lf = (*it).first.length();
                std::string::size_type ls = (*it).second.length();
                std::string::size_type sz = lf;

                if (ls) sz += 1 + ls;

                char* p = new char[sz + 1];

                if (!p) {
                    a_argc = 0;    //some delete are lacking.
                    a_argv = 0;
                    return false;
                }

                *av = p;
                {
                    char* pf = (char*)(*it).first.c_str();

                    for (std::string::size_type i = 0; i < lf; i++, p++, pf++) {
                        *p = *pf;
                    }

                    *p = 0;
                }

                if (ls) {
                    *p = '=';
                    p++;
                }

                {
                    char* ps = (char*)(*it).second.c_str();

                    for (std::string::size_type i = 0; i < ls; i++, p++, ps++) {
                        *p = *ps;
                    }

                    *p = 0;
                }
            }

            *(a_argv + m_args.size()) = 0;
            a_argc = (int)m_args.size();
            return true;
        }
        static void delete_argcv(int& a_argc, char**& a_argv)
        {
            for (int index = 0; index < a_argc; index++) delete [] a_argv[index];

            delete [] a_argv;
            a_argc = 0;
            a_argv = 0;
        }
        bool known_options(const std::vector<std::string>& a_opts) const
        {
            inlib_vforcit(arg, m_args, it) {
                if ((*it).first.find('-') == 0) { //find '-' at first pos.
                    bool found = false;
                    inlib_vforcit(std::string, a_opts, it2) {
                        if ((*it).first == (*it2)) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) return false;
                }
            }
            return true;
        }

        void files_at_end(bool a_skip_first = true)
        {
            // reorder to have "file" arguments at end.
            if (m_args.empty()) return;

            std::vector<arg> _args;

            if (a_skip_first) _args.push_back(*(m_args.begin()));

            //first pass :
            {
                std::vector<arg>::const_iterator it = m_args.begin();

                if (a_skip_first) it++;

                for (; it != m_args.end(); ++it) {
                    if (((*it).first.find('-') == 0) || (*it).second.size()) {
                        _args.push_back(*it);
                    }
                }
            }
            //second pass :
            {
                std::vector<arg>::const_iterator it = m_args.begin();

                if (a_skip_first) it++;

                for (; it != m_args.end(); ++it) {
                    if (((*it).first.find('-') == 0) || (*it).second.size()) {
                    } else {
                        _args.push_back(*it);
                    }
                }
            }
            m_args = _args;
        }

        //NOTE : print is a Python keyword.
        void dump(std::ostream& a_out, const std::string& a_comment = "", const std::string& a_prefix = "") const
        {
            if (a_comment.size()) a_out << a_comment << std::endl;

            inlib_vforcit(arg, m_args, it) {
                a_out << a_prefix << "key = " << sout((*it).first) << ", value = " << sout((*it).second) << std::endl;
            }
        }

    public: //backcomp (for Panoramix).
        bool isAnArgument(const std::string& a_key) const
        {
            return is_arg(a_key);
        }
    protected:
        std::vector<arg> m_args;
    };

    inline bool check_args(const std::vector<std::string>& a_args, unsigned int a_number, std::ostream& a_out)
    {
        if (a_args.size() == a_number) return true;

        a_out << "bad argument number."
              << " Given " << (unsigned int)a_args.size()
              << " whilst " << a_number << " expected."
              << std::endl;
        return false;
    }

    inline bool check_min(const std::vector<std::string>& a_args, unsigned int a_number, std::string& a_last, std::ostream& a_out)
    {
        if (a_args.size() >= a_number) {
            if (a_number == 0) {
                if (a_args.empty()) {
                    a_last.clear();
                } else {
                    a_last = a_args[0];

                    for (size_t index = 1; index < a_args.size(); index++) a_last += " " + a_args[index];
                }
            } else {
                a_last = a_args[a_number - 1];

                for (size_t index = a_number; index < a_args.size(); index++) a_last += " " + a_args[index];
            }

            return true;
        }

        a_out << "bad argument number."
              << " Given " << (unsigned int)a_args.size()
              << " whilst at least " << a_number << " expected."
              << std::endl;
        return false;
    }

    inline bool check_min_args(const std::vector<std::string>& aArgs, unsigned int a_number, std::ostream& a_out)
    {
        if (aArgs.size() >= a_number) return true;

        a_out << "bad argument number."
              << " Given " << (unsigned int)aArgs.size()
              << " whilst at least " << a_number << " expected."
              << std::endl;
        return false;
    }

    inline bool check_or_args(const std::vector<std::string>& aArgs, unsigned int a_1, unsigned int a_2, std::ostream& a_out)
    {
        if ((aArgs.size() == a_1) || (aArgs.size() == a_2)) return true;

        a_out << "bad argument number."
              << " Given " << (unsigned int)aArgs.size()
              << " whilst " << a_1 << " or " << a_2 << " expected."
              << std::endl;
        return false;
    }

    inline std::string gui_toolkit(args& a_args, bool a_rm_in_args)
    {
        std::string driver;
        a_args.find("-toolkit", driver);

        if (a_rm_in_args) a_args.remove("-toolkit");

        if (driver.empty()) {
            if (a_args.is_arg("-Xt") ||
                a_args.is_arg("-xt") ||
                a_args.is_arg("-Xm") ||
                a_args.is_arg("-xm") ||
                a_args.is_arg("-Motif") ||
                a_args.is_arg("-motif")) {
                driver = "Xt";

                if (a_rm_in_args) {
                    a_args.remove("-Xt");
                    a_args.remove("-xt");
                    a_args.remove("-Xm");
                    a_args.remove("-xm");
                    a_args.remove("-Motif");
                    a_args.remove("-motif");
                }
            } else if (a_args.is_arg("-Win") ||
                       a_args.is_arg("-win") ||
                       a_args.is_arg("-Win32") ||
                       a_args.is_arg("-win32")) {
                driver = "Win";

                if (a_rm_in_args) {
                    a_args.remove("-Win");
                    a_args.remove("-win");
                    a_args.remove("-Win32");
                    a_args.remove("-win32");
                }
            } else if (a_args.is_arg("-NextStep") ||
                       a_args.is_arg("-nextstep")) {
                driver = "NextStep";

                if (a_rm_in_args) {
                    a_args.remove("-NextStep");
                    a_args.remove("-nextstep");
                }
            } else if (a_args.is_arg("-Gtk") ||
                       a_args.is_arg("-gtk")) {
                driver = "Gtk";

                if (a_rm_in_args) {
                    a_args.remove("-Gtk");
                    a_args.remove("-gtk");
                }
            } else if (a_args.is_arg("-Qt") ||
                       a_args.is_arg("-qt")) {
                driver = "Qt";

                if (a_rm_in_args) {
                    a_args.remove("-Qt");
                    a_args.remove("-qt");
                }
            } else if (a_args.is_arg("-SDL") ||
                       a_args.is_arg("-sdl")) {
                driver = "SDL";

                if (a_rm_in_args) {
                    a_args.remove("-SDL");
                    a_args.remove("-sdl");
                }
            } else if (a_args.is_arg("-Net") ||
                       a_args.is_arg("-net")) {
                driver = "Net";

                if (a_rm_in_args) {
                    a_args.remove("-Net");
                    a_args.remove("-net");
                }
            } else if (a_args.is_arg("-inex")) {
                driver = "inex";

                if (a_rm_in_args) {
                    a_args.remove("-inex");
                }
            }
        }

        return driver;
    }

    inline void window_size_from_args(const args& a_args, unsigned int& a_ww, unsigned int& a_wh)
    {
        // return some common window size (in pixels).
        if (a_args.is_arg("-iPod") || a_args.is_arg("-iPhone")) {
            a_ww = 320;
            a_wh = 480;
        } else if (a_args.is_arg("-iPad")) {
            a_ww = 768;
            a_wh = 1024;
        } else if (a_args.is_arg("-iPhone4")) {
            a_ww = 640;
            a_wh = 960;
        } else if (a_args.is_arg("-wallino")) { //emulate LAL/wallino aspect ratio.
            a_ww = 1024;
            a_wh = 512;
        } else if (a_args.is_arg("-SGS")) { //Samsung Galaxy S
            //a_ww = 320;
            //a_wh = 533;
            a_ww = 480;
            a_wh = 800;
        } else {
            if (a_args.find<unsigned int>("-ww", a_ww)) {
                if (a_args.find<unsigned int>("-wh", a_wh)) return;

                //A4 : we have ww but not wh :
                a_wh = (unsigned int)(a_ww * (29.7f / 21.0f)); //29.7/21 = 1.414
            } else { //we don't have ww.
                if (a_args.find<unsigned int>("-wh", a_wh)) {
                    //A4 : we have wh but not ww :
                    a_ww = (unsigned int)(a_wh * (21.0f / 29.7f));
                } else {
                    //we have nothing. Take a ww of 700. With A4 wh is then 990.
                    a_ww = 700;
                    a_wh = (unsigned int)(a_ww * (29.7f / 21.0f)); //29.7/21 = 1.414
                }
            }
        }

        if (a_args.is_arg("-land")) {
            unsigned int _ww = a_ww;
            unsigned int _wh = a_wh;
            a_ww = mx(_ww, _wh);
            a_wh = mn(_ww, _wh);
        }

        if (a_args.is_arg("-portrait")) {
            unsigned int _ww = a_ww;
            unsigned int _wh = a_wh;
            a_ww = mn(_ww, _wh);
            a_wh = mx(_ww, _wh);
        }
    }

    inline void remove_window_size_args(args& a_args)
    {
        //use with Wt apps.
        a_args.remove("-iPod");
        a_args.remove("-iPhone");
        a_args.remove("-iPad");
        a_args.remove("-iPhone4");
        a_args.remove("-SGS");
        a_args.remove("-ww");
        a_args.remove("-wh");
        a_args.remove("-land");
    }

    inline std::vector<std::string> to(int a_argc, char** a_argv)
    {
        std::vector<std::string> v;

        for (int index = 0; index < a_argc; index++) v.push_back(a_argv[index]);

        return v;
    }

}

#endif
