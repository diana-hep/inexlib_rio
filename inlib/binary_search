// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_binary_search
#define inlib_binary_search

// used in omap.

namespace inlib {

    template <class V, class K>
    int binary_search(const V& a_v, const K& a_k) //return -1 if not found.
    {
        // a_v is assumed to be ordered.
        // V is assumed to have methods :
        //  [unsigned] int size()
        //  const K& value([unsigned] int)
        //from TObjArray::BinarySearch.
        // within the while(), base is always >=0 and last>=base>=0
        // so that position>=0. Moreover base<=last<=(a_v.size()-1)=max_index
        // so that :
        //   base+last <= 2*max_index
        //   (base+last)/2 <=max_index
        // then position is in range of a_v.
        int base = 0;
        int last = a_v.size() - 1;
        int position;

        while (last >= base) {
            position = (base + last) / 2;
            const K& k = a_v.value(position);

            if (k == a_k) return position;

            if (a_k < k)
                last = position - 1;
            else
                base = position + 1;
        }

        return -1;
    }

}

#endif
