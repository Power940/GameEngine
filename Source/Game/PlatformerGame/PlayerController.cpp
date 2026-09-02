#include "PlayerController.h"

using namespace STR_FALL;

void PlayerController::Start()
{
	GameObject::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);

	m_rendererComponent = GetComponent<RendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{

}