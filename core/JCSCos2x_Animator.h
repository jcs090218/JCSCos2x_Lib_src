#ifndef __JCSCOS2X_ANIMATOR_H__
/**
 * $File: JCSCos2x_Animator.h $
 * $Date: 2016-11-24 20:51:13 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_ANIMATOR_H__


namespace JCSCos2x
{
    class JCSCos2x_GameObject;

    /**
    @class JCSCos2x_Animator
    @brief Handle all the animation switching. (not working right now.)
    */
    class JCSCos2x_Animator
    {
    private:
        JCSCos2x_GameObject* m_pGameObject = nullptr;
        std::string m_filePath;
        std::string m_extension;

    public:
        explicit JCSCos2x_Animator(JCSCos2x_GameObject* gameObject);
        virtual ~JCSCos2x_Animator();

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
        void DoAnimationWithFile(
            const std::string baseName,
            const int32 frameCount,
            const int32 delayPerUnit,
            const int32 loop = -1,
            const bool restoreOriginFrame = true,
            const int32 startFrameIndex = 0);

        /** setter **/
        void SetFilePath(const std::string val) { this->m_filePath = val; }
        void SetExtension(const std::string val) { this->m_extension = val; }

        /** getter **/
        const std::string GetFilePath() const { return this->m_filePath; }
        const std::string GetExternsion() const { return this->m_extension; }

    };
}

#endif // __JCSCOS2X_ANIMATOR_H__
