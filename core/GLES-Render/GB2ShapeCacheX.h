/*******************************************************************************************************/
/*
 *
 * @File:           GB2ShapeCacheX.h
 * @Group:          Libraries
 * @Version:        Revision: 1.2.9   (Cocos2d-x V3.X)
 * @Last changed:   Date: 2014/08/06 08:03:06
 * @Created:        Date: 2014/08/05 05:03:06
 * @Purpose:        Define all class, function and variables for GB2ShapeCacheX.cpp object file.
 * @Author:         Harion
 * @Copyright:      (C)2012-2015 CreativeGame - G2TVN.,Corp
 * @Product:        :HerosWorld:
 *
 */
/*******************************************************************************************************/

#ifndef __GB2_SHAPE_CACHE_X__
#define __GB2_SHAPE_CACHE_X__

#include "cocos2d.h"

class BodyDef;
class b2Body;

namespace cocos2d {
	class GB2ShapeCache {
	public:
		static GB2ShapeCache * getInstance(void);
		
	public:
		bool init();			
		void addShapesWithFile(const std::string &plist);
		void addFixturesToBody(b2Body * body, const std::string &shape);
		cocos2d::Point anchorPointForShape(const std::string &shape);
		void reset();
		float getPtmRatio() { return ptmRatio; }
		~GB2ShapeCache() {}
		
	private:
          CC_SYNTHESIZE(bool, _ready, Ready);
		std::map<std::string, BodyDef *> shapeObjects;
		GB2ShapeCache(void) {}
		float ptmRatio;
	};
}

#endif // defined(__GB2_SHAPE_CACHE_X__)
