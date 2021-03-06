// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_date
#define inlib_wroot_date

//NOTE : Windows : localtime_r does not exist.
//WARNING : G4 does not want to include windows.h.

#ifdef INLIB_USE_WINDOWS
    #include <windows.h>
#else
    #include <time.h>
#endif

namespace inlib {
    namespace wroot {

        typedef unsigned int date;

        inline date get_date()
        {
            // Set Date/Time to current time as reported by the system.
            // Date and Time are encoded into one single unsigned 32 bit word.
            // Date is stored with the origin being the 1st january 1995.
            // Time has 1 second precision.
            #ifdef INLIB_USE_WINDOWS
            SYSTEMTIME tp;
            ::GetLocalTime(&tp);
            unsigned int year   = tp.wYear - 1900;
            unsigned int month  = tp.wMonth;
            unsigned int day    = tp.wDay;
            unsigned int hour   = tp.wHour;
            unsigned int min    = tp.wMinute;
            unsigned int sec    = tp.wSecond;
            #else
            time_t tloc = ::time(0);
            struct tm tpa;
            struct tm* tp = (tm*)::localtime_r(&tloc, &tpa); //does not exist on Windows.
            //struct tm *tp = (tm*)::localtime(&tloc); //not thread safe (but exist on Windows).
            unsigned int year   = tp->tm_year;
            unsigned int month  = tp->tm_mon + 1;
            unsigned int day    = tp->tm_mday;
            unsigned int hour   = tp->tm_hour;
            unsigned int min    = tp->tm_min;
            unsigned int sec    = tp->tm_sec;
            #endif
            return ((year - 95) << 26 | month << 22 | day << 17 | hour << 12 | min << 6 | sec);
        }

    }
}

//inlib_build_use kernel

#endif
