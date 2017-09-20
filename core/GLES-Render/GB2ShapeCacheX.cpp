/*******************************************************************************************************/
/*
 *
 * @File:           GB2ShapeCacheX.cpp
 * @Group:          Libraries
 * @Version:        Revision: 1.2.9   (Cocos2d-x V3.X)
 * @Last changed:   Date: 2014/08/06 08:03:06
 * @Created:        Date: 2014/08/05 05:03:06
 * @Purpose:        Process for GB2ShapeCacheX object.
 * @Author:         Harion
 * @Copyright:      (C)2012-2015 CreativeGame - G2TVN.,Corp
 * @Product:        :HerosWorld:
 *
 */
/*******************************************************************************************************/

#include "GB2ShapeCacheX.h"
#include "Box2D/Box2D.h"

using namespace std;
using namespace cocos2d;


// Define class FixtureDef
class FixtureDef {
public:
    FixtureDef() : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

// Define class BodyDef
class BodyDef {
public:
	BodyDef() : fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	FixtureDef *fixtures;
	Point anchorPoint;
};

// Define singleton instance object default is NULL
static GB2ShapeCache * _instance = NULL;


/*====================================================================================================*/
/*
 * @Name:      getInstance
 * @Class:     GB2ShapeCache
 * @Desc:      Get instance of this object
 * @Param:     void
 * @Return:    GB2ShapeCache
 */
/*----------------------------------------------------------------------------------------------------*/

GB2ShapeCache * GB2ShapeCache::getInstance(void) {
	if (!_instance) {
          _instance = new GB2ShapeCache();
          _instance->init();
	}
	return _instance;
}


/*====================================================================================================*/
/*
 * @Name:      init
 * @Class:     GB2ShapeCache
 * @Desc:      Initialization GB2 Shape Cache object
 * @Param:     void
 * @Return:    bool
 */
/*----------------------------------------------------------------------------------------------------*/

bool GB2ShapeCache::init() {
	return true;
}


/*====================================================================================================*/
/*
 * @Name:      reset
 * @Class:     GB2ShapeCache
 * @Desc:      Reset shape object
 * @Param:     null
 * @Return:    voi
 */
/*----------------------------------------------------------------------------------------------------*/

void GB2ShapeCache::reset() {
	map<string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}


/*====================================================================================================*/
/*
 * @Name:      addFixturesToBody
 * @Class:     GB2ShapeCache
 * @Desc:      Add fixtures to the body
 * @Param:     b2Body *body, const string &shape
 * @Return:    voi
 */
/*----------------------------------------------------------------------------------------------------*/

void GB2ShapeCache::addFixturesToBody(b2Body *body, const string &shape) {
	map<string, BodyDef *>::iterator pos = shapeObjects.find(shape);
     if (getReady()) {
          assert(pos != shapeObjects.end());
          BodyDef *so = (*pos).second;
          FixtureDef *fix = so->fixtures;
          while (fix) {
               body->CreateFixture(&fix->fixture);
               fix = fix->next;
          }
     } else return;
}


/*====================================================================================================*/
/*
 * @Name:      anchorPointForShape
 * @Class:     GB2ShapeCache
 * @Desc:      Get the anchor point for shape
 * @Param:     const string &shape
 * @Return:    Point
 */
/*----------------------------------------------------------------------------------------------------*/

Point GB2ShapeCache::anchorPointForShape(const string &shape) {
     Point result;
     if (getReady()) {
          map<string, BodyDef *>::iterator pos = shapeObjects.find(shape);
          assert(pos != shapeObjects.end());
          BodyDef *bd = (*pos).second;
          result = bd->anchorPoint;
     }
     return result;
}


/*====================================================================================================*/
/*
 * @Name:      addShapesWithFile
 * @Class:     GB2ShapeCache
 * @Desc:      Add the shape with data from file
 * @Param:     const string &plist
 * @Return:    Point
 */
/*----------------------------------------------------------------------------------------------------*/

void GB2ShapeCache::addShapesWithFile(const string &plist) {
	//const char * fullName = FileUtils::getInstance()->fullPathForFilename(plist.c_str()).c_str();
     __Dictionary * dict = __Dictionary::createWithContentsOfFile(plist.c_str());
	CCAssert(dict != NULL, "Shape-file not found");
     if (dict->count()==0) {
          setReady(false);
          return;
     }
     setReady(true);
     CCAssert(dict->count() != 0, "plist file empty or not existing");
	__Dictionary * metadataDict = (__Dictionary *)dict->objectForKey("metadata");
     int format = static_cast<__String *>(metadataDict->objectForKey("format"))->intValue();
     ptmRatio = static_cast<__String *>(metadataDict->objectForKey("ptm_ratio"))->floatValue();
     log("ptmRatio = %f",ptmRatio);
	CCAssert(format == 1, "Format not supported");
	__Dictionary * bodyDict = (__Dictionary *)dict->objectForKey("bodies");
     b2Vec2 vertices[b2_maxPolygonVertices];
     DictElement * dictElem;
     string bodyName;
	__Dictionary * bodyData;
     CCDICT_FOREACH(bodyDict,dictElem ) {
          bodyData = (__Dictionary*)dictElem->getObject();
          bodyName = dictElem->getStrKey();
          BodyDef * bodyDef = new BodyDef();
          bodyDef->anchorPoint = PointFromString(static_cast<__String *>(bodyData->objectForKey("anchorpoint"))->getCString());
          __Array * fixtureList = (__Array*)(bodyData->objectForKey("fixtures"));
          FixtureDef ** nextFixtureDef = &(bodyDef->fixtures);
          Ref *arrayElem;
          CCARRAY_FOREACH(fixtureList, arrayElem) {
               b2FixtureDef basicData;
               __Dictionary* fixtureData = (__Dictionary*)arrayElem;
               basicData.filter.categoryBits = static_cast<__String *>(fixtureData->objectForKey("filter_categoryBits"))->intValue();
               basicData.filter.maskBits = static_cast<__String *>(fixtureData->objectForKey("filter_maskBits"))->intValue();
               basicData.filter.groupIndex = static_cast<__String *>(fixtureData->objectForKey("filter_groupIndex"))->intValue();
               basicData.friction = static_cast<__String *>(fixtureData->objectForKey("friction"))->floatValue();
               basicData.density = static_cast<__String *>(fixtureData->objectForKey("density"))->floatValue();
               basicData.restitution = static_cast<__String *>(fixtureData->objectForKey("restitution"))->floatValue();
               basicData.isSensor = (bool)static_cast<__String *>(fixtureData->objectForKey("isSensor"))->intValue();
               __String * cb = static_cast<__String *>(fixtureData->objectForKey("userdataCbValue"));
               int callbackData = 0;
               if (cb) {
                  callbackData = cb->intValue();
               }
               __String * fixtureType = static_cast<__String *>(fixtureData->objectForKey("fixture_type"));
               if (strcmp(fixtureType->getCString(),"POLYGON") == 0) {
                    __Array *polygonsArray = (__Array *)(fixtureData->objectForKey("polygons"));
                    Ref *dicArrayElem;
                    CCARRAY_FOREACH(polygonsArray, dicArrayElem) {
                         FixtureDef *fix = new FixtureDef();
                         fix->fixture = basicData; // copy basic data
                         fix->callbackData = callbackData;
                         b2PolygonShape *polyshape = new b2PolygonShape();
                         int vindex = 0;
                         __Array *polygonArray = (__Array*)dicArrayElem;
                         assert(polygonArray->count() <= b2_maxPolygonVertices);
                         Ref *piter;
                         CCARRAY_FOREACH(polygonArray, piter) {
                              __String *verStr = (__String*)piter;
                              Point offset = PointFromString(verStr->getCString());
                              vertices[vindex].x = (offset.x / ptmRatio) ;
                              vertices[vindex].y = (offset.y / ptmRatio) ;
                              vindex++;
                         }
                         polyshape->Set(vertices, vindex);
                         fix->fixture.shape = polyshape;
                         *nextFixtureDef = fix;
                         nextFixtureDef = &(fix->next);
                    }
			} else if (strcmp(fixtureType->getCString(),"CIRCLE") == 0) {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
                    __Dictionary *circleData = (__Dictionary *)fixtureData->objectForKey("circle");
                    b2CircleShape *circleShape = new b2CircleShape();
                    circleShape->m_radius = static_cast<__String *>(circleData->objectForKey("radius"))->floatValue() / ptmRatio;
				Point p = PointFromString(static_cast<__String *>(circleData->objectForKey("position"))->getCString());
                    circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                    fix->fixture.shape = circleShape;
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
               } else {
				CCAssert(0, "Unknown fixtureType");
			}
		}
          shapeObjects[bodyName] = bodyDef;
     }
}