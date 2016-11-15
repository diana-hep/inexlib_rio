// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_hash_table
#define inlib_hash_table

#ifdef INLIB_MEM
    #include "mem.h"
#endif

namespace inlib {

    template <class K, class V>
    class hash_table {
        #ifdef INLIB_MEM
        static const std::string& s_class()
        {
            static const std::string s_v("inlib::hash_table");
            return s_v;
        }
        #endif
    private:
        class node {
            #ifdef INLIB_MEM
            static const std::string& s_class()
            {
                static const std::string s_v("inlib::hash_table::node");
                return s_v;
            }
            #endif
        public:
            node()
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
            }
            virtual ~node()
            {
                #ifdef INLIB_MEM
                mem::decrement(s_class().c_str());
                #endif
            }
        protected:
            node(const node&)
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
            }
            node& operator=(const node&)
            {
                return *this;
            }
        public:
            K m_key;
            V m_value;
            node* m_next;
        };
        typedef node* node_p;

    protected:
        virtual unsigned int hash(const K&) = 0;
        virtual bool cmp(const K&, const K&) = 0; //true=equal
    public:
        hash_table(unsigned int a_sz = 1024): NR_BUCKETS(a_sz), m_buckets(0)
        {
            #ifdef INLIB_MEM
            mem::increment(s_class().c_str());
            #endif
            m_buckets = new node_p[NR_BUCKETS];

            for (unsigned int i = 0; i < NR_BUCKETS; i++) m_buckets[i] = 0;
        }
        virtual ~hash_table()
        {
            clear();
            delete [] m_buckets;
            #ifdef INLIB_MEM
            mem::decrement(s_class().c_str());
            #endif
        }
    protected:
        hash_table(const hash_table&)
        {
            #ifdef INLIB_MEM
            mem::increment(s_class().c_str());
            #endif
        }
        hash_table& operator=(const hash_table&)
        {
            return *this;
        }
    public:
        bool insert(const K& a_key, const V& a_v)
        {
            unsigned int bucket = hash(a_key) % NR_BUCKETS;
            node* nd;
            node** tmp = m_buckets + bucket;

            while (*tmp) {
                if (cmp(a_key, (*tmp)->m_key)) break;

                tmp = &((*tmp)->m_next);
            }

            if (*tmp) {
                nd = *tmp;
                //nd->m_key = a_key;
                nd->m_value = a_v;
            } else {
                nd = new node;

                if (!nd) return false;

                nd->m_next = 0;
                *tmp = nd;
                nd->m_key = a_key;
                nd->m_value = a_v;
            }

            return true;
        }

        bool find(const K& a_key, V& a_v)
        {
            unsigned int bucket = hash(a_key) % NR_BUCKETS;
            node* nd = m_buckets[bucket];

            while (nd) {
                if (cmp(a_key, nd->m_key)) {
                    a_v = nd->m_value;
                    return true;
                }

                nd = nd->m_next;
            }

            return false;
        }

        void clear()
        {
            node_p* pos = m_buckets;

            for (unsigned int i = 0; i < NR_BUCKETS; i++, pos++) {
                if (*pos) delete_bucket(*pos);

                delete *pos;
                *pos = 0;
            }
        }
    protected:
        void delete_bucket(node*& a_buck)
        {
            if (a_buck->m_next) delete_bucket(a_buck->m_next);

            delete a_buck->m_next;
            a_buck->m_next = 0;
        }
    protected:
        unsigned int NR_BUCKETS;
        node_p* m_buckets;
    };

}

#endif
