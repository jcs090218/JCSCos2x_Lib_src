#ifndef __JCSCOS2X_GAMEOBJECT_H__
/**
 * $File: JCSCos2x_GameObject.h $
 * $Date: 2016-11-24 18:13:56 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_GAMEOBJECT_H__


#include <cocos2d.h>

#include <string.h>

namespace JCSCos2x
{
    class JCSCos2x_Animator;

    /**
    @class JCSCos2x_GameObject
    @brief General game object that will provide the 3 thing.
        1) Normal Sprite.
        2) Normal Animation.
        3) Animation.
    */
    class JCSCos2x_GameObject
    {
    private:
        // STUDY(jenchieh): never had the problem like this...
        // seems the cocos2d-x have some security layer for transfe-
        // ing the pointer and references.
        JCSCos2x_Animator* m_pJCSCos2xAnimator = nullptr;

        /* Animation & Animator Setting Variables */
        cocos2d::Sprite* m_pSprite = nullptr;
        cocos2d::Animation* m_pAnimation = nullptr;
        cocos2d::Animate* m_pAnimate = nullptr;
        cocos2d::Action* m_pAnimAction = nullptr;
        
        std::string m_filePath = "";
        std::string m_baseName = "";
        std::string m_extension = ".png";       // default as .png file.
        float m_delayPerUnit = -1;

    public:
        explicit JCSCos2x_GameObject();
        virtual ~JCSCos2x_GameObject();


        bool Initialize(void);

        /**
        @brief Switch the current animtion and run the newer animation.

        @param animation base name.
        @param total frame count in the animation.
        @param delay per frame in second.
        @param loop how many times the animation is going to loop.
            -1, loop forever.
            0 means animation is not animated.
            1, animation is executed one time, ...
        @param restoreOriginFrame
        @param firstFrameIndex
        */
        void JCSCos2x_GameObject::DoAnimation(
            const std::string baseName,
            const int32 frameCount,
            const float32 delayPerUnit,
            const int32 loop = -1,
            const bool restoreOriginFrame = true,
            const int32 firstFrameIndex = 0);

        /**
        @brief Switch the current animtion and run the newer animation.

        @param file path
        @param animation base name.
        @param total frame count in the animation.
        @param extension
        @param delay per frame in second.
        @param loop how many times the animation is going to loop.
            -1, loop forever.
            0 means animation is not animated.
            1, animation is executed one time, ...
        @param restoreOriginFrame
        @param firstFrameIndex
        */
        void DoAnimation(
            const std::string filePath,
            const std::string baseName,
            const int32 frameCount,
            const std::string ext,
            const float32 delayPerUnit,
            const int32 loop = -1,
            const bool restoreOriginFrame = true, 
            const int32 firstFrameIndex = 0);

        

        /** setter **/
        void SetSprite(cocos2d::Sprite* val) { this->m_pSprite = val; }
        void SetAnimation(cocos2d::Animation* val) { this->m_pAnimation = val; }
        void SetAnimate(cocos2d::Animate* val) { this->m_pAnimate = val; }
        void SetAnimAction(cocos2d::Action* val) { this->m_pAnimAction = val; }

        void SetFilePath(const std::string val) { this->m_filePath = val; }
        void SetBaseName(const std::string val) { this->m_baseName = val; }
        void SetExtension(const std::string val) { this->m_extension = val; }
        void SetDelayPerUnit(const float32 val) { this->m_delayPerUnit = val; }

        /**
        @brief Set the position using two float.
        @param float x position
        @param float y position
        */
        void SetPosition(const float32 x, const float32 y) const
        {
            this->SetPosition(cocos2d::Vec2(x, y));
        }

        /**
        @brief Set the position using normal cocos2d framework's vector2
        @param vec2
        */
        void SetPosition(const cocos2d::Vec2 pos) const
        {
            this->GetSprite()->setPosition(pos);
        }
        
        /** getter **/
        JCSCos2x_Animator* GetJCSCos2xAnimator() const { return this->m_pJCSCos2xAnimator; }
        cocos2d::Sprite* GetSprite() const { return this->m_pSprite; }
        cocos2d::Animation* GetAnimation() const { return this->m_pAnimation; }
        cocos2d::Animate* GetAnimate() const { return this->m_pAnimate; }
        cocos2d::Action* GetAnimAction() const { return this->m_pAnimAction; }

        const std::string GetFilePath() const { return this->m_filePath; }
        const std::string GetExternsion() const { return this->m_extension; }
    };
}

#endif // __JCSCOS2X_GAMEOBJECT_H__
