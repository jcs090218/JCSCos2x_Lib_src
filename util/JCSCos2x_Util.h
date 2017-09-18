#ifndef __JCSCOS2X_UTIL_H__
/**
 * $File: JCSCos2x_Util.h $
 * $Date: 2016-12-09 21:59:41 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_UTIL_H__

#include <cocos2d.h>

#include <SimpleAudioEngine.h>
#include <AudioEngine.h>

namespace JCSCos2x
{

    /**
    @brief 
    @param layer to add
    @param file path
    @param x position
    @param y position
    @param z render order
    */
    inline cocos2d::Sprite* CreateSpriteInLayer(
        cocos2d::Layer* const layer, 
        const std::string filePath, 
        const float x,
        const float y,
        const int localZOrder = 0)
    {
        auto sprite = cocos2d::Sprite::create(filePath);
        sprite->setPosition(cocos2d::Point(x, y));

        layer->addChild(sprite, localZOrder);

        return sprite;
    }

    /**
    * 
    */
    inline cocos2d::Sprite* CreateAnimationInLayer(
        cocos2d::Layer* const layer, 
        const float x,
        const float y,
        const std::string filePath,
        const std::string baseName,
        const int frameCount,
        const std::string ext, 
        const float delayPerUnit,
        const int loop = -1,
        const bool restoreOriginFrame = true,
        const int firstFrameIndex = 0, 
        const int localZOrder = 0)
    {
        auto sprite = cocos2d::Sprite::create();

        // create the newer animation instnce.
        auto animation = cocos2d::Animation::create();

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
            animation->addSpriteFrameWithFile(fullPath);
        }

        // some animation setting
        animation->setDelayPerUnit(delayPerUnit);
        animation->setRestoreOriginalFrame(restoreOriginFrame);
        animation->setLoops(loop);                  //-1无限循环

        // conver animation to animate, so we can run the action.
        auto animate = cocos2d::Animate::create(animation);

        // add action to sprite and assign the animation/animate action.
        sprite->runAction(animate);

        // set the sprite animation.
        sprite->setPosition(cocos2d::Point(x, y));

        // add sprite to target layer.
        layer->addChild(sprite, localZOrder);

        return sprite;
    }

    /**
    @brief Switch scene with fade effect.
    @param scene type
    @param fade time
    @param color to fade
    */
    template <class T>
    inline cocos2d::Scene* SwitchScene(
        float fadeTime, 
        Color3B color = Color3B(0, 0, 0))       // default to black
    {
        // create the scene
        auto pScene = T::createScene();

        Director::getInstance()->replaceScene(TransitionFade::create(fadeTime, pScene, color));

        return pScene;
    }

    /**
    @brief Switch scene with fade effect.
    @param scene type
    @param fade time
    @param file path
    @param loop the bgm
    @param volume
    @param color to fade
    */
    template <class T>
    inline cocos2d::Scene* SwitchSceneWithBGM(
        float fadeTime, 
        const std::string& filePath,
        bool loop = true,
        float volume = 1.0f,
        Color3B color = Color3B(0, 0, 0))       // default to black
    {
        // play the next bgm.
        JCSCos2x_SoundPlayer::GetInstance()->PlayBGM(filePath, loop, volume, nullptr);

        auto pScene = SwitchScene<T>(fadeTime, color);

        return pScene;
    }
    
    /**
    @brief Switch scene with fade effect.
    @param scene type
    @param fade time
    @param file path
    @param color to fade
    */
    template <class T>
    inline cocos2d::Scene* SwitchSceneWithBGM(
        float fadeTime,
        const std::string& filePath,
        Color3B color = Color3B(0, 0, 0))
    {
        return SwitchSceneWithBGM<T>(fadeTime, filePath, true, 1.0f, color);
    }

}

#endif // __JCSCOS2X_UTIL_H__
