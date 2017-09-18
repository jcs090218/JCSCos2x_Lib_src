#ifndef __JCSCOS2X_MUSICFADE_H__
/**
 * $File: JCSCos2x_MusicFade.h $
 * $Date: 2016-11-24 11:53:36 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_MUSICFADE_H__

#include "cocos2d.h"


namespace JCSCos2x
{

    /**
    @class JCSCos2x_MusicFade
    @brief Music Fader for Cocos2dx
    @source http://www.fuguelike.com/music-fader-for-cocos2dx/
    */
    class JCSCos2x_MusicFade
        : public cocos2d::CCActionInterval
    {
    public:
        JCSCos2x_MusicFade();

        static JCSCos2x_MusicFade* create(float d, float volume, bool pauseOnComplete = false);
        bool initWithDuration(float d, float volume, bool pauseOnComplete);

        virtual void startWithTarget(cocos2d::CCNode *pTarget);
        virtual void update(float time);
        virtual void stop(void);

    protected:
        float m_targetVal;
        float m_initialVal;
        bool m_bPauseOnComplete;
    };
}

typedef JCSCos2x::JCSCos2x_MusicFade JCSCos2x_MusicFade;

#endif // __JCSCOS2X_MUSICFADE_H__
