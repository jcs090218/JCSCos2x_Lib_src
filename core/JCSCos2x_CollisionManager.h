#ifndef __JCSCOS2X_COLLISIONMANAGER_H__
/**
 * $File: JCSCos2x_CollisionManager.h $
 * $Date: 2016-12-05 21:11:44 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_COLLISIONMANAGER_H__


#include <list>

namespace JCSCos2x
{

    /**
    @class JCSCos2x_CollisionManager
    @brief handle collision detection in each layer.
    */
    class JCSCos2x_CollisionManager
    {
    private:
        // link list.
        std::list<Sprite*> m_colliders;

    public:
        JCSCos2x_CollisionManager();
        virtual ~JCSCos2x_CollisionManager();

        bool CheckCollide(const Sprite* sprite);


        /** setter **/

        /** getter **/
        std::list<Sprite*> GetColliders() const { return this->m_colliders; }
    };
}


#endif // __JCSCOS2X_COLLISIONMANAGER_H__
