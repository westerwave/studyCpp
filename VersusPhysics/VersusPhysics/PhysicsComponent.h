#pragma once
#include "Component.h"
#include "PhysicsDescription.h"
#include "PhysicsState.h"
#include "Constants.h"
#include "GameObject.h"
#include "World.h"

class PhysicsComponent : public Component
{
public:

	PhysicsComponent(PhysicsState _State, PhysicsDescription _Description) :
		State(_State),
		Description(_Description)
	{
	}

	virtual void Update() override;

	sf::Vector2f GetPosition()
	{
		return State.Position;
	}

	sf::Vector2f GetSize() const
	{
		return Description.Size;
	}

	sf::Vector2f GetCenter() const
	{
		return State.Position + (Description.Size * 0.5f);
	}

	void ProcessMessage(Message Msg);

	PhysicsState State;
private:
	PhysicsDescription Description;

	void Move();

	void CheckForCollisionAndResolve(World* GameWorld);

	bool IntersectsWith(PhysicsComponent* Other);

	sf::Vector2f GetOverlapVector(PhysicsComponent* Other);
};