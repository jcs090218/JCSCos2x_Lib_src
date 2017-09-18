/*******************************************************************************************************/
/*
 *
 * @File:           GLESRender.cpp
 * @Group:          Libraries
 * @Version:        Revision: 1.2.9   (Cocos2d-x V3.X)
 * @Last changed:   Date: 2014/08/06 08:03:06
 * @Created:        Date: 2014/08/05 05:03:06
 * @Purpose:        Process for GLESRender object.
 * @Author:         Harion
 * @Copyright:      (C)2012-2015 CreativeGame - G2TVN.,Corp
 * @Product:        :HerosWorld:
 *
 */
/*******************************************************************************************************/

#include "GLESRender.h"
#include "cocos2d.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

USING_NS_CC;

/*====================================================================================================*/
/*
 * @Name:      Constructor
 * @Class:     GLESDebugDraw
 * @Desc:      Construct GLES Debug Draw object
 * @Param:     null
 * @Return:    GLESDebugDraw
 */
/*----------------------------------------------------------------------------------------------------*/

GLESDebugDraw::GLESDebugDraw() : mRatio(1.0f) {
     this->initShader();
}


/*====================================================================================================*/
/*
 * @Name:      Constructor
 * @Class:     GLESDebugDraw
 * @Desc:      Construct GLES Debug Draw object with ratio
 * @Param:     float32 ratio
 * @Return:    GLESDebugDraw
 */
/*----------------------------------------------------------------------------------------------------*/

GLESDebugDraw::GLESDebugDraw(float32 ratio) : mRatio(ratio) {
     this->initShader();
}


/*====================================================================================================*/
/*
 * @Name:      initShader
 * @Class:     GLESDebugDraw
 * @Desc:      Initialization Shader object
 * @Param:     void
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::initShader(void) {
     mShaderProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
     mColorLocation = glGetUniformLocation( mShaderProgram->getProgram(), "u_color");
}


/*====================================================================================================*/
/*
 * @Name:      DrawPolygon
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by polygon
 * @Param:     const b2Vec2* old_vertices, int vertexCount, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     b2Vec2* vertices = new b2Vec2[vertexCount];
     for ( int i=0;i<vertexCount;i++) {
          vertices[i] = old_vertices[i];
          vertices[i] *= mRatio;
     }
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
     glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);
     CHECK_GL_ERROR_DEBUG();
     delete[] vertices;
}


/*====================================================================================================*/
/*
 * @Name:      DrawSolidPolygon
 * @Class:     GLESDebugDraw
 * @Desc:      Draw solid for shader by polygon
 * @Param:     const b2Vec2* old_vertices, int vertexCount, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     b2Vec2* vertices = new b2Vec2[vertexCount];
     for ( int i=0;i<vertexCount;i++) {
          vertices[i] = old_vertices[i];
          vertices[i] *= mRatio;
     }
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
     glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);
     CHECK_GL_ERROR_DEBUG();
     delete[] vertices;
}


/*====================================================================================================*/
/*
 * @Name:      DrawCircle
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by circle
 * @Param:     const b2Vec2& center, float32 radius, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     const float32 k_segments = 16.0f;
     int vertexCount=16;
     const float32 k_increment = 2.0f * b2_pi / k_segments;
     float32 theta = 0.0f;
     GLfloat*    glVertices = new GLfloat[vertexCount*2];
     for (int i = 0; i < k_segments; ++i) {
          b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
          glVertices[i*2]=v.x * mRatio;
          glVertices[i*2+1]=v.y * mRatio;
          theta += k_increment;
     }
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
     glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);
     CHECK_GL_ERROR_DEBUG();
     delete[] glVertices;
}


/*====================================================================================================*/
/*
 * @Name:      DrawSolidCircle
 * @Class:     GLESDebugDraw
 * @Desc:      Draw solid for shader by circle
 * @Param:     const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     const float32 k_segments = 16.0f;
     int vertexCount=16;
     const float32 k_increment = 2.0f * b2_pi / k_segments;
     float32 theta = 0.0f;
     GLfloat * glVertices = new GLfloat[vertexCount*2];
     for (int i = 0; i < k_segments; ++i) {
         b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
         glVertices[i*2]=v.x * mRatio;
         glVertices[i*2+1]=v.y * mRatio;
         theta += k_increment;
     }
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
     glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
     DrawSegment(center,center+radius*axis,color);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);
     CHECK_GL_ERROR_DEBUG();
     delete[] glVertices;
}


/*====================================================================================================*/
/*
 * @Name:      DrawSegment
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by segment
 * @Param:     const b2Vec2& p1, const b2Vec2& p2, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     GLfloat glVertices[] = {p1.x * mRatio, p1.y * mRatio, p2.x * mRatio, p2.y * mRatio};
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
     glDrawArrays(GL_LINES, 0, 2);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,2);
     CHECK_GL_ERROR_DEBUG();
}


/*====================================================================================================*/
/*
 * @Name:      DrawTransform
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by transform
 * @Param:     const b2Transform& xf
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawTransform(const b2Transform& xf) {
     b2Vec2 p1 = xf.p, p2;
     const float32 k_axisScale = 0.4f;
     p2 = p1 + k_axisScale * xf.q.GetXAxis();
     DrawSegment(p1, p2, b2Color(1,0,0));
     p2 = p1 + k_axisScale * xf.q.GetYAxis();
     DrawSegment(p1,p2,b2Color(0,1,0));
}


/*====================================================================================================*/
/*
 * @Name:      DrawPoint
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by point
 * @Param:     const b2Vec2& p, float32 size, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     //glPointSize(size);
     GLfloat glVertices[] = {p.x * mRatio, p.y * mRatio};
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
     glDrawArrays(GL_POINTS, 0, 1);
     //glPointSize(1.0f);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,1);
     CHECK_GL_ERROR_DEBUG();
}


/*====================================================================================================*/
/*
 * @Name:      DrawString
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by string
 * @Param:     int x, int y, const char *string, ...
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawString(int x, int y, const char *string, ...) {
     //NSLog(@"DrawString: unsupported: %s", string);
     //printf(string);
}


/*====================================================================================================*/
/*
 * @Name:      DrawAABB
 * @Class:     GLESDebugDraw
 * @Desc:      Draw shader by AABB struct
 * @Param:     b2AABB* aabb, const b2Color& color
 * @Return:    void
 */
/*----------------------------------------------------------------------------------------------------*/

void GLESDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color) {
     mShaderProgram->use();
     mShaderProgram->setUniformsForBuiltins();
     mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
     GLfloat glVertices[] = {aabb->lowerBound.x * mRatio, aabb->lowerBound.y * mRatio, aabb->upperBound.x * mRatio, aabb->lowerBound.y * mRatio, aabb->upperBound.x * mRatio, aabb->upperBound.y * mRatio, aabb->lowerBound.x * mRatio, aabb->upperBound.y * mRatio};
     glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
     glDrawArrays(GL_LINE_LOOP, 0, 4);
     CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
     CHECK_GL_ERROR_DEBUG();
}
