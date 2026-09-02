#pragma once
#include "Framework/GameObject.h"



class PlayerController : public STR_FALL::GameObject
{
public:
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;
	void Update(float dt) override;

};