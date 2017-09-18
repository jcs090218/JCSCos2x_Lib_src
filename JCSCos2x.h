#ifndef __JCSCOS2X_H__
/**
 * $File: JCSCos2x.h $
 * $Date: 2016-11-17 22:14:34 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_H__


#include "cocos2d.h"

USING_NS_CC;

#include <SimpleAudioEngine.h>
#include <AudioEngine.h>

// include JCSCC framework.
#include <JayCeS_JCS\JayCes.h>

// core
#include "core/JCSCos2x_Layer.h"
#include "core/JCSCos2x_Input.h"
#include "core/JCSCos2x_SoundPlayer.h"
#include "core/JCSCos2x_MusicFade.h"
#include "core/JCSCos2x_GameObject.h"
#include "core/JCSCos2x_Animator.h"
#include "core/JCSCos2x_CollisionManager.h"
#include "core/JCSCos2x_ContactListener.h"

// util
#include "util/JCSCos2x_Util.h"

// libraries (comment out the library u don't need.)
#include <Box2D\Box2D.h>
#include "core/GLES-Render/B2DebugDrawLayer.h"
#include "core/GLES-Render/GB2ShapeCacheX.h"
#include "core/GLES-Render/GLESRender.h"
#include "core/GLES-Render/VisibleRect.h"

#endif // __JCSCOS2X_H__
