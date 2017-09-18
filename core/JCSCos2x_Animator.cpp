/**
 * $File: JCSCos2x_Animator.cpp $
 * $Date: 2016-11-24 20:51:10 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{

    JCSCos2x_Animator::JCSCos2x_Animator(JCSCos2x_GameObject* gameObject)
        : m_pGameObject(gameObject)
        , m_filePath("")
        , m_extension(".png")
    {

    }

    JCSCos2x_Animator::~JCSCos2x_Animator()
    {

    }

    void JCSCos2x_Animator::DoAnimationWithFile(
        const std::string baseName,
        const int32 frameCount,
        const int32 delayPerUnit,
        const int32 loop /*= -1*/,
        const bool restoreOriginFrame /*= true*/,
        const int32 startFrameIndex /*= 0*/)
    {
        cocos2d::Sprite* pSprite = this->m_pGameObject->GetSprite();
        cocos2d::Animation* pAnimation = this->m_pGameObject->GetAnimation();
        cocos2d::Animate* pAnimate = this->m_pGameObject->GetAnimate();
        cocos2d::Action* pAnimAction = this->m_pGameObject->GetAnimAction();

        // stop the current animation.
        pSprite->stopAction(pAnimAction);

        // create the newer animation instnce.
        pAnimation = cocos2d::Animation::create();

        // gain all the animation.
        for (int32 index = startFrameIndex;
            index < frameCount;
            ++index)
        {
            const std::string fullPath
                = m_filePath
                + baseName
                + std::to_string(index)
                + m_extension;

            // NOTE(jenchieh): in c++ 11 try/catch block cost 
            // performance, disable it if is in release mode.
#ifdef _DEBUG
            try 
            {
#endif
                // add the frame to sprite.
                pAnimation->addSpriteFrameWithFile(fullPath);
#ifdef _DEBUG
            }
            catch (...)
            {
                throw JCS_Debug(L"Failed to load sprite with loading...");
            }
#endif
        }

        // some animation setting
        pAnimation->setDelayPerUnit(delayPerUnit);
        pAnimation->setRestoreOriginalFrame(restoreOriginFrame);
        pAnimation->setLoops(loop);                  //-1无限循环

        // convet animation to animate, so we can run the action.
        pAnimate = cocos2d::Animate::create(pAnimation);

        // add action to sprite and assign the animation/animate action.
        pAnimAction = pSprite->runAction(pAnimate);

        this->m_pGameObject->SetSprite(pSprite);
        this->m_pGameObject->SetAnimAction(pAnimAction);
        this->m_pGameObject->SetAnimate(pAnimate);
        this->m_pGameObject->SetAnimation(pAnimation);
    }

}
