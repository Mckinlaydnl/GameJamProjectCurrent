// Project Includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "GridObject.h"

// Constants
#define JUMP_SPEED -1500.0f
#define GRAVITY 2000.0f
#define RUN_SPEED_INITIAL 500.0f

// Constructor
Player::Player()
	: GridObject()
	, m_sprite ()
	, m_velocity (0.0f, 0.0f)
	, m_touchingGround (false)
	
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));

	// TODO: Set up animation
	//m_animation.SetSprite(m_sprite);

}

void Player::Input(sf::Event _gameEvent)
{
	// Read the input from the keyboard and convert it
	// to a direction to move in (and then move)

	// Was the event a key press?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		// Yes it was a key press!
		// Check if the player pressed the jump button
		if (_gameEvent.type == sf::Event::KeyPressed)
		{
			// Check if the button was space
			if (m_touchingGround == true)
			{
				// Set the players upward velocity
				m_velocity.y = JUMP_SPEED;
			}
		}

		// What key was pressed?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// It was W!
			// Move up
			
		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// It was A!
			// Move left
			
		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// It was S!
			// Move down
		
		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// It was D!
			// Move right
		
		}
	}
}

void Player::Update(sf::Time _frameTime)
{
	// Apply gravity to our velocity 
	if (m_touchingGround == false)
	{
		float velocityChange = GRAVITY * _frameTime.asSeconds();
		m_velocity.y += velocityChange;
	}

	// Move sprite based on velocity
	sf::Vector2f currentPosition = m_sprite.getPosition();
	sf::Vector2f positionChange = m_velocity * _frameTime.asSeconds();
	m_sprite.setPosition(currentPosition + positionChange);

}

void Player::Draw(sf::RenderTarget& _target)
{
	_target.draw(m_sprite);
}

//void Player::Spawn()
//{
	//m_sprite.setPosition(500, 500);
	//m_velocity.y = 0;
	//m_velocity.x = 0;
//}

sf::Vector2f Player::GetPosition()
{
	return m_sprite.getPosition();
}

void Player::HandleCollision(std::vector<sf::FloatRect> _walls)
{
	// Record whether we used to be touching the ground
	bool wereTouchingGround = m_touchingGround;

	// Assume we did not collide
	m_touchingGround = false;

	// Get the collider for the player
	sf::FloatRect playerCollider = m_sprite.getGlobalBounds();

	// Loop through each wall collider
	for (auto it = _walls.begin(); it != _walls.end(); ++it)
	{
		// Go to iterator pointer and get rect
		sf::FloatRect wallCollider = *it;

		// Does our sprite intersect a wall?
		if (playerCollider.intersects(wallCollider))
		{
			// Yes it intersects!

			// Check the bottom of our feet is touching the
			// top of the wall

			// Create feet collider
			sf::FloatRect feetCollider = playerCollider;
			// Set our feet to be 10 pixels fro  the bottom of the player collider
			feetCollider.top += playerCollider.height - 10;
			// Set our feet collider height to be 10 pixels
			feetCollider.height = 10;

			//Create wall top collider
			sf::FloatRect wallTop = wallCollider;
			wallTop.height = 10;

			// Are the feet touching the top of the wall?
			if (feetCollider.intersects(wallTop))
			{
				// Yes! Feet are touching

				// Record that we're touching the ground
				m_touchingGround = true;

				// Check of we are falling downward
				// and not already touching the ground
				if (wereTouchingGround == false && m_velocity.y > 0)
				{
					// We have now just touched the ground
					m_velocity.y = 0;
				}
			}

		}
	}
	// TODO: Jump animation
}

