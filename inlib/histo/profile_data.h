// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_histo_profile_data
#define inlib_histo_profile_data

#include "histo_data.h"

namespace inlib {
    namespace histo {

        template <class TC, class TO, class TN, class TW, class TV>
        class profile_data : public histo_data<TC, TO, TN, TW> {
            typedef histo_data<TC, TO, TN, TW> parent;
        public:
            typedef std::vector<TV> vs_t;
        public:
            profile_data()
                : parent()
                , m_is_profile(true)
                , m_cut_v(false)
                , m_min_v(0)
                , m_max_v(0)
            {}

            profile_data(const histo_data<TC, TO, TN, TW>& a_from)
                : parent(a_from)
                , m_is_profile(false)
                , m_cut_v(false)
                , m_min_v(0)
                , m_max_v(0)
            {}

        public:
            profile_data(const profile_data& a_from)
                : parent(a_from)
                , m_is_profile(a_from.m_is_profile)
                , m_bin_Svw(a_from.m_bin_Svw)
                , m_bin_Sv2w(a_from.m_bin_Sv2w)
                , m_cut_v(a_from.m_cut_v)
                , m_min_v(a_from.m_min_v)
                , m_max_v(a_from.m_max_v)
            {}

            profile_data& operator=(const profile_data& a_from)
            {
                parent::operator=(a_from);
                m_is_profile = a_from.m_is_profile;
                m_bin_Svw = a_from.m_bin_Svw;
                m_bin_Sv2w = a_from.m_bin_Sv2w;
                m_cut_v = a_from.m_cut_v;
                m_min_v = a_from.m_min_v;
                m_max_v = a_from.m_max_v;
                return *this;
            }

            virtual ~profile_data() {}

        public:
            profile_data& operator=(const histo_data<TC, TO, TN, TW>& a_from)
            {
                //for Rio_THisogram.
                histo_data<TC, TO, TN, TW>::operator=(a_from);

                if (&a_from == this) return *this;

                m_is_profile = false;
                m_bin_Svw.clear();
                m_bin_Sv2w.clear();
                m_cut_v = false;
                m_min_v = 0;
                m_max_v = 0;
                return *this;
            }

        public:
            bool m_is_profile; //for Rio_THistogram.
            std::vector<TV> m_bin_Svw;
            std::vector<TV> m_bin_Sv2w;
            bool m_cut_v;
            TV m_min_v;
            TV m_max_v;
        };

    }
}

#endif
