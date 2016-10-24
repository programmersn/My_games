///////////////////////////////////////////////////////////////////////////////
/// \file Kernel.h
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include "core/Singleton.h"

///////////////////////////////////////////////////////////////////////////////
/// \namespace engn.
/// \brief Classes and methods implementing the Engine Layer of the game.
///
///////////////////////////////////////////////////////////////////////////////
namespace engn
{
///////////////////////////////////////////////////////////////////////////////
/// \namespace ker.
/// \brief Classes and methods implementing the Kernel of the game.
///
///////////////////////////////////////////////////////////////////////////////
namespace ker
{
///////////////////////////////////////////////////////////////////////////////
/// \class Kernel.
/// \brief The kernel of the game software.
/// \note Implemented as \em singleton, which implies the \em uncopyable-ness  
///       and \em unmovable-ness properties of this class.
///
///////////////////////////////////////////////////////////////////////////////
class Kernel final : public core::Singleton<Kernel>
{
   friend class core::Singleton<Kernel>;
private:
   ///// \brief Unique instance of \c Kernel object (singleton).
   //static Kernel * Instance_;
   /// \brief Constant time during which each video frame will be displayed.
   static const sf::Time TimePerFrame_;
   /// \brief Application's render window.
   sf::RenderWindow window_;

   // hero attributes
   //!< To put in a specific class
   sf::Sprite    sprite_;
   sf::Vector2f  position_;
   sf::Vector2f  scale_;
   sf::Vector2f  speed_;
   bool          isMovingRight_;
   bool          isMovingLeft_;
   bool          isMovingUp_;
   bool          isMovingDown_;
   std::string str_ = "First";
public:
   /// \brief Destructor.
   ~Kernel();
   /// \brief Run the current game engine's instance.
   void run ();

private:
   /// \brief Constructor;
   Kernel ();
   Kernel (std::string const & str) : str_{str} { }
   /// \brief Init the current instance.
   void init();
   /// \brief Handle game events.
   void handleEvents ();
   /// \brief Update the game state.
   void update () noexcept;
   /// \brief Render the game's current frame.
   void render () noexcept;
   /// \brief Manage user input events.
   /// \param code Code of the key
   /// \param isPressed True if the key is pressed.
   void manageUserEvents (sf::Keyboard::Key code, bool isPressed) noexcept;
};	// class Kernel

} // namespace ker
}	// namespace engn

#endif	// GAME_ENGINE_H
