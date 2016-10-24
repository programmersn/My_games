///////////////////////////////////////////////////////////////////////////////
/// \file ResourcesHolder.cpp
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>

namespace engn
{
namespace rsc
{

template <typename ResourceType, typename IdentifierType>
ResourcesHolder<ResourceType, IdentifierType>::ResourcesHolder()
= default;

template <typename ResourceType, typename IdentifierType>
ResourcesHolder<ResourceType, IdentifierType>::~ResourcesHolder()
{
   resourcesMap_.clear();
   printf("~ResourcesHolder<ResourceType, IdentifierType>()");
}

template <typename ResourceType, typename IdentifierType>
void
ResourcesHolder<ResourceType, IdentifierType>::load(IdentifierType const  id, 
                                                    std::string    const& path)
{
   //<! \todo: Replace by logging method
   std::cout << "GAME_DEBUG--ResourcesHolder<ResourceType, IdentifierType>::load(): loading resource"
      "\"" + path + "\" ..."
      << std::endl;

   ResourcePtr<ResourceType> resourcePtr = makeResource<ResourceType>();
   if ( ! resourcePtr->loadFromFile(path))
      throw std::runtime_error("Unable to load resource from file "+path+"\n");
   this->insert(id, std::move(resourcePtr));
}

template <typename ResourceType, typename IdentifierType>
template <typename ArgType>
void
ResourcesHolder<ResourceType, IdentifierType>::load(IdentifierType const  id,
                                                    std::string    const& path,
                                                    ArgType        const& arg)
{
   ResourcePtr<ResourceType> resourcePtr = makeResource<ResourceType>();
   if ( ! resourcePtr->loadFromFile(path, arg))
      throw std::runtime_error("Unable to load resource from file "+path+"\n");
   this->insert(id, std::move(resourcePtr));
}

template <typename ResourceType, typename IdentifierType>
std::add_lvalue_reference_t<ResourceType>
ResourcesHolder<ResourceType, IdentifierType>::get(IdentifierType id)
{
   return this->find(id);
}

template <typename ResourceType, typename IdentifierType>
const std::add_lvalue_reference_t<ResourceType>
ResourcesHolder<ResourceType, IdentifierType>::get(IdentifierType id) const
{
   return this->find(id);
}

template <typename ResourceType, typename IdentifierType>
void
ResourcesHolder<ResourceType, IdentifierType>::erase(IdentifierType id) 
   noexcept(noexcept(resourcesMap_.erase(id)))
{
   resourcesMap_.erase(id);
}

template <typename ResourceType, typename IdentifierType>
void
ResourcesHolder<ResourceType, IdentifierType>::clear() 
   noexcept(noexcept(resourcesMap_.clear()))
{
   resourcesMap_.clear();
}

template <typename ResourceType, typename IdentifierType>
void
ResourcesHolder<ResourceType, IdentifierType>::insert (
   IdentifierType            id,
   ResourcePtr<ResourceType> resourcePtr
)
{    
   auto resourcePtrPair = std::make_pair(id, std::move(resourcePtr));
   
   std::pair<std::map<IdentifierType, ResourcePtr<ResourceType>>::iterator, 
             bool> inserted = resourcesMap_.insert(std::move(resourcePtrPair));
   
   assert(inserted.second);
}

template <typename ResourceType, typename IdentifierType>
std::add_lvalue_reference_t<ResourceType>
ResourcesHolder<ResourceType, IdentifierType>::find (IdentifierType id)
{
   std::map<IdentifierType, ResourcePtr<ResourceType>>::const_iterator found = 
      resourcesMap_.find(id);

   assert(resourcesMap_.end() != found);

   return *found->second;
}

}  // namespace rsc
}	// namespace engn