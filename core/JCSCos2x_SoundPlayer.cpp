/**
 * $File: JCSCos2x_SoundPlayer.cpp $
 * $Date: 2016-11-22 21:28:24 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"

using namespace cocos2d::experimental;


namespace JCSCos2x
{
	JCSCos2x_SoundPlayer* JCSCos2x_SoundPlayer::s_pSoundPlayer = nullptr;

	JCSCos2x_SoundPlayer::JCSCos2x_SoundPlayer()
	{
        
	}

	JCSCos2x_SoundPlayer::~JCSCos2x_SoundPlayer()
	{
        s_pSoundPlayer = nullptr;
	}

	void JCSCos2x_SoundPlayer::PlayOneShot(
        const char* filePath,
        bool loop /*= false*/, 
        float pitch /*= 1.0f*/, 
        float pan /*= 0.0f*/,
        float gain /*= 1.0f*/)
	{
        auto pSimpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

        pSimpleAudioEngine->playEffect(filePath, loop, pitch, pan, gain);
	}

	void JCSCos2x_SoundPlayer::PlayBGM(
        const std::string& filePath, 
        bool loop /*= true*/, 
        float volume /*= 1.0f*/, 
        const AudioProfile* profile /*= nullptr*/)
	{
        // NOTE(jenchieh): obsolete in v3 Cocos2d-x Framework
        /*auto pSimpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

        pSimpleAudioEngine->preloadBackgroundMusic(filePath);
        pSimpleAudioEngine->playBackgroundMusic(filePath, loop);*/


        // stop the previous audio source
        StopBGM();

        // play the new audio source.
        m_bgmId = AudioEngine::play2d(filePath, loop, volume, profile);
	}

    void JCSCos2x_SoundPlayer::SetBGMVolume(float32 volume)
    {
        // set the volume using bgm id.
        AudioEngine::setVolume(this->GetBGMId(), volume);
    }

    int32 JCSCos2x_SoundPlayer::GetBGMVolume()
    {
        return AudioEngine::getVolume(this->GetBGMId());
    }

    void JCSCos2x_SoundPlayer::PauseBGM()
    {
        AudioEngine::pause(this->GetBGMId());
    }

    void JCSCos2x_SoundPlayer::StopBGM()
    {
        AudioEngine::stop(this->GetBGMId());
    }

}
