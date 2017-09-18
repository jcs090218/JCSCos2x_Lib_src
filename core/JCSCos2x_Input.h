#ifndef __JCSCOS2X_INPUT_H__
/**
 * $File: JCSCos2x_Input.h $
 * $Date: 2016-11-17 21:00:54 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_INPUT_H__


#include "cocos2d.h"

typedef cocos2d::EventKeyboard::KeyCode JCSCos2x_KeyCode;

namespace JCSCos2x
{

	/**
	Hanlde input.
	*/
	class JCSCos2x_Input
	{
	private:
		std::unordered_map<JCSCos2x_KeyCode, bool> m_keysPressedThisFrame;
		std::unordered_map<JCSCos2x_KeyCode, bool> m_keysReleasedThisFrame;
		std::unordered_map<JCSCos2x_KeyCode, bool> m_keysDown;

        bool m_mouseDownThisFrame = false;
        bool m_mouseIsDown = false;
        bool m_mouseUpThisFrame = false;
        cocos2d::Vec2 m_mousePosition = cocos2d::Vec2::ZERO;

	public:
		JCSCos2x_Input();
		virtual ~JCSCos2x_Input();

		// NOTE(jenchieh): this might be the bad design, 
		// but since we scene are not going to expand more 
		// and more, so i think with this is okay.

        /* Check whether the given key was pressed this frame. */
		bool GetKeyDown(JCSCos2x_KeyCode keyCode);
        /* Check whether the given key is pressed. */
		bool GetKeyUp(JCSCos2x_KeyCode keyCode);
        /* Check whether the given key was released this frame. */
		bool GetKey(JCSCos2x_KeyCode keyCode);

        /* Check whether the mouse was pressed this frame. */
        bool GetMouseButtonDown();
        /* Check whether the mouse is held down. */
        bool GetMouseButton();
        /* Check whether the mouse was released this frame. */
        bool GetMouseButtonUp();

        /* Clean up the key code list. */
		void update(void);

        /*  */
		void KeysPressedThisFrame(JCSCos2x_KeyCode keyID, bool act);
        /*  */
		void KeysReleasedThisFrame(JCSCos2x_KeyCode keyID, bool act);
        /*  */
		void KeyDownThisFrame(JCSCos2x_KeyCode keyID, bool act);

		// setter
        void SetMouseDownThisFrame(const bool val) { this->m_mouseDownThisFrame = val; }
        void SetMouseIsDown(const bool val) { this->m_mouseIsDown = val; }
        void SetMouseUpThisFrame(const bool val) { this->m_mouseUpThisFrame = val; }
        void SetMousePosition(const cocos2d::Vec2 val) 
        { 
            this->m_mousePosition.x = val.x; 
            this->m_mousePosition.y = val.y;
        }

		// getter
        cocos2d::Vec2 GetMousePosition() const { return this->m_mousePosition; }
        /**
        @brief Position that are in the node space.
        @param node space u want to pass in.
        */
        cocos2d::Vec2 GetMousePositionInNodeSpace(const Node* node) const;

	};
}

typedef JCSCos2x::JCSCos2x_Input JCSCos2x_Input;

#endif // __JCSCOS2X_INPUT_H__
