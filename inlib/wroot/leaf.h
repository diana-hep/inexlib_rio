// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_leaf
#define inlib_wroot_leaf

#include "base_leaf.h"

namespace inlib {
    namespace wroot {

        inline const std::string& leaf_store_class(char)
        {
            static const std::string s_v("TLeafB");
            return s_v;
        }
        inline const std::string& leaf_store_class(short)
        {
            static const std::string s_v("TLeafS");
            return s_v;
        }
        inline const std::string& leaf_store_class(int)
        {
            static const std::string s_v("TLeafI");
            return s_v;
        }
        inline const std::string& leaf_store_class(float)
        {
            static const std::string s_v("TLeafF");
            return s_v;
        }
        inline const std::string& leaf_store_class(double)
        {
            static const std::string s_v("TLeafD");
            return s_v;
        }
        inline const std::string& leaf_string_store_class()
        {
            static const std::string s_v("TLeafC");
            return s_v;
        }
        inline const std::string& leaf_element_store_class()
        {
            static const std::string s_v("TLeafElement");
            return s_v;
        }

        template <class T>
        class leaf : public base_leaf {
            typedef base_leaf parent;
        public: //ibo
            virtual const std::string& store_cls() const
            {
                return leaf_store_class(T());
            }
            virtual bool stream(buffer& a_buffer) const
            {
                unsigned int c;

                if (!a_buffer.write_version(1, c)) return false;

                if (!parent::stream(a_buffer)) return false;

                if (!a_buffer.write(m_min)) return false;

                if (!a_buffer.write(m_max)) return false;

                if (!a_buffer.set_byte_count(c)) return false;

                return true;
            }
        public: //base_leaf
            virtual bool fill_basket(buffer& a_buffer) const
            {
                return a_buffer.write<T>(m_value);
            }
        public:
            leaf(std::ostream& a_out,
                 wroot::branch& a_branch,
                 const std::string& a_name,
                 const std::string& a_title)
                : parent(a_out, a_branch, a_name, a_title)
                , m_min(T()), m_max(T())
                , m_value(T())
            {
                m_length = 1;
                m_length_type = sizeof(T);
            }
            virtual ~leaf() {}
        protected:
            leaf(const leaf& a_from): ibo(a_from), parent(a_from) {}
            leaf& operator=(const leaf&)
            {
                return *this;
            }
        public:
            void fill(const T& a_value)
            {
                m_value = a_value;
            }
        protected:
            T m_min;    //Minimum value if leaf range is specified
            T m_max;    //Maximum value if leaf range is specified
            T m_value;
        };

        class leaf_string : public base_leaf {
            typedef base_leaf parent;
        public: //ibo
            virtual const std::string& store_cls() const
            {
                return leaf_string_store_class();
            }
            virtual bool stream(buffer& a_buffer) const
            {
                unsigned int c;

                if (!a_buffer.write_version(1, c)) return false;

                if (!parent::stream(a_buffer)) return false;

                if (!a_buffer.write(m_min)) return false;

                if (!a_buffer.write(m_max)) return false;

                if (!a_buffer.set_byte_count(c)) return false;

                return true;
            }
        public: //base_leaf
            virtual bool fill_basket(buffer& a_buffer) const
            {
                size_t len = ::strlen(m_value.c_str());
                leaf_string& self = const_cast<leaf_string&>(*this);

                if (len >= (size_t)m_max) self.m_max = len + 1;

                if (len >= m_length) self.m_length = len + 1;

                if (len < 255) {
                    if (!a_buffer.write<unsigned char>((unsigned char)len)) return false;
                } else {
                    if (!a_buffer.write<unsigned char>(255)) return false;

                    if (!a_buffer.write<uint32>(len)) return false;
                }

                if (len) if (!a_buffer.write_fast_array(m_value.c_str(), len)) return false;

                return true;
            }
        public:
            leaf_string(std::ostream& a_out,
                        wroot::branch& a_branch,
                        const std::string& a_name,
                        const std::string& a_title)
                : parent(a_out, a_branch, a_name, a_title)
                , m_min(0), m_max(0)
            {
                m_length_type = 1;
            }
            virtual ~leaf_string() {}
        protected:
            leaf_string(const leaf_string& a_from): ibo(a_from), parent(a_from) {}
            leaf_string& operator=(const leaf_string&)
            {
                return *this;
            }
        public:
            void fill(const std::string& a_value)
            {
                m_value = a_value;
            }
        protected:
            int m_min; //Minimum value if leaf range is specified
            int m_max; //Maximum value if leaf range is specified
            std::string m_value;
        };

        class leaf_element : public base_leaf {
            typedef base_leaf parent;
        public:
            virtual const std::string& store_cls() const
            {
                return leaf_element_store_class();
            }
            virtual bool stream(buffer& a_buffer) const
            {
                unsigned int c;

                if (!a_buffer.write_version(1, c)) return false;

                if (!parent::stream(a_buffer)) return false;

                if (!a_buffer.write(fID)) return false;

                if (!a_buffer.write(fType)) return false;

                if (!a_buffer.set_byte_count(c)) return false;

                return true;
            }
        public: //base_leaf
            virtual bool fill_basket(buffer&) const
            {
                m_out << "inlib::wroot::leaf_element::fill_basket : dummy." << std::endl;
                return false;
            }
        public:
            leaf_element(std::ostream& a_out,
                         wroot::branch& a_branch,
                         const std::string& a_name,
                         const std::string& a_title,
                         int a_id, int a_type)
                : parent(a_out, a_branch, a_name, a_title)
                , fID(a_id)
                , fType(a_type)
            {}
            virtual ~leaf_element() {}
        protected:
            leaf_element(const leaf_element& a_from): ibo(a_from), parent(a_from) {}
            leaf_element& operator=(const leaf_element& a_from)
            {
                parent::operator=(a_from);
                return *this;
            }
        protected:
            int fID;   //element serial number in fInfo
            int fType; //leaf type
        };

    }
}

#endif
