///////////////////////////////////////////////////////////////////////////////
/// \file ResourcesHolder.h
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#ifndef RESOURCES_HOLDER_H
#define RESOURCES_HOLDER_H

#include <map>
#include "ResourcePtr.h"
#include "core/Singleton.h"

///////////////////////////////////////////////////////////////////////////////
/// \namespace engn.
/// \brief Classes and methods implementing the Engine Layer of the game.
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
/// \class ResourcesHolder.
/// \brief Provider of a holder resources objects.
/// \details Provide generalized loading, getting and releasing methods  
///          to efficiently manage game's resources.
/// \tparam ResourceType Resource's type.
/// \tparam IdentifierType Resource identifier's type.
/// \remark Implemented as Singleton
///
///////////////////////////////////////////////////////////////////////////////
template <typename ResourceType, typename IdentifierType>
class ResourcesHolder 
   : public core::Singleton<ResourcesHolder<ResourceType, IdentifierType>>
{
   friend class core::Singleton<ResourcesHolder<ResourceType, IdentifierType>>;
private:
   /// Resources map, for resource retrieval.
   std::map<IdentifierType, ResourcePtr<ResourceType>> resourcesMap_;

public:
   /// \brief Destructor
	virtual ~ResourcesHolder ();

   /// \brief Load a specific resource from hard disk.
   /// \details Load a resource stocked in the hard disk from the path \em path
   ///          and identifie it by th identifier \em id in the resources map.
   /// \param id The identifier to be assigned to the loaded resource in the
   ///           resources map.
   /// \param path The path from which resource will be loaded from the hard
   ///             disk.
   /// \note Load sfml resources of the following types :
   ///       -  <tt>sf::Font</tt>
   ///       -  <tt>sf::Image</tt>
   ///       -  <tt>sf::SoundBuffer</tt>
   ///       -  <tt>sf::Texture</tt>
   ///  \note For loading a resource of type \c sf::Shader, use instead the
   ///  overloaded method \c load(IdentifierType const&, std::string const&, ArgType const&).
   ///  \note For managing resources of type \c sf::Music, use instead 
   ///  \c MusicPlayer class.
   void load (IdentifierType const id, std::string const & path);

   /// \brief Load a specific resource of type from hard disk.
   /// \details Load a resource stocked in the hard disk from 
   ///          the path \em path and assign it the identifier \em id in the 
   ///          resources map.
   /// \param id The identifier to be assigned to the loaded resource in the
   ///           resources map.
   /// \param path The path from which resource will be loaded from the hard
   ///             disk.
   /// \note Ideal to :
   ///       - Load sfml resource of types \c sf::Shader,
   ///       - Load a fragment of a \c sf::Texture resource, by calling
   ///         <tt>sf::Texture::load(std::string const&, sf::IntRect const&)
   ///         </tt>
   ///  \note For managing resources of type \c sf::Music, use instead 
   ///  \c MusicPlayer class.
   template <typename ArgType>
   void load (IdentifierType const id, std::string const& path, 
              ArgType const& arg);

   /// \brief Get a constant reference to the resource identified by \em id.
   /// \param id The resource identifier.
   /// \return Reference to the held resource.
   std::add_lvalue_reference_t<ResourceType> get (IdentifierType id);

   /// \brief Get a constant reference to the resource identified by \em id.
   /// \param id The resource identifier.
   /// \return Constant reference to the held resource.
   const std::add_lvalue_reference_t<ResourceType> get (IdentifierType id) 
      const;
   
   /// \brief Erase the resource identified by \em id.
   /// \param id The resource identifier in the resource map.
	void erase (IdentifierType id) noexcept(noexcept(resourcesMap_.erase(id)));

   /// \brief Clear the map, \em ie erase all resources from the map.
	void clear () noexcept(noexcept(resourcesMap_.clear()));

protected:
   /// \brief Default constructor.
	ResourcesHolder ();

   /// \brief Insert resource into the resources map.
   /// \details Insert the resource pointed by \em resourcePtr, of identifier 
   ///          \em id, in the resources map.
   /// \param resourcePtr Pointer to the resource to be inserted.
   /// \param id          Identifier of the resource to be inserted.
   void insert (IdentifierType id, ResourcePtr<ResourceType> resourcePtr);

   /// \brief Find resource.
   /// \details Find resource identified by \em id in the resources map.
   /// \param id The resource identifier.
   /// \return Reference to the found resource.
   /// \todo Throw specific exception if resource is not found.
   std::add_lvalue_reference_t<ResourceType> find (IdentifierType id);
}; // class ResourcesHolder

} // namespace rsc
}  // namespace engn

#include "ResourcesHolder.inl"

#endif	// RESOURCES_HOLDER_H