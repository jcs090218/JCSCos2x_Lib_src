#ifndef __JCSCOS2X_CONTACTLISTENER_H__
/**
 * $File: JCSCos2x_ContactListener.h $
 * $Date: 2016-12-06 16:37:55 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */
#define __JCSCOS2X_CONTACTLISTENER_H__


#include <Box2D\Box2D.h>

const int32 k_maxContactPoints = 2048;

#define SCALE_RATIO 10

namespace JCSCos2x
{
    class JCSCos2x_ContactListener;

    /**
    @class DestructionListener
    @brief This is called when a joint in the world is 
    implicitly destroyed because an attached body is 
    destroyed. This gives us a chance to nullify the 
    mouse joint.
    */
    class DestructionListener 
    : public b2DestructionListener
    {
    public:
        JCSCos2x_ContactListener* test;

    public:
        void SayGoodbye(b2Fixture* fixture) { B2_NOT_USED(fixture); }
        void SayGoodbye(b2Joint* joint);
    };

    /**
    @struct ContactPoint
    @brief 
    */
    struct JCSCos2x_ContactPoint
    {
        b2Fixture* fixtureA;
        b2Fixture* fixtureB;
        b2Vec2 normal;
        b2Vec2 position;
        b2PointState state;
        float32 normalImpulse;
        float32 tangentImpulse;
        float32 separation;

        bool operator==(const JCSCos2x_ContactPoint& other) const
        {
            return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
        }
    };

    /**
    @class JCSCos2x_ContactListener
    @brief Contact Listener for box2d handle.
    */
    class JCSCos2x_ContactListener
        : public b2ContactListener
    {
    protected:
        friend class DestructionListener;
        friend class BoundaryListener;
        friend class ContactListener;


        JCSCos2x_ContactPoint m_points[k_maxContactPoints];
        std::vector<JCSCos2x_ContactPoint> m_contacts;

        b2World* m_pWorld;
        b2Body* m_pGroundBody;

        b2AABB m_worldAABB;
        
        int32 m_pointCount;
        DestructionListener m_destructionListener;
        int32 m_textLine;
        
        b2Body* m_bomb;
        b2MouseJoint* m_mouseJoint;
        b2Vec2 m_bombSpawnPoint;
        bool m_bombSpawning;
        b2Vec2 m_mouseWorld;
        int32 m_stepCount;

        b2Profile m_maxProfile;
        b2Profile m_totalProfile;

    public:
        JCSCos2x_ContactListener();
        virtual ~JCSCos2x_ContactListener();

        // Let derived tests know that a joint was destroyed.
        virtual void JointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }

        // Callbacks for derived classes.
        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);


        /** setter **/

        /** getter **/
        b2World* GetWorld() const { return this->m_pWorld; }
        b2Body* GetGroundBody() const { return this->m_pGroundBody; }
    };
}

#endif // __JCSCOS2X_CONTACTLISTENER_H__
