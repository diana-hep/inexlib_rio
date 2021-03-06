// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_rroot_ntuple
#define inlib_rroot_ntuple

// to have same API than rcsv::ntuple.

#include "../rntuple.h"

#include "tree.h"
#include "leaf.h"
#include "stl_vector.h"

#include "../cids.h"
#include "../vfind.h"
#include "../vmanip.h"
#include "../ntuple_binding.h"

#ifdef INLIB_MEM
    #include "../mem.h"
#endif

namespace inlib {
    namespace rroot {

        class ntuple : public virtual read::intuple {
        public:
            static const std::string& s_class()
            {
                static const std::string s_v("inlib::rroot::ntuple");
                return s_v;
            }
        public: //intuple
            virtual void start()
            {
                m_index = -1;
            }
            virtual bool next()
            {
                m_index++;

                if ((uint64)m_index >= m_tree.entries()) return false;

                return true;
            }
            virtual read::icol* find_icol(const std::string& a_name)
            {
                return find_named<read::icol>(m_cols, a_name);
            }
            virtual const std::vector<read::icol*>& columns() const
            {
                return m_cols;
            }
        public:

            template <class T>
            class column : public virtual read::icolumn<T> {
                typedef read::icolumn<T> parent;
            public:
                static cid id_class()
                {
                    return 200 + _cid(T());
                }
            public: //icol
                virtual void* cast(cid a_class) const
                {
                    if (void* p = cmp_cast<column>(this, a_class)) {
                        return p;
                    }

                    return parent::cast(a_class);
                }
                virtual cid id_cls() const
                {
                    return id_class();
                }
            public: //icol
                virtual const std::string& name() const
                {
                    return m_leaf.name();
                }
            public: //icolumn<T>
                virtual bool get_entry(T& a_v) const
                {
                    unsigned int n;

                    if (!m_leaf.branch().find_entry(uint32(m_index), n)) {
                        a_v = T();
                        return false;
                    }

                    a_v = m_leaf.value();
                    return true;
                }
                virtual bool fetch_entry() const
                {
                    //NOTE : it is ok to have a NULL m_user_var.
                    unsigned int n;

                    if (!m_leaf.branch().find_entry(uint32(m_index), n)) {
                        if (m_user_var) *m_user_var = T();

                        return false;
                    }

                    if (m_user_var) *m_user_var = m_leaf.value();

                    return true;
                }
            public:
                column(leaf<T>& a_leaf, int64& a_index, T* a_user_var = 0)
                    : m_leaf(a_leaf)
                    , m_index(a_index) //WARNING : we keep the ref !
                    , m_user_var(a_user_var) //not owner
                {}
                virtual ~column() {}
            protected:
                column(const column& a_from)
                    : read::intuple(a_from)
                    , parent(a_from)
                    , m_leaf(a_from.m_leaf)
                    , m_index(a_from.m_index)
                    , m_user_var(a_from.m_user_var)
                {}
                column& operator=(const column& a_from)
                {
                    if (&a_from == this) return *this;

                    m_user_var = a_from.m_user_var;
                    return *this;
                }
            protected:
                leaf<T>& m_leaf;
                int64& m_index; //WARNING : a ref.
                T* m_user_var;
            };

            class column_string : public virtual read::icol {
            public:
                static cid id_class()
                {
                    static const std::string s_v;
                    return _cid(s_v);
                }
            public: //icol
                virtual void* cast(cid a_class) const
                {
                    if (void* p = cmp_cast<column_string>(this, a_class)) return p;

                    return 0;
                }
                virtual cid id_cls() const
                {
                    return id_class();
                }
                virtual const std::string& name() const
                {
                    return m_leaf.name();
                }
            public:
                virtual bool fetch_entry() const
                {
                    //NOTE : it is ok to have a NULL m_user_var.
                    unsigned int n;

                    if (!m_leaf.branch().find_entry(uint32(m_index), n)) {
                        if (m_user_var) *m_user_var = std::string();

                        return false;
                    }

                    if (m_user_var) *m_user_var = m_leaf.value();

                    return true;
                }
            public:
                column_string(leaf_string& a_leaf, int64& a_index, std::string* a_user_var = 0)
                    : m_leaf(a_leaf)
                    , m_index(a_index) //WARNING : we keep the ref !
                    , m_user_var(a_user_var) //not owner
                {}
                virtual ~column_string() {}
            protected:
                column_string(const column_string& a_from)
                    : read::icol(a_from)
                    , m_leaf(a_from.m_leaf)
                    , m_index(a_from.m_index)
                    , m_user_var(a_from.m_user_var)
                {}
                column_string& operator=(const column_string& a_from)
                {
                    if (&a_from == this) return *this;

                    m_user_var = a_from.m_user_var;
                    return *this;
                }
            protected:
                leaf_string& m_leaf;
                int64& m_index; //WARNING : a ref.
                std::string* m_user_var;
            };

            template <class RT, class T>
            class column_element : public virtual read::icolumn<T> {
                typedef read::icolumn<T> parent;
            public:
                static cid id_class()
                {
                    return 300 + _cid(T());
                }
            public: //icol
                virtual void* cast(cid a_class) const
                {
                    if (void* p = cmp_cast<column_element>(this, a_class)) {
                        return p;
                    }

                    return parent::cast(a_class);
                }
                virtual cid id_cls() const
                {
                    return id_class();
                }
            public: //icol
                virtual const std::string& name() const
                {
                    return m_leaf.name();
                }
            public: //icolumn<T>
                virtual bool get_entry(T& a_v) const
                {
                    unsigned int n;

                    if (!m_leaf.branch().find_entry(uint32(m_index), n)) {
                        a_v = T();
                        return false;
                    }

                    if (!m_be)  {
                        a_v = T();
                        return false;
                    }

                    iro* obj = m_be->object(); //Not owner.

                    if (!obj) {
                        a_v = T();
                        return false;
                    }

                    RT* v = id_cast<iro, RT>(*obj);

                    if (!v) {
                        a_v = T();
                        return false;
                    }

                    a_v = *v; //it assumes a T::operator=(RT)
                    return true;
                }
                virtual bool fetch_entry() const
                {
                    unsigned int n;

                    if (!m_leaf.branch().find_entry(uint32(m_index), n)) {
                        if (m_user_var) *m_user_var = T();

                        return false;
                    }

                    if (!m_be)  {
                        if (m_user_var) *m_user_var = T();

                        return false;
                    }

                    iro* obj = m_be->object(); //Not owner.

                    if (!obj)  {
                        if (m_user_var) *m_user_var = T();

                        return false;
                    }

                    RT* v = id_cast<iro, RT>(*obj);

                    if (!v)  {
                        if (m_user_var) *m_user_var = T();

                        return false;
                    }

                    if (m_user_var) *m_user_var = *v; //it assumes a T::operator=(RT)

                    return true;
                }
            public:
                column_element(leaf_element& a_leaf, int64& a_index, T* a_user_var = 0)
                    : m_leaf(a_leaf)
                    , m_index(a_index) //WARNING : we keep the ref !
                    , m_be(0)
                    , m_user_var(a_user_var) //not owner
                {
                    m_be = safe_cast<branch, branch_element>(m_leaf.branch());
                }
                virtual ~column_element() {}
            protected:
                column_element(const column_element& a_from)
                    : read::intuple(a_from), parent(a_from)
                    , m_leaf(a_from.m_leaf)
                    , m_index(a_from.m_index)
                    , m_be(a_from.m_be)
                    , m_user_var(a_from.m_user_var)
                {}
                column_element& operator=(const column_element& a_from)
                {
                    if (&a_from == this) return *this;

                    m_be = a_from.m_be;
                    m_user_var = a_from.m_user_var;
                    return *this;
                }
            protected:
                leaf_element& m_leaf;
                int64& m_index; //WARNING : a ref.
                branch_element* m_be;
                T* m_user_var;
            };

        public:
            ntuple(tree& a_tree): m_tree(a_tree), m_index(-1)
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
            }
            virtual ~ntuple()
            {
                inlib::clear<read::icol>(m_cols);
                #ifdef INLIB_MEM
                mem::decrement(s_class().c_str());
                #endif
            }
        protected:
            ntuple(const ntuple& a_from)
                : read::intuple(a_from), m_tree(a_from.m_tree)
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
            }
            ntuple& operator=(const ntuple&)
            {
                return *this;
            }
        public:
            bool initialize(std::ostream& a_out, const ntuple_binding& a_bd = ntuple_binding())
            {
                inlib::clear<read::icol>(m_cols);
                std::vector<base_leaf*> leaves = m_tree.find_leaves();
                inlib_vforcit(base_leaf*, leaves, it) {
                    base_leaf* bl = (*it);

                    if (find_named<read::icol>(m_cols, bl->name())) {
                        a_out << "inlib::rroot::ntuple::initialize :"
                              << " column with name " << sout(bl->name())
                              << " already exists."
                              << std::endl;
                        inlib::clear<read::icol>(m_cols);
                        return false;
                    }

                    //a_out << "inlib::rroot::ntuple::initialize :"
                    //      << " entries " << bl->branch().entry_number() << "."
                    //      << std::endl;

                    if (leaf<float>* lf = safe_cast<base_leaf, leaf<float> >(*bl)) {
                        column<float>* col = new column<float>(*lf, m_index, a_bd.find_variable<float>(bl->name()));
                        m_cols.push_back(col);
                    } else if (leaf<double>* ld = safe_cast<base_leaf, leaf<double> >(*bl)) {
                        column<double>* col = new column<double>(*ld, m_index, a_bd.find_variable<double>(bl->name()));
                        m_cols.push_back(col);
                    } else if (leaf<int>* li = safe_cast<base_leaf, leaf<int> >(*bl)) {
                        column<int>* col = new column<int>(*li, m_index, a_bd.find_variable<int>(bl->name()));
                        m_cols.push_back(col);
                    } else if (leaf_string* ls = safe_cast<base_leaf, leaf_string >(*bl)) {
                        column_string* col = new column_string(*ls, m_index, a_bd.find_variable<std::string>(bl->name()));
                        m_cols.push_back(col);
                    } else if (leaf_element* le = safe_cast<base_leaf, leaf_element>(*bl)) {
                        branch_element* be = safe_cast<branch, branch_element>(le->branch());

                        if (be->class_name() == "vector<string>") {
                            typedef std::string el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                            //unsigned int n;
                            //if(!be->find_entry(0,n)) {}
                        } else if (be->class_name() == "vector<unsigned short>") {
                            typedef unsigned short el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<short>") {
                            typedef short el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<unsigned int>") {
                            typedef unsigned int el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<unsigned long>") { //beurk!
                            typedef uint64 el_t; //it is ok to map to an uint64 ?
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                            //unsigned int n;
                            //if(!be->find_entry(0,n)) {}
                        } else if (be->class_name() == "vector<int>") {
                            typedef int el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<float>") {
                            typedef float el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<double>") {
                            typedef double el_t;
                            typedef column_element< stl_vector<el_t> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<vector<unsigned short> >") {
                            typedef std::vector<unsigned short> el_t;
                            typedef column_element< stl_vector_vector<unsigned short> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<vector<short> >") {
                            typedef std::vector<short> el_t;
                            typedef column_element< stl_vector_vector<short> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<vector<unsigned int> >") {
                            typedef std::vector<unsigned int> el_t;
                            typedef column_element< stl_vector_vector<unsigned int> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<vector<int> >") {
                            typedef std::vector<int> el_t;
                            typedef column_element< stl_vector_vector<int> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else if (be->class_name() == "vector<vector<float> >") {
                            typedef std::vector<float> el_t;
                            typedef column_element< stl_vector_vector<float> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                            //unsigned int n;
                            //if(!be->find_entry(0,n)) {}
                        } else if (be->class_name() == "vector<vector<double> >") {
                            typedef std::vector<double> el_t;
                            typedef column_element< stl_vector_vector<double> , std::vector<el_t> > ce_t;
                            ce_t* col = new ce_t(*le, m_index, a_bd.find_variable< std::vector<el_t> >(bl->name()));
                            m_cols.push_back(col);
                        } else {
                            a_out << "inlib::rroot::ntuple::initialize :"
                                  << " WARNING : leaf element"
                                  << " with name " << inlib::sout(bl->name())
                                  << ",title " << inlib::sout(bl->title())
                                  << " br_elem class name " << be->class_name() << "."
                                  << " entries " << be->entry_number() << "."
                                  << std::endl;
                        }
                    } else {
                        a_out << "inlib::rroot::ntuple::initialize :"
                              << " WARNING : column type not yet handled for leaf"
                              << " with name " << inlib::sout(bl->name())
                              << " and title " << inlib::sout(bl->title()) << "."
                              << " s_cls() is " << inlib::sout(bl->s_cls()) << "."
                              << " Not fatal."
                              << std::endl;
                    }
                }
                unsigned int num = m_cols.size();

                if (!num) {
                    a_out << "inlib::rroot::ntuple::initialize :"
                          << " zero columns."
                          << std::endl;
                    return false;
                }

                //a_out << "inlib::rroot::ntuple::initialize :"
                //      << " number of columns " << num << "."
                //      << std::endl;
                return true;
            }

            bool get_row() const
            {
                bool status = true;
                inlib_vforcit(read::icol*, m_cols, it) {
                    if (!(*it)->fetch_entry()) status = false;
                }
                return status;
            }
        protected:
            tree& m_tree;
            std::vector<read::icol*> m_cols;
            int64 m_index;
        };

    }
}

#endif
