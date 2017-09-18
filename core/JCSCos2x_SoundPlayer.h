#ifndef __JCSCOS2X_SOUNDPLAYER_H__
/**
 * $File: JCSCos2x_SoundPlayer.h $
 * $Date: 2016-11-22 21:28:22 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_SOUNDPLAYER_H__


#include "cocos2d.h"

#include <SimpleAudioEngine.h>
#include <AudioEngine.h>


namespace JCSCos2x
{

    /**
    @desc Rewrapper for cocos2dx framework to own use.

    @source: http://shahdza.blog.51cto.com/2410787/1545820
    */
	class JCSCos2x_SoundPlayer
	{
	private:
		// singleton
		static JCSCos2x_SoundPlayer* s_pSoundPlayer;

        // hold the background music id.
        int32 m_bgmId = -1;

	public:
		virtual ~JCSCos2x_SoundPlayer();

		/**
		@brief Singleton

		@return Return unique instance object.
		*/
		static JCSCos2x_SoundPlayer* GetInstance()
		{
			if (!s_pSoundPlayer)
                s_pSoundPlayer = new JCSCos2x_SoundPlayer;
			return s_pSoundPlayer;
		}
		
		/**
		@brief Destroy singleton instance object.
		*/
		static void DestroyInstance()
		{
			SafeDeleteObject(s_pSoundPlayer);
		}

        /**
        @ breif Play sound effects.
        */
		void PlayOneShot(const char* filePath, bool loop = false, 
            float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
        /**
        @brief Play the Background Music.
        */
		void PlayBGM(const std::string& filePath, 
            bool loop = true, 
            float volume = 1.0f, 
            const cocos2d::experimental::AudioProfile* profile = nullptr);

        /**
        @brief Set background music volume.
        */
        void SetBGMVolume(float32 volume);
        /**
        @brief Get background music volume.
        */
        int32 GetBGMVolume();
        /**
        @brief pause background music volume.
        */
        void PauseBGM();

        /**
        @brief stop background music.
        */
        void StopBGM();

		
		// setter

		// getter
		CocosDenshion::SimpleAudioEngine* GetSimpleAduioEngine() const { return CocosDenshion::SimpleAudioEngine::getInstance(); }
        int32 GetBGMId() const { return this->m_bgmId; }

	private:
		// Constructor
		JCSCos2x_SoundPlayer();
	};
}

#endif // __JCSCOS2X_SOUNDPLAYER_H__
