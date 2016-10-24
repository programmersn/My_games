///////////////////////////////////////////////////////////////////////////////
/// \file ResourcePtr.inl
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
namespace engn
{
namespace rsc
{

template <typename ResourceType>
constexpr ResourcePtr<ResourceType>::ResourcePtr()
   noexcept(noexcept(std::unique_ptr<ResourceType>()))
   : smartPtr_{}
{
}

template <typename ResourceType>
ResourcePtr<ResourceType>::ResourcePtr(ResourceType* rawPtr)
   noexcept(noexcept(std::unique_ptr<ResourceType>(rawPtr)))
   : smartPtr_{rawPtr}
{
}

template <typename ResourceType>
ResourcePtr<ResourceType>::ResourcePtr(ResourcePtr<ResourceType>&& rhs)
noexcept(noexcept(std::unique_ptr<ResourceType>(std::move(rhs.smartPtr_))))
   : smartPtr_ { std::move(rhs.smartPtr_) }
{
   rhs.smartPtr_.reset();
}

template <typename ResourceType>
ResourcePtr<ResourceType>::~ResourcePtr()
{
   smartPtr_.release();
}

template <typename ResourceType>
ResourcePtr<ResourceType>&
ResourcePtr<ResourceType>::operator=(ResourcePtr<ResourceType>&& rhs) & 
   noexcept(noexcept(smartPtr_.operator=(rhs.smartPtr_)))
{
   smartPtr_ = std::move(rhs.smartPtr_);
   rhs.smartPtr_.reset();

   return *this;
}

template <typename ResourceType>
ResourcePtr<ResourceType>& 
ResourcePtr<ResourceType>::operator= (std::nullptr_t) & 
   noexcept(noexcept(smartPtr_.operator=(nullptr)))
{
   smartPtr_ = nullptr;
   return *this;
}

template <typename ResourceType>
std::add_lvalue_reference_t<ResourceType>
ResourcePtr<ResourceType>::operator*() const
{
   return smartPtr_.operator*();
}

template <typename ResourceType>
ResourceType*
ResourcePtr<ResourceType>::operator->() const noexcept
{
   return smartPtr_.operator->();
}

template <typename ResourceType>
ResourceType*
ResourcePtr<ResourceType>::get() const 
   noexcept(noexcept(smartPtr_.get()))
{
   return smartPtr_->get();
}

template <typename ResourceType>
ResourceType*
ResourcePtr<ResourceType>::release() 
   noexcept(noexcept(smartPtr_.release()))
{
   return smartPtr_->release();
}

template <typename ResourceType>
void
ResourcePtr<ResourceType>::reset(ResourceType* rscPtr)
   noexcept(noexcept(smartPtr_.reset()))
{
   smartPtr_->reset(rscPtr);
}

template <typename ResourceType>
ResourcePtr<ResourceType>::operator bool() const
   noexcept(noexcept(smartPtr_.operator bool()))
{
   return bool(smartPtr_);
}

template <typename ResourceType, typename ... ArgsTypes>
ResourcePtr<ResourceType>
makeResource(ArgsTypes&& ... args)
{
   return ResourcePtr<ResourceType> (
      new ResourceType(std::forward<ArgsTypes>(args)...)
   );
}

} // namespace rsc
}  // namespace engn
