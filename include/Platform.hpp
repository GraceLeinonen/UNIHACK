#ifndef Platform_HPP
#define Platform_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Keys.hpp"
#include "Animator.hpp"

#define WINDOW m_context->m_window

class Platform : public Engine::State
{
public:
  Platform(std::shared_ptr<Context>& context, std::string name);
  ~Platform() override;

  void Init() override;
  void ProcessInput() override;
  void Update(const sf::Time& deltaTime) override; 
  void Draw() override;

  /// @brief Returns the correction needed to clip some entity within a boundary
  /// @param centre - The world position of the entity
  /// @param padding - Some padding representing how much space the entity takes up from its central position
  /// @param bounds - The boundary that the entity will be clipped within
  /// @return The correction vector that can be applied to the given centre position to clip the entity within the boundary
  sf::Vector2f clipWithinBounds(sf::Vector2f centre, sf::Vector2f padding, sf::IntRect bounds);

private:
  std::shared_ptr<Context> m_context;

	/// @brief The view that represents the camera of the program
	sf::View view;

  // The following varaibles are for testing purposes only
  bool isCharMoving = false;

  sf::Texture tileTex;
  sf::Texture charTex;

  sf::IntRect worldRect;
  sf::Sprite tile;
  sf::Sprite character;
  Animator charAnim;
};

#endif