#pragma once

#include <vector>

#include "Structs.h"

namespace STR_FALL
{
	class Input
	{
	private:
		int m_numKeys;

		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePos = Vector2();
	public:
		bool Initialize();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates.at(key); }
		bool GetKeyPrevDown(int key) const { return m_prevKeyStates.at(key); }
		bool GetKeyPressed(int key) const { return !m_prevKeyStates.at(key) && m_keyStates.at(key); }
		bool GetKeyReleased(int key) const { return m_prevKeyStates.at(key) && !m_keyStates.at(key); }

		Vector2 GetMouseDown() const { return m_mousePos; }

		Vector2 GetMousePos() const { return m_mousePos; }
	};
}