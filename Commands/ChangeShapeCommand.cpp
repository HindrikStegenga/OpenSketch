//
// Created by hindrik on 5-10-16.
//

#include <algorithm>
#include "ChangeShapeCommand.h"
#include "../OpenGL/ShapeRenderManager.h"

ChangeShapeCommand::ChangeShapeCommand(size_t _index,int _posx_change, int _posy_change, int _sizex_change, int _sizey_change)
        : m_posx_change(_posx_change), m_posy_change(_posy_change), m_sizex_change(_sizex_change), m_sizey_change(_sizey_change), m_index(_index)
{
}

void ChangeShapeCommand::execute(Application *_context)
{
    Shape& rect = *_context->getGLManager().getShapes()[m_index];
    glm::vec2 pos = rect.getPosition();
    glm::vec2 size = rect.getSize();
    rect.setPosition(static_cast<int>(pos.x) + m_posx_change, static_cast<int>(pos.y) + m_posy_change);
    rect.setSize(static_cast<int>(size.x) + m_sizex_change, static_cast<int>(size.y) + m_sizey_change);
}

void ChangeShapeCommand::undo(Application *_context)
{
    Shape& rect = *_context->getGLManager().getShapes()[m_index];
    glm::vec2 pos = rect.getPosition();
    glm::vec2 size = rect.getSize();
    rect.setPosition(static_cast<int>(pos.x) - m_posx_change, static_cast<int>(pos.y) - m_posy_change);
    rect.setSize(static_cast<int>(size.x) - m_sizex_change, static_cast<int>(size.y) - m_sizey_change);
}