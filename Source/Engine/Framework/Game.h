#pragma once


namespace STR_FALL
{
	class Scene;

	class Game
	{
	protected:
		Scene* m_scene = nullptr;

	public:
		Game() = default;
		Game(Scene* scene) : m_scene(scene) {}

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {}
		virtual void Update() = 0;
		virtual void Draw() = 0;

		void SetScene(Scene* scene) { m_scene = scene; }
	};
}