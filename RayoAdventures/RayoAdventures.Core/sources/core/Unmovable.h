///////////////////////////////////////////////////////////////////////////////
/// \file Unmovable.h
/// \author Noua�m SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#ifndef UNMOVABLE_H
#define UNMOVABLE_H

///////////////////////////////////////////////////////////////////////////////
/// \namespace core.
/// \brief The core components of the engine layer.
///
///////////////////////////////////////////////////////////////////////////////
namespace core
{

///////////////////////////////////////////////////////////////////////////////
/// \struct Unmovable.
/// \brief Provide unmovable-ness property for inherited classes.
///
///////////////////////////////////////////////////////////////////////////////
struct Unmovable
{
   Unmovable ()                             = default;
   virtual ~Unmovable()                     = default;

   Unmovable(Unmovable &&)                   = delete;
   Unmovable & operator= (Unmovable &&)       = delete;
};

} // namespace core

#endif // namespace UNMOVABLE_H