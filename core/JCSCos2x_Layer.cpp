/**
 * $File: JCSCos2x_Layer.cpp $
 * $Date: 2016-11-17 20:38:04 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{
    float32 JCSCos2x_Layer::s_followFriction = 0.01f;

	Scene* JCSCos2x_Layer::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::create();

		// 'layer' is an autorelease object
		auto layer = JCSCos2x_Layer::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	JCSCos2x_Layer::~JCSCos2x_Layer()
	{
		exit();
	}

	// on "init" you need to initialize your instance
	bool JCSCos2x_Layer::init()
	{
		// check super init function.
		if (!Layer::init())
			return false;

		// update the function assign
		this->scheduleUpdate();

		// create event listener
		this->CreateEventListener();

        // create important instances and managers.
		m_pInput = new JCSCos2x_Input;
		m_pSoundManager = JCSCos2x_SoundPlayer::GetInstance();

		// finally return the init layer.
		if (!jcscos_init())
			return false;

        // NOTE(jenchieh): every layer need a camera target, 
        // in order to move the whole layer.
        // create 2d camera as default.
        if (m_isGameLayer)
        {
            this->Create2DCamera();
        }

		// reset start trigger.
		m_runStart = false;

		return true;
	}

	// This will call every frame.
	void JCSCos2x_Layer::update(float32 deltaTime)
	{
#ifdef _DEBUG
        this->PositionSpriteControl(deltaTime);

        // toggle camera sprite.
        if (GetJCSInput()->GetKeyDown(JCSCos2x_KeyCode::KEY_L))
        {
            if (GetCamera() != nullptr)
                GetCamera()->setVisible(!GetCamera()->isVisible());
        }
#endif

		// only run once.
		if (!this->m_runStart)
		{
			// run only once.
			this->jcscos_start();
			this->m_runStart = true;
		}

		// call self update.
		this->jcscos_update(deltaTime);

		// update the key frame.
        this->m_pInput->update();

        if (m_isGameLayer)
        {
            this->Update2DCamera(deltaTime);
        }
	}

	void JCSCos2x_Layer::exit(void)
	{
		SafeDeleteObject(m_pInput);
		JCSCos2x_SoundPlayer::DestroyInstance();

		this->jcscos_exit();
	}

	void JCSCos2x_Layer::CreateEventListener(void)
	{
        // -------------------- Keyboard Event ----------------------//
		auto eventListener = EventListenerKeyboard::create();

		auto boundKeyPressListener = CC_CALLBACK_2(JCSCos2x_Layer::OnKeyPress, this);
		auto boundKeyReleaseListener = CC_CALLBACK_2(JCSCos2x_Layer::OnKeyRelease, this);

		eventListener->onKeyPressed = boundKeyPressListener;
		eventListener->onKeyReleased = boundKeyReleaseListener;

		// dispatch the event listener.
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


        // -------------------- Touch Event ----------------------//
        auto touchListener = EventListenerTouchOneByOne::create();

        touchListener->onTouchBegan = CC_CALLBACK_2(JCSCos2x_Layer::OnTouchBegan, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(JCSCos2x_Layer::OnTouchEnded, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(JCSCos2x_Layer::OnTouchMoved, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(JCSCos2x_Layer::OnTouchCancelled, this);

        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	}

	void JCSCos2x_Layer::menuCloseCallback(Ref* pSender)
	{
		this->exit();

		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

		/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

		//EventCustom customEndEvent("game_scene_close_event");
		//_eventDispatcher->dispatchEvent(&customEndEvent);


	}

	void JCSCos2x_Layer::OnKeyPress(EventKeyboard::KeyCode keyCode, Event* evt)
	{
		m_pInput->KeysPressedThisFrame(keyCode, true);
		m_pInput->KeyDownThisFrame(keyCode, true);
	}

	void JCSCos2x_Layer::OnKeyRelease(EventKeyboard::KeyCode keyCode, Event* evt)
	{
		m_pInput->KeysReleasedThisFrame(keyCode, true);
		m_pInput->KeyDownThisFrame(keyCode, false);
	}

    // touch moved
    bool JCSCos2x_Layer::OnTouchBegan(Touch* touch, Event* evt)
    {
        m_pInput->SetMousePosition(touch->getLocationInView());

        // You touched here.
        m_pInput->SetMouseDownThisFrame(true);
        m_pInput->SetMouseIsDown(true);

        return true;
    }

    // touch ended
    void JCSCos2x_Layer::OnTouchEnded(Touch* touch, Event* evt)
    {
        m_pInput->SetMousePosition(touch->getLocationInView());
        m_pInput->SetMouseUpThisFrame(true);
        m_pInput->SetMouseIsDown(false);
    }

    // touch moved
    void JCSCos2x_Layer::OnTouchMoved(Touch* touch, Event* evt)
    {
        m_pInput->SetMousePosition(touch->getLocationInView());
    }

    // touch cancelled
    void JCSCos2x_Layer::OnTouchCancelled(Touch* touch, Event* evt)
    {
        m_pInput->SetMousePosition(touch->getLocationInView());

        m_pInput->SetMouseUpThisFrame(true);
        m_pInput->SetMouseIsDown(false);
    }

    void JCSCos2x_Layer::Create3DCamera(cocos2d::Vec3 pos, bool follow /*= false*/)
    {
        // Scene Settings.
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // create camera
        {
            //auto camTargetPos = Vec3(pos);

            //m_pCamera = cocos2d::Camera::createPerspective(
            //    60,         // field of view
            //    (float)visibleSize.width / visibleSize.height,      // aspect ratio
            //    1.0f,       // near plane
            //    1000);      // far plane

            //m_pCamera->setCameraFlag(CameraFlag::USER2);

            //// the calling order matters, we should first call 
            //// setPosition3D, then call lookAt.
            //m_pCamera->setPosition3D(camTargetPos + Vec3(0, 0, 0));
            //m_pCamera->lookAt(camTargetPos, Vec3(0.0f, 1.0f, 0.0f));

            //this->addChild(m_pCamera);
        }

        if (follow)
        {
            // TODO(jenchieh): 3d camera follow algorithm 
            // design here...
        }
    }

    void JCSCos2x_Layer::Create2DCamera(bool follow /*= true*/)
    {
        // NOTE(jenchieh): check if camera has been created.
        if (m_pCamera)
            return;

        // Scene Settings.
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // first create the camera target image.
#if _DEBUG
        // debug camera sprite.
        m_pCamera = cocos2d::Sprite::create("vcam_flash.png");
        m_pCamera->setOpacity(200.0f);
#else
        // if release, create the empty sprite.
        m_pCamera = cocos2d::Sprite::create();
#endif
        m_pCamera->setPosition(0, 0);
        m_pCamera->retain();

        // add all needed game object here...
        this->addChild(m_pCamera);

        // do the following?
        if (follow)
        {
            m_pCameraFollow = Follow::create(m_pCamera, Rect::ZERO);
            m_pCameraFollow->retain();

            // make layer follow the camera target, so 
            // now the camera target are the camera for 
            // 2d game.
            this->runAction(m_pCameraFollow);
        }
    }

    void JCSCos2x_Layer::Update2DCamera(float32 deltaTime)
    {
        // check 2d camera.
        if (!GetCamera())
            return;

        // NOTE(jenchieh): first follow the target with friction.
        if (GetCameraTarget())
        {
            // make camera/layer target offset a bit, in order to 
            // create the parallax effect.
            {
                if (m_layerFriction != 0)
                {
                    // NOTE(jenchieh): 
                    Vec2 currentCameraPos = GetCameraTarget()->getPosition();

                    // get the delta position = velocity.
                    Vec2 deltaCameraPos = m_lasFrametCameraTargetPosition - currentCameraPos;
                
                    // update the camera target position by friction.
                    m_cameraTargetPositionParallax += deltaCameraPos * m_layerFriction;
                }
            }

            // make the layer follow the camera target.
            {
                Vec2 newPos = GetCamera()->getPosition();

                // follow the camera target's target.
                newPos +=
                    ((m_pCameraTarget->getPosition() - m_cameraTargetPositionParallax) - newPos)
                    / JCSCos2x_Layer::s_followFriction
                    * deltaTime;

                // apply new position.
                GetCamera()->setPosition(newPos);
            }
        }

        // do min/max.
        {
            Vec2 cameraPos = GetCamera()->getPosition();

            // check x min/max
            if (cameraPos.x < m_minCamX)
                cameraPos.x = m_minCamX;
            else if (cameraPos.x > m_maxCamX)
                cameraPos.x = m_maxCamX;

            // check y min/max
            if (cameraPos.y < m_minCamY)
                cameraPos.y = m_minCamY;
            else if (cameraPos.y > m_maxCamY)
                cameraPos.y = m_maxCamY;

            // set the camera position, so it won't go out of scope.
            GetCamera()->setPosition(cameraPos);
        }

        if (GetCameraTarget())
        {
            // set the last frame camera position.
            m_lasFrametCameraTargetPosition = GetCameraTarget()->getPosition();
        }
    }

    void JCSCos2x_Layer::SetCameraTargetTarget(cocos2d::Node* const node, bool over /*= true*/)
    {
        this->m_pCameraTarget = node;

        // do over?
        if (!over)
            return;

        // get all the children in the scene.
        Vector<Node*> layers = this->getScene()->getChildren();

        for (cocos2d::Node* pNode : layers)
        {
            JCSCos2x_Layer* pJCSLayer = dynamic_cast<JCSCos2x_Layer*>(pNode);

            // if cast failed
            if (!pJCSLayer)
                continue;

			// if not game layer, skip it.
			if (!pJCSLayer->GetIsGameLayer())
				continue;

            // set over to false to prevent function 
            // call stack overflow.
            pJCSLayer->SetCameraTargetTarget(node, false);
        }
    }

	void JCSCos2x_Layer::SetCameraMinX(const float32 val, bool over /*= true*/)
	{
        // if not game layer, skip it.
        if (GetIsGameLayer())
        {
            if (GetLayerFriction() != 0)
                this->m_minCamX = (val + (val * GetLayerFriction()));
            else
                this->m_minCamX = val;
        }

		// do over?
		if (!over)
			return;

		// get all the children in the scene.
		Vector<Node*> layers = this->getScene()->getChildren();

		for (cocos2d::Node* pNode : layers)
		{
			JCSCos2x_Layer* pJCSLayer = dynamic_cast<JCSCos2x_Layer*>(pNode);

			// if cast failed
			if (!pJCSLayer)
				continue;

			// set over to false to prevent function 
			// call stack overflow.
			pJCSLayer->SetCameraMinX(val, false);
		}
	}
	void JCSCos2x_Layer::SetCameraMaxX(const float32 val, bool over /*= true*/)
	{
        // if not game layer, skip it.
        if (GetIsGameLayer())
        {
            if (GetLayerFriction() != 0)
                this->m_maxCamX = (val + (val * GetLayerFriction()));
            else
                this->m_maxCamX = val;
        }

		// do over?
		if (!over)
			return;

		// get all the children in the scene.
		Vector<Node*> layers = this->getScene()->getChildren();

		for (cocos2d::Node* pNode : layers)
		{
			JCSCos2x_Layer* pJCSLayer = dynamic_cast<JCSCos2x_Layer*>(pNode);

			// if cast failed
			if (!pJCSLayer)
				continue;

			// set over to false to prevent function 
			// call stack overflow.
			pJCSLayer->SetCameraMaxX(val, false);
		}
	}
	void JCSCos2x_Layer::SetCameraMinY(const float32 val, bool over /*= true*/)
	{
        // if not game layer, skip it.
        if (GetIsGameLayer())
        {
            if (GetLayerFriction() != 0)
                this->m_minCamY = (val + (val * GetLayerFriction()));
            else
                this->m_minCamY = val;
        }

		// do over?
		if (!over)
			return;

		// get all the children in the scene.
		Vector<Node*> layers = this->getScene()->getChildren();

		for (cocos2d::Node* pNode : layers)
		{
			JCSCos2x_Layer* pJCSLayer = dynamic_cast<JCSCos2x_Layer*>(pNode);

			// if cast failed
			if (!pJCSLayer)
				continue;

			// set over to false to prevent function 
			// call stack overflow.
			pJCSLayer->SetCameraMinY(val, false);
		}
	}
	void JCSCos2x_Layer::SetCameraMaxY(const float32 val, bool over /*= true*/)
	{
        // if not game layer, skip it.
        if (GetIsGameLayer())
        {
            if (GetLayerFriction() != 0)
                this->m_maxCamY = (val + (val * GetLayerFriction()));
            else
                this->m_maxCamY = val;
        }

		// do over?
		if (!over)
			return;

		// get all the children in the scene.
		Vector<Node*> layers = this->getScene()->getChildren();

		for (cocos2d::Node* pNode : layers)
		{
			JCSCos2x_Layer* pJCSLayer = dynamic_cast<JCSCos2x_Layer*>(pNode);

			// if cast failed
			if (!pJCSLayer)
				continue;

			// if not game layer, skip it.
			if (!pJCSLayer->GetIsGameLayer())
				continue;

			// set over to false to prevent function 
			// call stack overflow.
			pJCSLayer->SetCameraMaxY(val, false);
		}
	}

#ifdef _DEBUG
    void JCSCos2x_Layer::PositionSpriteControl(const float32 deltaTime)
    {
        // check if null.
        if (!m_pOtherSprite)
            return;

        if (GetJCSInput()->GetKeyDown(JCSCos2x_KeyCode::KEY_T))
        {
            // reverse the trigger.
            SetControlSprite(!m_controlSprite);
        }

        if (!m_controlSprite)
            return;

        // get the last frame position
        Vec2 beforePosition = m_pOtherSprite->getPosition();

        // reset velocity.
        m_otherSpriteVelocity = cocos2d::Vec2::ZERO;

        // do control
        {
            FastFixControl(deltaTime);
            SlowFixControl(deltaTime);
        }

        Vec2 newPos = m_pOtherSprite->getPosition();

        newPos.x += m_otherSpriteVelocity.x * deltaTime;
        newPos.y += m_otherSpriteVelocity.y * deltaTime;

        // apply new position.
        m_pOtherSprite->setPosition(newPos);

        if (newPos == beforePosition &&
            m_recordPosition != beforePosition && 
            m_otherSpriteVelocity.x == 0 &&
            m_otherSpriteVelocity.y == 0)
        {
            m_undoPos.push(beforePosition);

            // record down the position
            m_recordPosition = beforePosition;
        }

        if (GetJCSInput()->GetKeyDown(JCSCos2x_KeyCode::KEY_P))
        {
            // print out the position in order to get the test result.
            JCS_Print(L"\n---------------------------------------------\n");
            JCS_Print1(L"Position X: %f\n", m_pOtherSprite->getPosition().x);
            JCS_Print1(L"Position Y: %f\n", m_pOtherSprite->getPosition().y);
            JCS_Print(L"---------------------------------------------\n");
        }

        // make udo
        if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_CTRL))
        {
            if (GetJCSInput()->GetKeyDown(JCSCos2x_KeyCode::KEY_Z))
            {
                if (m_undoPos.size() != 0)
                {
                    Vec2 currentPos = m_pOtherSprite->getPosition();

                    Vec2 tempUndoPos = DoUndo(currentPos);

                    if (m_undoPos.size() != 0)
                    {
                        // update the record position
                        m_recordPosition = tempUndoPos;
                    }
                    else
                    {
                        m_undoPos.push(tempUndoPos);
                    }
                }
            }
        }

    }
#endif

    void JCSCos2x_Layer::SetSpriteControl(Sprite* sprite)
    {
#ifdef _DEBUG
        // get the sprite pointer.
        m_pOtherSprite = sprite;
#endif
    }

#ifdef _DEBUG
    cocos2d::Vec2 JCSCos2x_Layer::DoUndo(const cocos2d::Vec2 currentPos)
    {
        // top return the element.
        cocos2d::Vec2 tempUndoPos = m_undoPos.top();

        // remove the top element.
        m_undoPos.pop();

        // set to the undo position.
        this->m_pOtherSprite->setPosition(tempUndoPos);

        if (currentPos == tempUndoPos && m_undoPos.size() != 0)
            return DoUndo(currentPos);

        return tempUndoPos;
    }

    void JCSCos2x_Layer::FastFixControl(const float32 deltaTime)
    {
        if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_A))
        {
            m_otherSpriteVelocity.x = -m_fastFixSpeed;
        }
        else if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_D))
        {
            m_otherSpriteVelocity.x = m_fastFixSpeed;
        }

        if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_W))
        {
            m_otherSpriteVelocity.y = m_fastFixSpeed;
        }
        else if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_S))
        {
            m_otherSpriteVelocity.y = -m_fastFixSpeed;
        }
    }

    void JCSCos2x_Layer::SlowFixControl(const float32 deltaTime)
    {
        if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_J))
        {
            m_otherSpriteVelocity.x = -m_slowFixSpeed;
        }
        else if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_L))
        {
            m_otherSpriteVelocity.x = m_slowFixSpeed;
        }

        if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_I))
        {
            m_otherSpriteVelocity.y = m_slowFixSpeed;
        }
        else if (GetJCSInput()->GetKey(JCSCos2x_KeyCode::KEY_K))
        {
            m_otherSpriteVelocity.y = -m_slowFixSpeed;
        }
    }

#endif

}
