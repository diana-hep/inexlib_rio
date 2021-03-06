// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_cids
#define inlib_cids

#include "cid.h"

#include <string>
#include "typedefs.h" //byte

namespace inlib {

    inline cid _cid(byte)
    {
        return 1;
    }
    inline cid _cid(char)
    {
        return 2;
    }
    inline cid _cid(unsigned short)
    {
        return 3;
    }
    inline cid _cid(short)
    {
        return 4;
    }
    inline cid _cid(unsigned int)
    {
        return 5;
    }
    inline cid _cid(int)
    {
        return 6;
    }
    inline cid _cid(float)
    {
        return 7;
    }
    inline cid _cid(double)
    {
        return 8;
    }
    inline cid _cid(bool)
    {
        return 9;
    }

    // not compiler types :
    inline cid _cid(uint64)
    {
        return 10;
    }
    inline cid _cid(int64)
    {
        return 11;
    }
    inline cid _cid(const std::string&)
    {
        return 12;
    }
    inline cid _cid(fits_bit)
    {
        return 13;
    }
    inline cid _cid(csv_time)
    {
        return 14;
    }

    //NOTE : avoid time_t which is defined in general as a long
    //       and is then ambiguous relative to int/int64.

    //NOTE : if adding some, it must not exceed 20. Else, you have to change
    //       the below for std::vector.

}

#include <vector>

namespace inlib {

    // For rntuple and rroot::ntuple::column_element.
    // The read::icolumn<T> needs a _cid(T) with T :
    //   std::vector< [basic_type, std::vector<basic_type>] >

    template <class T>
    inline cid _cid(const std::vector<T>&)
    {
        return 20 + _cid(T());
    }

    template <class T>
    inline cid _cid_std_vector()
    {
        return 20 + _cid(T());
    }

    // Then : cid for std::vector< std::vector<T> > is going to be :
    //   20+_cid(std::vector<T>) = 2*20+_cid(T)

    //WARNING : rroot/cids start at 100.
    //WARNING : rroot/geo_cids start at 1000.

}

namespace inlib {

    inline bool cid2s(cid a_id, std::string& a_s)
    {
        // NOTE : the returned string must not contain space.
        if (a_id == _cid(char(0)))       {
            a_s = "char";
            return true;
        } else if (a_id == _cid(short(0)))      {
            a_s = "short";
            return true;
        } else if (a_id == _cid(int(0)))        {
            a_s = "int";
            return true;
        } else if (a_id == _cid(float(0)))      {
            a_s = "float";
            return true;
        } else if (a_id == _cid(double(0)))     {
            a_s = "double";
            return true;
        } else if (a_id == _cid(std::string())) {
            a_s = "string";
            return true;
        }
        // NOTE : the below do not follow the AIDA convention.
        else if (a_id == _cid((unsigned char)0))  {
            a_s = "uchar";    //AIDA=byte
            return true;
        } else if (a_id == _cid((unsigned short)0)) {
            a_s = "ushort";    //AIDA not defined
            return true;
        } else if (a_id == _cid((unsigned int)0))   {
            a_s = "uint";    //AIDA not defined
            return true;
        } else if (a_id == _cid(bool(true)))        {
            a_s = "bool";    //AIDA=boolean
            return true;
        } else if (a_id == _cid(int64(0)))          {
            a_s = "int64";    //AIDA=long
            return true;
        } else if (a_id == _cid(uint64(0)))         {
            a_s = "uint64";    //AIDA=not defined
            return true;
        } else if (a_id == _cid_std_vector<char>())        {
            a_s = "char[]";
            return true;
        } else if (a_id == _cid_std_vector<short>())       {
            a_s = "short[]";
            return true;
        } else if (a_id == _cid_std_vector<int>())         {
            a_s = "int[]";
            return true;
        } else if (a_id == _cid_std_vector<float>())       {
            a_s = "float[]";
            return true;
        } else if (a_id == _cid_std_vector<double>())      {
            a_s = "double[]";
            return true;
        } else if (a_id == _cid_std_vector<std::string>()) {
            a_s = "string[]";
            return true;
        } else if (a_id == _cid_std_vector<unsigned char>())        {
            a_s = "uchar[]";
            return true;
        } else if (a_id == _cid_std_vector<unsigned short>())       {
            a_s = "ushort[]";
            return true;
        } else if (a_id == _cid_std_vector<unsigned int>())         {
            a_s = "uint[]";
            return true;
        } else if (a_id == _cid_std_vector<bool>())                 {
            a_s = "bool[]";
            return true;
        } else if (a_id == _cid_std_vector<int64>())                {
            a_s = "int64[]";
            return true;
        } else if (a_id == _cid_std_vector<uint64>())               {
            a_s = "uint64[]";
            return true;
        }

        a_s.clear();
        return false;
    }

}

#endif
