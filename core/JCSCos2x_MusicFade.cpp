/**
 * $File: JCSCos2x_MusicFade.cpp $
 * $Date: 2016-11-24 11:53:42 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"

#include <SimpleAudioEngine.h>
#include <AudioEngine.h>

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::experimental;


namespace JCSCos2x
{

    JCSCos2x_MusicFade::JCSCos2x_MusicFade()
    {
        m_initialVal = 0;
        m_targetVal = 0;
    }

    JCSCos2x_MusicFade* JCSCos2x_MusicFade::create(float duration, float volume, bool pauseOnComplete)
    {
        JCSCos2x_MusicFade *pAction = new JCSCos2x_MusicFade();
        pAction->initWithDuration(duration, volume, pauseOnComplete);
        pAction->autorelease();

        return pAction;
    }

    bool JCSCos2x_MusicFade::initWithDuration(float duration, float volume, bool pauseOnComplete)
    {
        if (CCActionInterval::initWithDuration(duration))
        {
            m_targetVal = volume;
            m_bPauseOnComplete = pauseOnComplete;
            return true;
        }

        return false;
    }

    void JCSCos2x_MusicFade::update(float time)
    {
        float vol = m_initialVal + time * (m_targetVal - m_initialVal);
        
        
        // NOTE(jenchieh): obsolete in v3 Cocos2d-x Framework
        //SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(vol);

        JCSCos2x_SoundPlayer::GetInstance()->SetBGMVolume(vol);
    }

    void JCSCos2x_MusicFade::startWithTarget(Node *pTarget)
    {
        ActionInterval::startWithTarget(pTarget);

        // NOTE(jenchieh): obsolete in v3 Cocos2d-x Framework
        //m_initialVal = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();

        m_initialVal = JCSCos2x_SoundPlayer::GetInstance()->GetBGMVolume();
    }

    void JCSCos2x_MusicFade::stop(void)
    {
        if (m_bPauseOnComplete)
        {
            // NOTE(jenchieh): obsolete in v3 Cocos2d-x Framework
            //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

            JCSCos2x_SoundPlayer::GetInstance()->PauseBGM();
        }

        CCActionInterval::stop();
    }
}
