/**
 * $File: JCSCos2x_GameObject.cpp $
 * $Date: 2016-11-24 18:13:54 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{

    JCSCos2x_GameObject::JCSCos2x_GameObject()
    {
        
    }

    JCSCos2x_GameObject::~JCSCos2x_GameObject()
    {
        SafeDeleteObject(m_pJCSCos2xAnimator);
    }

    bool JCSCos2x_GameObject::Initialize(void)
    {
        this->m_pSprite = cocos2d::Sprite::create();
        if (!m_pSprite)
        {
            JCS_Debug(L"Failed to create sprite in Cocos2d-x framework...");

            return false;
        }

        // create the animator for use.
        m_pJCSCos2xAnimator = new JCSCos2x_Animator(this);
        if (!m_pJCSCos2xAnimator)
        {
            JCS_Debug(L"Failed to create JCS Animator...");

            return false;
        }

        // init success
        return true;
    }

    void JCSCos2x_GameObject::DoAnimation(
        const std::string baseName,
        const int32 frameCount,
        const float32 delayPerUnit,
        const int32 loop /*= -1*/,
        const bool restoreOriginFrame /*= true*/,
        const int32 firstFrameIndex /*= 0*/)
    {
        this->DoAnimation(
            m_filePath, 
            baseName, 
            frameCount, 
            m_extension,
            delayPerUnit, 
            loop, 
            restoreOriginFrame, 
            firstFrameIndex);
    }

    void JCSCos2x_GameObject::DoAnimation(
        const std::string filePath,
        const std::string baseName,
        const int32 frameCount,
        const std::string ext,
        const float32 delayPerUnit,
        const int32 loop /*= -1*/,
        const bool restoreOriginFrame /*= true*/, 
        const int32 firstFrameIndex /*= 0*/)
    {
        // if the animation are the same return it.
        if (m_filePath == filePath && 
            m_baseName == baseName &&
            m_extension == ext && 
            m_delayPerUnit == delayPerUnit)
            return;

        SetFilePath(filePath);
        SetBaseName(baseName);
        SetExtension(ext);
        SetDelayPerUnit(delayPerUnit);

        // stop the current animation.
        m_pSprite->stopAction(this->GetAnimAction());

        // create the newer animation instnce.
        this->m_pAnimation = cocos2d::Animation::create();

        // gain all the animation.
        for (int32 index = firstFrameIndex;
            index < frameCount;
            ++index)
        {
            const std::string fullPath
                = filePath
                + baseName
                + std::to_string(index)
                + ext;

            // add the frame to sprite.
            m_pAnimation->addSpriteFrameWithFile(fullPath);
        }

        // some animation setting
        this->m_pAnimation->setDelayPerUnit(delayPerUnit);
        this->m_pAnimation->setRestoreOriginalFrame(restoreOriginFrame);
        this->m_pAnimation->setLoops(loop);                  //-1无限循环

        // conver animation to animate, so we can run the action.
        m_pAnimate = cocos2d::Animate::create(m_pAnimation);

        // add action to sprite and assign the animation/animate action.
        m_pAnimAction = m_pSprite->runAction(m_pAnimate);
    }

}
