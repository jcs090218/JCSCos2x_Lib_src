/**
 * $File: JCSCos2x_Input.cpp $
 * $Date: 2016-11-17 21:00:56 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{

	JCSCos2x_Input::JCSCos2x_Input()
		: m_keysPressedThisFrame()
		, m_keysReleasedThisFrame()
		, m_keysDown()
	{

	}

	JCSCos2x_Input::~JCSCos2x_Input()
	{

	}

	void JCSCos2x_Input::update(void)
	{
        // reset mouse states
        m_mouseDownThisFrame = false;
        m_mouseUpThisFrame = false;

		// clear everything back to false.
		for (auto it = m_keysPressedThisFrame.begin(); it != m_keysPressedThisFrame.end(); ++it)
			m_keysPressedThisFrame[it->first] = false;

		for (auto it = m_keysReleasedThisFrame.begin(); it != m_keysReleasedThisFrame.end(); ++it)
			m_keysReleasedThisFrame[it->first] = false;
	}

	bool JCSCos2x_Input::GetKeyDown(JCSCos2x_KeyCode keyCode)
	{
		auto it = m_keysPressedThisFrame.find(keyCode);
		if (it != m_keysPressedThisFrame.end() && !GetKeyUp(keyCode))
		{
			// Found the key
			return it->second;
		}

		return false;
	}

	bool JCSCos2x_Input::GetKeyUp(JCSCos2x_KeyCode keyCode)
	{
		auto it = m_keysReleasedThisFrame.find(keyCode);
		if (it != m_keysReleasedThisFrame.end())
		{
			// Found the key
			return it->second;
		}

		return false;
	}

	bool JCSCos2x_Input::GetKey(JCSCos2x_KeyCode keyCode)
	{
		auto it = m_keysDown.find(keyCode);
		if (it != m_keysDown.end())
		{
			// Found the key
			return it->second;
		}

		return false;
	}

	void JCSCos2x_Input::KeysPressedThisFrame(JCSCos2x_KeyCode keyID, bool act)
	{
		// if already is down do nothing.
		if (GetKey(keyID))
			return;

		// Here we are treating _keyMap as an associative array.
		// if keyID doesn't already exist in _keyMap, it will get added
		m_keysPressedThisFrame[keyID] = act;
	}

	void JCSCos2x_Input::KeysReleasedThisFrame(JCSCos2x_KeyCode keyID, bool act)
	{
		m_keysReleasedThisFrame[keyID] = act;
	}

	void JCSCos2x_Input::KeyDownThisFrame(JCSCos2x_KeyCode keyID, bool act)
	{
		m_keysDown[keyID] = act;
	}

    bool JCSCos2x_Input::GetMouseButtonDown()
    {
        return m_mouseDownThisFrame;
    }

    bool JCSCos2x_Input::GetMouseButton()
    {
        return m_mouseIsDown;
    }

    bool JCSCos2x_Input::GetMouseButtonUp()
    {
        return m_mouseUpThisFrame;
    }

    cocos2d::Vec2 JCSCos2x_Input::GetMousePositionInNodeSpace(const Node* node) const
    {
        Vec2 mousePosition = GetMousePosition();
        Vec2 worldMousePos = node->convertToNodeSpace(mousePosition);

        worldMousePos.y = -worldMousePos.y;

        return worldMousePos;
    }
}
