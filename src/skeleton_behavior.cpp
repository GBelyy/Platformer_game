#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_states.h"
#include "skeleton_behavior.h"

using namespace std;

class Skeleton;
class Player;
class SkeletonState;

SkeletonStrategy::SkeletonStrategy() {};

void SkeletonStrategy::update(Skeleton* skeleton, Player& player, float dt) {
    skeleton->set_state(new skeletonIdle(skeleton));
    skeleton->state->update(skeleton, dt);
};

SkeletonStrategy::~SkeletonStrategy() {};



Wait::Wait(Skeleton* skeleton)
{
    skeleton->velocity = {0, 0};
    skeleton->set_state(new skeletonIdle(skeleton));
}

void Wait::update(Skeleton* skeleton, Player& player, float dt)
{
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) <= 30 && abs(player.get_position().y - skeleton->get_position().y) <= 30)
    {
        skeleton->set_strategy(new Attacking(skeleton));
    }
}


Attacking::Attacking(Skeleton* skeleton)
{
    skeleton->set_state(new skeletonAttack(skeleton));
}

void Attacking::update(Skeleton* skeleton, Player& player, float dt)
{
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) >= min_attak_dist || 
    abs(player.get_position().y - skeleton->get_position().y) >= 100)
        skeleton->set_strategy(new Wait(skeleton));
    
}