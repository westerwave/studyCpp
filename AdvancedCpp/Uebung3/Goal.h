#pragma once
#include "ITile.h"

class Goal : public ITile
{
public:
	Goal();
	~Goal();

	virtual bool isBlocking() override;
	virtual bool isGoal() override;

	virtual void render(std::ostream& stream) override;
};

