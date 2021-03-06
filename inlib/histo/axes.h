// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_histo_axes
#define inlib_histo_axes

#include "axis.h"

namespace inlib {
    namespace histo {

        //TC is for a coordinate.
        //TO is for an offset used to identify a bin.

        template <class TC, class TO>
        inline bool is_out(const std::vector< axis<TC, TO> >& a_axes, TO a_offset)
        {
            TO offset = a_offset;
            int index;
            typename std::vector< axis<TC, TO> >::size_type dimension = a_axes.size();

            for (int iaxis = int(dimension) - 1; iaxis >= 0; iaxis--) {
                index = int(offset / a_axes[iaxis].m_offset);

                if (index == 0) return true;

                if (index == (int(a_axes[iaxis].m_number_of_bins) + 1)) return true;

                offset -= index * a_axes[iaxis].m_offset;
            }

            return false;
        }

        template <class TC, class TO>
        inline void get_indices(const std::vector< axis<TC, TO> >& a_axes, TO a_offset, std::vector<int>& a_is)
        {
            TO offset = a_offset;
            typename std::vector< axis<TC, TO> >::size_type dimension = a_axes.size();
            {
                for (int iaxis = int(dimension) - 1; iaxis >= 0; iaxis--) {
                    a_is[iaxis] = int(offset / a_axes[iaxis].m_offset);
                    offset -= a_is[iaxis] * a_axes[iaxis].m_offset;
                }
            }
            typedef unsigned int dim_t;

            for (dim_t iaxis = 0; iaxis < dimension; iaxis++) {
                if (a_is[iaxis] == 0) {
                    a_is[iaxis] = axis_UNDERFLOW_BIN;
                } else if (a_is[iaxis] == int(a_axes[iaxis].m_number_of_bins) + 1) {
                    a_is[iaxis] = axis_OVERFLOW_BIN;
                } else {
                    a_is[iaxis]--;
                }
            }
        }

        template <class TC, class TO>
        inline bool get_offset(const std::vector< axis<TC, TO> >& a_axes, const std::vector<int>& a_is, TO& a_offset)
        {
            // a_is[iaxis] is given in in-range indexing :
            //  - [0,n[iaxis]-1] for in-range bins
            //  - UNDERFLOW_BIN for the iaxis underflow bin
            //  - OVERFLOW_BIN for the iaxis overflow bin
            a_offset = 0;

            if (a_axes.empty()) return false;

            typename std::vector< axis<TC, TO> >::size_type dimension = a_axes.size();
            typename axis<TC, TO>::bn_t ibin;
            typedef unsigned int dim_t;

            for (dim_t iaxis = 0; iaxis < dimension; iaxis++) {
                if (!a_axes[iaxis].in_range_to_absolute_index(a_is[iaxis], ibin)) {
                    a_offset = 0;
                    return false;
                }

                a_offset += ibin * a_axes[iaxis].m_offset;
            }

            return true;
        }

    }
}

#endif




