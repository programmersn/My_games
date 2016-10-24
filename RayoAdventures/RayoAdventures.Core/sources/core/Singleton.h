///////////////////////////////////////////////////////////////////////////////
/// \file Singleton.h
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include "Uncopyable.h"
#include "Unmovable.h"

///////////////////////////////////////////////////////////////////////////////
/// \namespace core.
/// \brief The core functionalites of the application.
///
///////////////////////////////////////////////////////////////////////////////
namespace core
{
///////////////////////////////////////////////////////////////////////////////
/// \class Singleton.
/// \brief Template class of the pattern design \c Singleton.
/// \details Provide singleton pattern property for inherited classes.
/// \tparam T Type of the object to be instancied.
/// \note This class is uncopyable and unmovable.
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class Singleton : Unmovable, Uncopyable
{
private:
   /// \brief Unique instance of the object of type \c T.
   static std::unique_ptr<T> Instance_;

protected:
   /// \brief Default constructor.
   Singleton();
   /// \brief Default destructor.
   virtual ~Singleton();
public:
   /// \brief Get the classe's unique instance.
   /// \details Get the unique instance of the object of type \c T.
   ///          If the instance hasn't been created yet, then create it.
   /// \tparam ArgsTypes Arguments types param
   /// \param args Arguments parameters pack, to be forwarded to the 
   ///             constructor of the type \c T.
   /// \return Lvalue reference to the \c T unique instance.
   /// \see Jiang Bian's thread-safe C++11 singleton class.
   /// \todo Make this method \em thread-safe.
   template <typename ... ArgsTypes>
   static std::add_lvalue_reference_t<T> getInstance (ArgsTypes&& ... args);
}; // class Singleton

} // namespace core

#include "Singleton.inl"

#endif // SINGLETON_H