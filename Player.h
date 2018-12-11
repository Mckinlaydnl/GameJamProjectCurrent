#pragma once

// Project Includes
#include "Framework/SpriteObject.h"
#include "GridObject.h"
#include "Framework/AnimationSystem.h"

// Library Include
#include <SFML/Audio.hpp>
#include <vector>

class Player : public GridObject
{

	// Functions

public:

	Player();

	// Overriding Methods
	void Input(sf::Event _gameEvent);
	void Update(sf::Time _frameTime);
	void Draw(sf::RenderTarget& _frameTime);

	void Spawn();

	sf::Vector2f GetPosition();

	void HandleCollision(std::vector<sf::FloatRect> _platforms);

private:


	// Data

private:

	// Assets 
	sf::Sprite m_sprite;
	//AnimationSystem m_animation;

	// State 
	sf::Vector2f m_velocity;
	bool m_touchingGround;
};