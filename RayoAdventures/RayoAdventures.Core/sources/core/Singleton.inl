///////////////////////////////////////////////////////////////////////////////
/// \file Singleton.inl
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#include <cassert>

namespace core
{

template <typename T>
std::unique_ptr<T>
Singleton<T>::Instance_ = nullptr;

template <typename T>
Singleton<T>::Singleton()
   = default;

template <typename T>
Singleton<T>::~Singleton()
{
   std::cout << "\n\n------------- ~Singleton()------------------\n\n";
}

template <typename T>
template <typename ... ArgsTypes>
inline static std::add_lvalue_reference_t<T>
Singleton<T>::getInstance (ArgsTypes&& ... args)
{
   printf ("getInstance()\n");
   if (nullptr == Instance_) {
      Instance_.reset(new T(std::forward<ArgsTypes>(args)...));
      assert(nullptr != Instance_);
   }
   return *Instance_;
}

} // namespace core
