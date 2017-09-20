/*******************************************************************************************************/
/*
 *
 * @File:           B2DebugDrawLayer.h
 * @Group:          Libraries
 * @Version:        Revision: 1.2.9   (Cocos2d-x V3.X)
 * @Last changed:   Date: 2014/08/06 08:03:06
 * @Created:        Date: 2014/08/05 05:03:06
 * @Purpose:        Define all class, function and variables for B2DebugDrawLayer.cpp object file.
 * @Author:         Harion
 * @Copyright:      (C)2012-2015 CreativeGame - G2TVN.,Corp
 * @Product:        :HerosWorld:
 *
 */
/*******************************************************************************************************/

#ifndef __B2_DEBUG_DRAW_LAYER__
#define __B2_DEBUG_DRAW_LAYER__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLESRender.h"
#include "VisibleRect.h"

using namespace cocos2d;

/**
@class B2DebugDrawLayer
@brief 
*/
class B2DebugDrawLayer 
    : public Layer 
{
  b2World * mB2World;
  GLESDebugDraw * mB2DebugDraw;
  const float mPtmRatio;
 
public:
  B2DebugDrawLayer(b2World* pB2World, float pPtmRatio);
  virtual ~B2DebugDrawLayer();
  static B2DebugDrawLayer* create(b2World* pB2World, float pPtmRatio, int mod=0);
  virtual bool init(int mod=0);
  virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
protected:
    Mat4 _modelViewMV;
    void onDraw();
    CustomCommand _customCommand;
};

#endif // defined(__B2_DEBUG_DRAW_LAYER__)
