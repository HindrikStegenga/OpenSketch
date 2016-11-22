//
// Created by hindrik on 16-11-16.
//

#include "../Shapes/Shape.h"
#include "../Shapes/Group.h"
#include "ResizeShapeVisitor.h"
#include "MoveShapeVisitor.h"

ResizeShapeVisitor::ResizeShapeVisitor(int _pixelsX, int _pixelsY) : m_pixelsX(_pixelsX), m_pixelsY(_pixelsY)
{
}

void ResizeShapeVisitor::start_visit(Shape &_shape) {
    //Shape is zelfstandig als er geen parent group is.
    if(m_deque.size() == 0)
    {
        _shape.resize(m_pixelsX, m_pixelsY);
        return;
    }

    //Shape is onderdeel van een groep

    ResizeData rs = m_deque.back();

    int newHeight = static_cast<int>(_shape.getSize().y * rs.m_factorY);
    int newWidth = static_cast<int>(_shape.getSize().x * rs.m_factorX);

    int delta_x = static_cast<int>((_shape.getPosition().x - rs.m_old_width) * (rs.m_factorX - 1));
    int delta_y = static_cast<int>((_shape.getPosition().y - rs.m_old_height) * (rs.m_factorY - 1));

    MoveShapeVisitor v(delta_x, delta_y);
    _shape.accept(v);

    int changeX = newWidth - static_cast<int>(_shape.getSize().x);
    int changeY = newHeight - static_cast<int>(_shape.getSize().y);

    if(!(changeX == 0 && changeY == 0))
        _shape.resize(changeX, changeY);
}

void ResizeShapeVisitor::start_visit(Group& _group) {

    //Indien de deque leeg is, maak een parent group met de correcte data,
    // en resize alles ten opzichte van deze group\
    // Shapes in groups in de parentgroup worden dus als individuele shapes behandeld.
    if(m_deque.size() == 0)
    {
        int old_pos_x = static_cast<int>(_group.getPosition().x);
        int old_pos_y = static_cast<int>(_group.getPosition().y);

        int old_width = static_cast<int>(_group.getSize().x);
        int old_height = static_cast<int>(_group.getSize().y);

        float factorX = static_cast<float>(old_width + m_pixelsX) / old_width;
        float factorY = static_cast<float>(old_height + m_pixelsY) / old_height;

        ResizeData rs = {
                old_pos_x,
                old_pos_y,
                old_width,
                old_height,
                factorX,
                factorY,
        };

        m_deque.push_front(rs);
        return;
    }
    //Push empty
    m_deque.push_front(ResizeData{});
}

void ResizeShapeVisitor::stop_visit(Shape &_shape) {

}

void ResizeShapeVisitor::stop_visit(Group &_group) {

    //indien parent group, reset de group op de correcte positie.
    // (Nodig ivm matrix ordening, waardoor de positie af wijkt, en dus naar oude gereset moet worden)
    if(m_deque.size() == 1) {

        ResizeData rs = m_deque.front();

        int xdiff = static_cast<int>(rs.m_old_pos_x - _group.getPosition().x);
        int ydiff = static_cast<int>(rs.m_old_pos_y - _group.getPosition().y);

        MoveShapeVisitor v(xdiff,ydiff);
        _group.accept(v);
    }

    //Pop empty of pop de parent.
    m_deque.pop_front();
}
