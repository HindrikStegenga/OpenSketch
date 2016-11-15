//
// Created by hindrik on 14-11-16.
//

#ifndef OPEN_SKETCH_MOVESHAPEVISITOR_H
#define OPEN_SKETCH_MOVESHAPEVISITOR_H


#include "../Shapes/Visitor.h"
#include <vector>
#include <string>

class MoveShapeVisitor : public Visitor{
private:
    int m_x = 0;
    int m_y = 0;
public:
    MoveShapeVisitor(int _x, int _y);

    virtual void visit(Shape& _shape) override;

    virtual void visit(Group& _group) override;
};


#endif //OPEN_SKETCH_MOVESHAPEVISITOR_H