// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_wroot_tree
#define inlib_wroot_tree

#include "itree.h"
#include "iobject.h"

#include "branch_element.h"

namespace inlib {
    namespace wroot {

        class tree : public virtual iobject, public virtual itree {
            #ifdef INLIB_MEM
            static const std::string& s_class()
            {
                static const std::string s_v("inlib::wroot::tree");
                return s_v;
            }
            #endif
        public: //iobject
            virtual const std::string& name() const
            {
                return m_name;
            }
            virtual const std::string& title() const
            {
                return m_title;
            }
            virtual const std::string& store_class_name() const
            {
                static const std::string s_v("TTree");
                return s_v;
            }
            virtual bool stream(buffer& a_buffer) const
            {
                unsigned int c;

                if (!a_buffer.write_version(5, c)) return false;

                if (!Named_stream(a_buffer, m_name, m_title)) return false;

                // Beurk.
                if (!AttLine_stream(a_buffer)) return false;

                if (!AttFill_stream(a_buffer)) return false;

                if (!AttMarker_stream(a_buffer)) return false;

                double fEntries = (double)m_entries;

                if (!a_buffer.write(fEntries)) return false;

                double fTotBytes = (double)m_tot_bytes;
                double fZipBytes = (double)m_zip_bytes;

                if (!a_buffer.write(fTotBytes)) return false;

                if (!a_buffer.write(fZipBytes)) return false;

                if (!a_buffer.write((double)0)) return false; //fSavedBytes

                if (!a_buffer.write((int)0)) return false;   //fTimerInterval

                if (!a_buffer.write((int)25)) return false;  //fScanField (25)

                if (!a_buffer.write((int)0)) return false;   //fUpdate

                if (!a_buffer.write((int)1000000000)) return false; //fMaxEntryLoop

                int fMaxVirtualSize = 0;
                int fAutoSave = 100000000;

                if (!a_buffer.write(fMaxVirtualSize)) return false;

                if (!a_buffer.write(fAutoSave)) return false;

                if (!a_buffer.write((int)1000000)) return false;   //fEstimate;

                if (!m_branches.stream(a_buffer)) return false;

                {
                    ObjArray<base_leaf> m_leaves;
                    inlib_vforcit(branch*, m_branches, itb) {
                        const std::vector<base_leaf*>& leaves = (*itb)->leaves();
                        inlib_vforcit(base_leaf*, leaves, itl) {
                            m_leaves.push_back(*itl); //WARNING : ownership touchy.
                        }
                    }

                    if (!m_leaves.stream(a_buffer)) return false;

                    m_leaves.clear();
                } //WARNING : important.

                // fIndexValues (TArrayD).
                if (!a_buffer.write_array(std::vector<double>())) return false; //TArrayD

                // fIndex (TArrayI).
                if (!a_buffer.write_array(std::vector<int>())) return false; //TArrayI

                if (!a_buffer.set_byte_count(c)) return false;

                return true;
            }
        public: //itree
            virtual void add_tot_bytes(uint32 a_n)
            {
                m_tot_bytes += a_n;
            }
            virtual void add_zip_bytes(uint32 a_n)
            {
                m_zip_bytes += a_n;
            }
            virtual idir& dir()
            {
                return m_dir;
            }
            virtual const idir& dir() const
            {
                return m_dir;
            }
        public:
            tree(idir& a_dir, //for branch/baskets(which are keys)
                 const std::string& a_name,
                 const std::string& a_title)
                : m_dir(a_dir)
                , m_out(a_dir.file().out())
                , m_name(a_name)
                , m_title(a_title)
                , m_entries(0)
                , m_tot_bytes(0)
                , m_zip_bytes(0)
            {
                #ifdef INLIB_MEM
                mem::increment(s_class().c_str());
                #endif
                a_dir.append_object(this); //a_dir takes ownership of tree.
            }
            virtual ~tree()
            {
                #ifdef INLIB_MEM
                mem::decrement(s_class().c_str());
                #endif
            }
        protected:
            tree(const tree& a_from)
                : iobject(a_from), itree(a_from)
                , m_dir(a_from.m_dir)
                , m_out(a_from.m_out)
            {}
            tree& operator=(const tree&)
            {
                return *this;
            }
        public:
            //const std::vector<branch*>& branches() const {return m_branches;}

            branch* create_branch(const std::string& a_name)
            {
                branch* br = new branch(*this, a_name, m_name);
                m_branches.push_back(br);
                return br;
            }

            template <class T>
            std_vector_be<T>* create_std_vector_be(const std::string& a_name, std::vector<T>& a_vec)
            {
                std_vector_be<T>* br = new std_vector_be<T>(*this, a_name, m_name, a_vec);
                m_branches.push_back(br);
                return br;
            }

            bool fill(uint32& a_nbytes)
            {
                // Fill all branches of a Tree :
                //   This function loops on all the branches of this tree.
                //   For each branch, it copies to the branch buffer (basket) the current
                //   values of the leaves data types.
                //   If a leaf is a simple data type, a simple conversion to a machine
                //   independent format has to be done.
                a_nbytes = 0;
                inlib_vforcit(branch*, m_branches, it) {
                    //FIXME if ((*it)->testBit(kDoNotProcess)) continue;
                    uint32 n;

                    if (!(*it)->fill(n)) {
                        a_nbytes = 0;
                        return false;
                    }

                    a_nbytes += n;
                }
                m_entries++;
                //if (fTotBytes - fSavedBytes > fAutoSave) {
                //  if(!autoSave()) return false;
                //}
                return true;
            }

        protected:
            idir& m_dir;
            std::ostream& m_out;
            //Named
            std::string m_name;
            std::string m_title;

            ObjArray<branch> m_branches;
            uint64 m_entries;   // Number of entries
            uint64 m_tot_bytes; // Total number of bytes in branches before compression
            uint64 m_zip_bytes; // Total number of bytes in branches after compression
        };

    }
}

//inlib_build_use kernel

#endif
