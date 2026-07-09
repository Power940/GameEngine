#pragma once

#include <vector>

#include "Structs.h"

namespace STR_FALL
{
	class Input
	{
	private:
		int m_numKeys = 0;

		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePos = Vector2();
	public:
		enum MouseButton
		{
			Left = 0b0001,
			Middle = 0b0010,
			Right = 0b0100
		};

		bool Initialize();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates.at(key); }
		bool GetKeyPrevDown(int key) const { return m_prevKeyStates.at(key); }
		bool GetKeyPressed(int key) const { return !m_prevKeyStates.at(key) && m_keyStates.at(key); }
		bool GetKeyReleased(int key) const { return m_prevKeyStates.at(key) && !m_keyStates.at(key); }

		bool GetMouseDown(MouseButton button) const { return m_buttonStates & button; }
		bool GetMousePrevDown(MouseButton button) const { return m_prevButtonStates & button; }
		bool GetMousePressed(MouseButton button) const { return !(m_prevButtonStates & button) && (m_buttonStates & button); }
		bool GetMouseReleased(MouseButton button) const { return (m_prevButtonStates & button) && !(m_buttonStates & button); }

		Vector2 GetMousePos() const { return m_mousePos; }
	};
}