// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_omap
#define inlib_omap

// A vector of pair<key,value> ordered according key.

#include <vector>

#include "binary_search.h"

namespace inlib {

    /*
    template <class K,class T>
    class omit : public std::vector< std::pair<K,T> >::iterator {
      typedef typename std::pair<K,T> element;
      typedef typename std::vector<element>::iterator parent;
    public:
      omit():parent() {}
    public:
      virtual ~omit() {}
    public:
      omit(const omit& a_from):parent(a_from){}
      omit(const parent& a_from):parent(a_from){}

      omit& operator=(const omit& a_from){
        parent::operator=(a_from);
        return *this;
      }
      omit& operator=(const parent& a_from){
        parent::operator=(a_from);
        return *this;
      }
    public:
      void operator=(const T& a_value){
        element& e = parent::operator*();
        e.second = a_value;
      }
    };
    */

    template <class K, class T>
    class omap : public std::vector< std::pair<K, T> > {
        typedef typename std::pair<K, T> element;
        typedef typename std::vector<element> parent;
    public:
        typedef typename std::vector<element>::iterator iterator;
        typedef typename std::vector<element>::iterator const_iterator;
    public:
        omap(): parent() {}
        virtual ~omap() {}
    public:
        omap(const omap& a_from): parent(a_from) {}
        omap& operator=(const omap& a_from)
        {
            parent::operator=(a_from);
            return *this;
        }
    public: //operators
        /*
          typedef typename inlib::omit<K,T> mit;
          mit operator[](const K& a_key){
            mit it;
            for(it=parent::begin();it!=parent::end();++it){
              if(a_key<(*it).first) {
                return insert(it,element(a_key,T()));
              } else if(a_key==(*it).first) {
                return it;
              }
            }
            parent::push_back(element(a_key,T()));
            return parent::end()-1;
          }

          iterator operator[](const K& a_key){
            iterator it;
            for(it=parent::begin();it!=parent::end();++it){
              if(a_key<(*it).first) {
                return insert(it,element(a_key,T()));
              } else if(a_key==(*it).first) {
                return it;
              }
            }
            parent::push_back(element(a_key,T()));
            return parent::end()-1;
          }
        */

        T& operator[](const K& a_key)
        {
            #ifdef inlib_stl_vector
            element* pos = parent::m_data;

            for (unsigned int index = 0; index < parent::m_number; index++, pos++) {
                if (a_key < pos->first) {
                    _insert(index, element(a_key, T()));
                    //can't use pos after the upper.
                    return (parent::m_data + index)->second;
                } else if (a_key == pos->first) {
                    return pos->second;
                }
            }

            parent::push_back(element(a_key, T()));
            return (parent::m_data + parent::m_number - 1)->second;
            #else
            iterator it;

            for (it = parent::begin(); it != parent::end(); ++it) {
                if (a_key < (*it).first) {
                    it = insert(it, element(a_key, T()));
                    return (*it).second;
                } else if (a_key == (*it).first) {
                    return (*it).second;
                }
            }

            parent::push_back(element(a_key, T()));
            return parent::back().second;
            #endif
        }

    public:
        iterator find(const K& a_key)
        {
            int index = binary_search(*this, a_key);

            if (index == not_found()) return parent::end();

            return parent::begin() + index;
        }
        const_iterator find(const K& a_key) const
        {
            int index = binary_search(*this, a_key);

            if (index == not_found()) return parent::end();

            return parent::begin() + index;
        }

    public:
        void clear()
        {
            parent::clear();
        }
        typedef unsigned int size_type;
        size_type size() const
        {
            return parent::size();
        }
        bool empty() const
        {
            return parent::empty();
        }

    protected:
        // for binary_search :
        static int not_found()
        {
            return -1;
        }
    public:
        const K& value(unsigned int a_index) const
        {
            return parent::operator[](a_index).first;
        }
    };

}

#endif
