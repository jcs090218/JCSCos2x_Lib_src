/**
 * $File: JCSCos2x_ContactListener.cpp $
 * $Date: 2016-12-06 16:40:19 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2016 by Shen, Jen-Chieh $
 */

#include "../JCSCos2x.h"


namespace JCSCos2x
{

    void DestructionListener::SayGoodbye(b2Joint* joint)
    {
        if (test->m_mouseJoint == joint)
        {
            test->m_mouseJoint = NULL;
        }
        else
        {
            test->JointDestroyed(joint);
        }
    }

    JCSCos2x_ContactListener::JCSCos2x_ContactListener()
        : m_contacts()
    {
        b2Vec2 gravity;
        gravity.Set(0.0f, -9.81f);
        m_pWorld = new b2World(gravity);
        m_bomb = NULL;
        m_textLine = 30;
        m_mouseJoint = NULL;
        m_pointCount = 0;

        m_destructionListener.test = this;
        m_pWorld->SetDestructionListener(&m_destructionListener);
        m_pWorld->SetContactListener(this);
        //m_pWorld->SetDebugDraw(&g_debugDraw);

        m_bombSpawning = false;

        m_stepCount = 0;

        b2BodyDef bodyDef;
        m_pGroundBody = m_pWorld->CreateBody(&bodyDef);

        memset(&m_maxProfile, 0, sizeof(b2Profile));
        memset(&m_totalProfile, 0, sizeof(b2Profile));
    }

    JCSCos2x_ContactListener::~JCSCos2x_ContactListener()
    {
        SafeDeleteObject(m_pWorld);
    }

    void JCSCos2x_ContactListener::BeginContact(b2Contact* contact)
    {
        // We need to copy out the data because the b2Contact passed in
        // is reused.
        JCSCos2x_ContactPoint myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
        m_contacts.push_back(myContact);
    }

    void JCSCos2x_ContactListener::EndContact(b2Contact* contact)
    {
        JCSCos2x_ContactPoint myContact = { contact->GetFixtureA(), contact->GetFixtureB() };

        std::vector<JCSCos2x_ContactPoint>::iterator pos;
        pos = std::find(m_contacts.begin(), m_contacts.end(), myContact);

        if (pos != m_contacts.end())
        {
            m_contacts.erase(pos);
        }
    }

    void JCSCos2x_ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
        const b2Manifold* manifold = contact->GetManifold();

        if (manifold->pointCount == 0)
        {
            return;
        }

        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
        b2GetPointStates(state1, state2, oldManifold, manifold);

        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);

        for (int32 i = 0; i < manifold->pointCount && m_pointCount < k_maxContactPoints; ++i)
        {
            JCSCos2x_ContactPoint* cp = m_points + m_pointCount;
            cp->fixtureA = fixtureA;
            cp->fixtureB = fixtureB;
            cp->position = worldManifold.points[i];
            cp->normal = worldManifold.normal;
            cp->state = state2[i];
            cp->normalImpulse = manifold->points[i].normalImpulse;
            cp->tangentImpulse = manifold->points[i].tangentImpulse;
            cp->separation = worldManifold.separations[i];
            ++m_pointCount;
        }
    }

    void JCSCos2x_ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        
    }
}
