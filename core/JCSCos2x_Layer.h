#ifndef __JCSCOS2X_SCENE_H__
/**
 * $File: JCSCos2x_Layer.h $
 * $Date: 2016-11-17 20:37:54 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_SCENE_H__


#include "cocos2d.h"

#include <stack>
#include <amp.h>

namespace JCSCos2x
{
	class JCSCos2x_Input;
	class JCSCos2x_SoundPlayer;

	/**
	Custom scene overide the default cocos2d's layer.
	*/
	class JCSCos2x_Layer
		: public cocos2d::Layer
	{
    public:
        // how fast the layer follow the target.
        static float32 s_followFriction;

		// check if run the start function.
		bool m_runStart = false;

	private:
		JCSCos2x_Input* m_pInput = nullptr;
		JCSCos2x_SoundPlayer* m_pSoundManager = nullptr;

        // camera.
        cocos2d::Sprite* m_pCamera = nullptr;     // camera will follow this sprite.
        cocos2d::Follow* m_pCameraFollow = nullptr;     // layer, we treat this as camera.

        // camera target sprite will follow this + friction/offset.
        cocos2d::Node* m_pCameraTarget = nullptr;
        // the actual position each layer targeting.
        cocos2d::Vec2 m_cameraTargetPositionParallax = Vec2::ZERO;
        Vec2 m_lasFrametCameraTargetPosition = Vec2::ZERO;

        // offset friction layer toward.
        float32 m_layerFriction = 0.0f;

        // check if this layer part of the game/HUD.
        bool m_isGameLayer = true;

        // set the min/max distance the layer can move.
        float32 m_minCamX = -std::numeric_limits<float32>::infinity();
        float32 m_maxCamX = std::numeric_limits<float32>::infinity();
        float32 m_minCamY = -std::numeric_limits<float32>::infinity();
        float32 m_maxCamY = std::numeric_limits<float32>::infinity();

#ifdef _DEBUG
    protected:
        cocos2d::Sprite* m_pOtherSprite = nullptr;
        bool m_controlSprite = true;
        cocos2d::Vec2 m_recordPosition = cocos2d::Vec2::ZERO;

        float32 m_slowFixSpeed = 10;
        float32 m_fastFixSpeed = 100;

        // velocity for control sprite
        cocos2d::Vec2 m_otherSpriteVelocity = cocos2d::Vec2::ZERO;

        std::stack<cocos2d::Vec2> m_undoPos;
#endif

	public:
		static cocos2d::Scene* createScene();

		virtual ~JCSCos2x_Layer();

		// initialize the scene here...
		virtual bool init() override;

		/**
		This will call every frame.

		@param deltaTime : delta time calculate by game timer
		engine from cocos2dx.
		*/
		virtual void update(float32 deltaTime) override;

		/*
		Self layer exit application function call back.
		*/
		void exit(void);

		// smart pointer handle for cocos2dx framework
		CREATE_FUNC(JCSCos2x_Layer);

		// a selector callback
		virtual void menuCloseCallback(cocos2d::Ref* pSender);

        /**
        @brief Create the camera for the scene.

        @source1: http://www.mets-blog.com/cocos2d-x-platformer-tutorial-part-5-camera/
        @source2: http://www.cnblogs.com/wantnon/p/4158135.html
        @source3: http://discuss.cocos2d-x.org/t/how-to-use-new-camera-system/18644/3

        @param visible size / screen size / window size
        @param screen origin
        */
        void Create3DCamera(cocos2d::Vec3 pos, bool follow = false);

        /**
        @brief Create the camera for the scene.

        @source1: http://www.mets-blog.com/cocos2d-x-platformer-tutorial-part-5-camera/
        @source2: http://www.cnblogs.com/wantnon/p/4158135.html
        @source3: http://discuss.cocos2d-x.org/t/how-to-use-new-camera-system/18644/3

        @param screen origin
        */
        void Create2DCamera(bool follow = true);


		/** setter **/
		void SetCameraMinX(const float32 val, bool over = true);
		void SetCameraMaxX(const float32 val, bool over = true);
		void SetCameraMinY(const float32 val, bool over = true);
		void SetCameraMaxY(const float32 val, bool over = true);

        void SetCameraTargetTarget(cocos2d::Node* const node, bool over = true);

        /**
        * @brief How fast the layer move. 
        *     slow <-----> fast
        *    -1.0f <-----> 1.0f
        * @param friction of the layer. (default: 0)
        */
        void SetLayerFriction(const float32 val) 
        { 
            this->m_layerFriction = clampf(val, -1.0f, 1.0f);
        }

        void SetIsGameLayer(const bool val) { this->m_isGameLayer = val; }

#ifdef _DEBUG
        /**
        @brief Do the undo key algorithm
        */
        cocos2d::Vec2 DoUndo(const cocos2d::Vec2 currentPos);

        /* fast control function */
        void FastFixControl(const float32 deltaTime);
        /* slow control function */
        void SlowFixControl(const float32 deltaTime);

        void SetControlSprite(const bool val) { this->m_controlSprite = val; }
        void SetSlowFixSpeed(const float32 val) { this->m_slowFixSpeed = val; }
        void SetFastFixSpeed(const float32 val) { this->m_fastFixSpeed = val; }
#endif

		/** getter **/
		JCSCos2x_Input* GetJCSInput() const { return this->m_pInput; }
		JCSCos2x_SoundPlayer* GetSoundPlayer() const { return this->m_pSoundManager; }
        cocos2d::Sprite* GetCamera() const { return this->m_pCamera; }
        cocos2d::Follow* GetCameraFollow() const { return this->m_pCameraFollow; }
        cocos2d::Node* GetCameraTarget() { return this->m_pCameraTarget; }

        const float32 GetCameraMinX() const { return this->m_minCamX; }
        const float32 GetCameraMaxX() const { return this->m_maxCamX; }
        const float32 GetCameraMinY() const { return this->m_minCamY; }
        const float32 GetCameraMaxY() const { return this->m_maxCamY; }
		
		float32 GetLayerFriction() const { return this->m_layerFriction; }

		bool GetIsGameLayer() const { return this->m_isGameLayer; }

	protected:
		// MPTE(jenchieh): provide down function call.

		/**
		Initialize the scene.

		@return true: initialize the scene succeeded.
		@return false: failed to initialize the scene.
		*/
		virtual bool jcscos_init(void) { return true; }

		/**
		Initialize the scene run once after jcscos_init function.
		NOTE(jenchieh): this cost performance.
		*/
		virtual void jcscos_start(void) { }

		/**
		@param delta time provide by cocos2d-x time engine.
		*/
		virtual void jcscos_update(float32 deltaTime) { }

		/**
		Exit out the application callback.
		*/
		virtual void jcscos_exit(void) { }

        /**
        @brief In order to make me easier to make the sprite
        into the position i want.
        @param Sprite pointer
        */
        void SetSpriteControl(Sprite* sprite);

	private:
		/**
		Create event listener like input, sound, etc.
		*/
		void CreateEventListener(void);

		/**
		Handle on key press event call back.

		@param keycode that preseed.
		@param event type.
		*/
		void OnKeyPress(EventKeyboard::KeyCode keyPressed, Event* evt);
		/**
		Handle on key release event call back.

		@param keycode that preseed.
		@param event type.
		*/
		void OnKeyRelease(EventKeyboard::KeyCode keyReleased, Event* evt);

        /**
        @brief update the camera.
        @param delta time
        */
        void Update2DCamera(float32 deltaTime);

        /**
        @brief When the touch start
        @param touch part
        @param event type.
        */
        bool OnTouchBegan(Touch* touch, Event* evt);
        /**
        @brief When the touch start
        @param touch part
        @param event type.
        */
        void OnTouchEnded(Touch* touch, Event* evt);
        /**
        @brief When the touch start
        @param touch part
        @param event type.
        */
        void OnTouchMoved(Touch* touch, Event* evt);
        /**
        @brief When the touch start
        @param touch part
        @param event type.
        */
        void OnTouchCancelled(Touch* touch, Event* evt);

        /* use a sprite to find out the position. */
        void PositionSpriteControl(const float32 deltaTime);

	};
}

#endif // __JCSCOS2X_SCENE_H__
