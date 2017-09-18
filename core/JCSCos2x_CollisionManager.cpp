/**
 * $File: JCSCos2x_CollisionManager.cpp $
 * $Date: 2016-12-05 21:11:47 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{

    JCSCos2x_CollisionManager::JCSCos2x_CollisionManager()
        : m_colliders()
    {

    }

    JCSCos2x_CollisionManager::~JCSCos2x_CollisionManager()
    {

    }

    bool JCSCos2x_CollisionManager::CheckCollide(const Sprite* sprite)
    {
        for (Sprite* pSprite : m_colliders)
        {
            
        }

        // not collide.
        return false;
    }

}
