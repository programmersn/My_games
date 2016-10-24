///////////////////////////////////////////////////////////////////////////////
/// \file Kernel.cpp
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include "Kernel.h"
#include "rsc/ResourcesHolder.h"
#include "rsc/ResourceId.h"

namespace engn
{

namespace ker
{

sf::Time const
Kernel::TimePerFrame_ { sf::seconds(1.f / 60.f) };

Kernel::Kernel()
   : window_ { sf::VideoMode{700, 600}, "Rayo adventures",
               sf::Style::None },
   sprite_ {},
   position_ { 50.f, 50.f },
   scale_ { 0.25, 0.25 },
   speed_ { 1.f, 1.f },
   isMovingRight_ { false },
   isMovingLeft_ { false },
   isMovingUp_ { false },
   isMovingDown_ { false }
{
   this->init();
}

Kernel::~Kernel()
{
   window_.close();
   std::cout << "~Kernel" << std::endl;
}

void
Kernel::init()
{
   using TexturesHolder =
      rsc::ResourcesHolder<sf::Texture,
      rsc::ResourceId::Texture>;
   TexturesHolder & texturesHolder = TexturesHolder::getInstance();

   texturesHolder.load(rsc::ResourceId::Texture::RayoIdle_1,
                       "./resources/textures/rayo/Idle_1.png");
   // Why we need to use reference to texture here ?
   sf::Texture& rayoTexture =
      texturesHolder.get(rsc::ResourceId::Texture::RayoIdle_1);
   sprite_.setTexture(rayoTexture);
   sprite_.setScale(sf::Vector2f(1 / 3.f, 1 / 3.f));
}

void
Kernel::run()
{
   sf::Clock clock;
   sf::Time elapsedTime = sf::Time::Zero;

   while (window_.isOpen()) {
      this->handleEvents();
      elapsedTime += clock.restart();
      while (elapsedTime > TimePerFrame_) {
         this->handleEvents();
         this->update();
         elapsedTime -= TimePerFrame_;
      }
      this->render();
   }
/*
   while(m_window.isOpen()) {
      this->handleEvents();
      sf::Time elapsedTime = clock.restart();
      timeSinceLastUpdate += clock.restart();
      while(timeSinceLastUpdate > Kernel::TimePerFrame_) {
         this->handleEvents();
         this->update();
         timeSinceLastUpdate -= Kernel::TimePerFrame_;
      }
      this->render();
   }*/
}

void
Kernel::handleEvents()
{
   sf::Event event;
   while (window_.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::KeyPressed:
         this->manageUserEvents(event.key.code, true);
         break;
      case sf::Event::KeyReleased:
         this->manageUserEvents(event.key.code, false);
         break;
      default:
         break;
      }
   }
}

void
Kernel::update() noexcept
{
   sf::Vector2f localSpeed(0.f, 0.f);

   if (isMovingRight_)
      localSpeed.x += speed_.x;
   if (isMovingLeft_)
      localSpeed.x -= speed_.x;
   if (isMovingUp_)
      localSpeed.y -= speed_.y;
   if (isMovingDown_)
      localSpeed.y += speed_.y;

   sprite_.move(localSpeed /**(float)Kernel::TimePerFrame_.asMilliseconds()*/);
}

void
Kernel::render() noexcept
{
   window_.clear();
//	m_window.draw(m_sprite2);
   window_.draw(sprite_);
   window_.display();
}

void
Kernel::manageUserEvents(sf::Keyboard::Key key, bool isPressed) noexcept
{
   if (sf::Keyboard::Escape == key && isPressed)
      window_.close();
   else if (sf::Keyboard::D == key)
      isMovingRight_ = isPressed;
   else if (sf::Keyboard::Q == key)
      isMovingLeft_ = isPressed;
   else if (sf::Keyboard::Z == key)
      isMovingUp_ = isPressed;
   else if (sf::Keyboard::S == key)
      isMovingDown_ = isPressed;
}

} // namespace ker
}  // namespace engn
