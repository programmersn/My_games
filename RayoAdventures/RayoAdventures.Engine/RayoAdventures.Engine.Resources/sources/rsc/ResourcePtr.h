///////////////////////////////////////////////////////////////////////////////
/// \file ResourcePtr.hpp
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#ifndef RESOURCE_PTR_H
#define RESOURCE_PTR_H

#include <memory>

///////////////////////////////////////////////////////////////////////////////
/// \namespace engn.
/// \brief The engine layer.
///
///////////////////////////////////////////////////////////////////////////////
namespace engn
{
///////////////////////////////////////////////////////////////////////////////
/// \namespace rsc.
/// \brief Define resources structures and classes.
///
///////////////////////////////////////////////////////////////////////////////
namespace rsc
{

///////////////////////////////////////////////////////////////////////////////
/// \class ResourcePtr.
/// \brief Generic class which provide smart resource pointer encapsulation,
/// which simplify the usage of resource smart pointer. 
/// \tparam \em ResourceType Underlying resource's type.
/// \note All the <tt>noexcept</tt> specifiers of the methods of this class   
/// depends on the <tt>noexcept</tt> specifiers of the methods of the  
/// encapsulated smart pointer class.
///////////////////////////////////////////////////////////////////////////////
template <typename ResourceType>
class ResourcePtr : core::Uncopyable
{
private:
   /// \brief Smart pointer, owner of the pointer to the \em ResourceType 
   ///        resource
   std::unique_ptr<ResourceType> smartPtr_;

public:
   /// \brief Default constructor.
   /// \details Constructs a resource pointer that owns nothing.
   ///          Value-initialize the stored raw pointer.
   /// \post <tt>nullptr == this->get()<\tt>.
   /// \note Simple encapsulation of 
   ///       \code std::unique_ptr<ResourceType>::unique_ptr() \endcode.
   constexpr ResourcePtr () 
      noexcept(noexcept(std::unique_ptr<ResourceType>()));

   /// \brief Constructor
    explicit ResourcePtr(ResourceType* rawPtr)
      noexcept(noexcept(std::unique_ptr<ResourceType>(rawPtr)));

   /// \brief Move constructor
   /// \details Constructs \c ResourcePtr by transferring ownership of
   ///          \em smartPtr_ from \em rhs to \c this.
   /// \note It's a simple encapsulation of 
   /// <tt>std::unique_ptr<ResourceType>::unique_ptr(std::unique_ptr<ResourceType>&&)</tt>.
   ResourcePtr (ResourcePtr<ResourceType>&& rhs)
      noexcept(noexcept(std::unique_ptr<ResourceType>(std::move(rhs.smartPtr_))));

   /// \brief Destructor.
   /// \details Release the owned resource.
   /// \post <tt>nullptr == this->get()</tt>.
   virtual ~ResourcePtr();

   /// \brief Move assignment operator
   /// \details Transfers ownership of \em smartPtr_ from \em rhs to \c *this
   /// \return \code *this \endcode.
   /// \note It's a simple encapsulation of 
   /// <tt>
   /// std::unique_ptr<ResourceType>& std::unique_ptr<ResourceType>::operator=(std::unique_ptr<ResourceType>&&) 
   /// </tt>.
   ResourcePtr<ResourceType>& operator= (ResourcePtr<ResourceType>&& rhs) & 
      noexcept(noexcept(smartPtr_.operator=(rhs.smartPtr_)));

   /// \brief Encapsulated overloaded assignment operator.
   ResourcePtr<ResourceType>& operator= (std::nullptr_t) & 
      noexcept(noexcept(smartPtr_.operator=(nullptr)));
   
   /// \brief Encapsulated dereferencing operator. 
   std::add_lvalue_reference_t<ResourceType> operator* () const;

   /// \brief Encapsulated dereferencing operator.
   ///\todo - Debug the noexcept problem
   ResourceType* operator->() const
      noexcept;

   ///
   ResourceType* get () const
      noexcept(noexcept(smartPtr_.get()));

   ///
   ResourceType* release () 
      noexcept(noexcept(smartPtr_.release()));

   ///
   void reset(ResourceType* rscPtr = nullptr)
      noexcept(noexcept(smartPtr_.reset()));

   ///
   explicit operator bool() const
      noexcept(noexcept(smartPtr_.operator bool()));
}; // class ResourcePtr

/// \brief Make smart resource pointer.
/// \details Make a smart resource pointer, which own a raw resource pointer.
/// \note Encapsulation of <tt>make_unique<ResourceType>(<em>args</em>)</tt>.
template <typename ResourceType, typename ... ArgsTypes>
ResourcePtr<ResourceType>
makeResource(ArgsTypes&& ... args);

} // namespace rsc
} // namespace engn

#include "ResourcePtr.inl"

#endif // RESOURCE_PTR_H

