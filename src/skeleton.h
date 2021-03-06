#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player_states.h"
#include "tiles.h"

class SkeletonState;

class Skeleton
{
private:
    SkeletonState* state;
	
	sf::Texture texture;
	sf::Sprite sprite;

	bool is_faced_right;
	sf::Vector2f velocity;
	float scale_factor;

	void set_state(SkeletonState* new_state);

public:
	Skeleton(sf::Vector2f position);

	sf::Vector2f get_center() const;
	sf::Vector2f get_position() const;
	void set_position(sf::Vector2f position);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	bool handle_collision(const sf::FloatRect& rect, bool is_hookable);
	void handle_all_collisions(sf::Vector2i tile_counts, sf::Vector2f tile_sizes, const std::vector<Tile>& tilemap);


	~Skeleton();

	friend class SkeletonState;
	friend class skeletonIdle;
	friend class skeletonRunning;
};