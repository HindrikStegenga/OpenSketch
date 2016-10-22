//
// Created by hindrik on 4-10-16.
//

#include "Shape.h"
#include <algorithm>
#include "../OpenGL/OpenGLRenderManager.h"
#include "../Application.h"
#include "../OpenGL/Drawer.h"

//mappen van range x-y naar w-z
static float map(float _value, float _from1, float _to1, float _from2, float _to2)
{
    return _from2 + (_value - _from1) * (_to2 - _from2) / (_to1 - _from1);
}

Shape::Shape(OpenGLRenderManager* _oglRenderer,int _posx, int _posy, int _width, int _height, Drawer* _drawer)
        : m_oglRenderer(_oglRenderer), m_drawer(_drawer)
{
    //Basic Shape in t midden, deze transformeer ik doormiddel van matrices naar de juiste positie en grootte
    setSize(_width, _height);
    setPosition(_posx, _posy);
}

Shape::~Shape() {
}

void Shape::setPosition(int _pixelsX, int _pixelsY)
{
    int window_width, window_height;
    Application::getInstance().getPaintWindowSize(window_width, window_height);

    //Mappen van de pixel coord naar Normalized Device Coords range. (0 tot width/height naar -1 tot 1)
    float posx = map(_pixelsX, 0, window_width, -1.0f, 1.0f);
    float posy = map(_pixelsY, 0, window_height, 1.0f, -1.0f);

    //Deze transform op de matrix toepassen, we moeten wel de scale behouden, immers die bepaalt de grootte.
    glm::vec3 scale;
    glm::quat dummy0;
    glm::vec3 dummy1;
    glm::vec4 dummy2;
    glm::decompose(m_transformMatrix, scale, dummy0,dummy1,dummy1,dummy2);
    glm::mat4 identity;
    m_transformMatrix = glm::translate(identity, glm::vec3(posx, posy, 0.0f));
    m_transformMatrix = glm::scale(m_transformMatrix, scale);
    m_position = glm::vec2(_pixelsX, _pixelsY);
}

void Shape::setSize(int _width, int _height)
{
    int window_width, window_height;
    Application::getInstance().getPaintWindowSize(window_width, window_height);


    int defaultSizeX = static_cast<int>(0.5f * window_width);
    int defaultSizeY = static_cast<int>(0.5f * window_height);

    //Mappen van de pixel coord naar Normalized Device Coords range. (0 tot width/height naar -1 tot 1)
    float scalex = map(_width, 0, defaultSizeX, 0.0f, 1.0f);
    float scaley = map(_height, 0, defaultSizeY, 0.0f, 1.0f);

    //Deze transform op de matrix toepassen, we moeten wel de translatie behouden, immers die bepaalt de positie.
    glm::vec3 translate;
    glm::quat dummy0;
    glm::vec3 dummy1;
    glm::vec4 dummy2;
    glm::decompose(m_transformMatrix, dummy1, dummy0,translate,dummy1,dummy2);
    glm::mat4 identity;
    identity = glm::translate(identity, translate);
    m_transformMatrix = glm::scale(identity, glm::vec3(scalex, scaley, 1.0f));
    m_size = glm::vec2(_width, _height);
}

void Shape::draw() const {
    if(m_drawer != nullptr)
        m_drawer->draw(*this);
}

Shape* Shape::getSelectedShape(int _xpos, int _ypos) const {

    int xleft, xright, ytop, ybottom;
    xleft = static_cast<int>(getPosition().x - (getSize().x / 2));
    xright = static_cast<int>(getPosition().x + (getSize().x / 2));
    ytop = static_cast<int>(getPosition().y - (getSize().y / 2));
    ybottom = static_cast<int>(getPosition().y + (getSize().y / 2));

    if(_xpos >= xleft && _xpos <= xright && _ypos <= ybottom && _ypos >= ytop)
        return const_cast<Shape*>(this);
    return nullptr;
}

Shape *Shape::getSelectedShapePriority(int _xpos, int _ypos, Shape *_prioShape, bool &_isPrio) {
    int xleft, xright, ytop, ybottom;
    xleft = static_cast<int>(getPosition().x - (getSize().x / 2));
    xright = static_cast<int>(getPosition().x + (getSize().x / 2));
    ytop = static_cast<int>(getPosition().y - (getSize().y / 2));
    ybottom = static_cast<int>(getPosition().y + (getSize().y / 2));

    if(_xpos >= xleft && _xpos <= xright && _ypos <= ybottom && _ypos >= ytop)
    {
        _isPrio = (this == _prioShape);
        return const_cast<Shape*>(this);
    }
    return nullptr;
}