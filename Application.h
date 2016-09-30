//
// Created by Hindrik Stegenga on 24-9-16.
//

#ifndef OPEN_SKETCH_APPLICATION_H
#define OPEN_SKETCH_APPLICATION_H

/*
 * SINGLETON PATTERN
 * getInstance() retourneert de instance
 * de constructor is private, zodat je die niet zomaar kan callen
 * en de copy constructor, move constructor, assignment operator en move assignment operator zijn gedelete,
 * zodat ze niet gecalled kunnen worden.
 */

#include "SupportClasses.h"
#include <iostream>
#include "includeLibs.h"
#include "GTK/GTKManager.h"
#include "GTK/GTKWindow.h"
#include "States/State.h"


//prototypes
class OpenGLRenderManager;



class Application {
public:
    static Application& getInstance();
private:
    Application();
public:
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;
    ~Application();
private:
    bool initGLFW();
    bool initGLEW();
    void initGTK();
    void processMouseAndShapes();
    void initToolWindow();
public:
    //State pattern stuff
    void setState(State* _state);
    State* getState();
    void resetState();

    //Init functions
    void initialize();
    void run();
    void getPaintWindowSize(int& _width, int& _height);
    inline void setStartupArgs(Args _args);
    inline Args getStartupArgs();
    void setShapeEdited(bool _val);
    void setShapeDeleted(bool _val);
    glm::vec2 getPaintWindowCursorPos() const;
    OpenGLRenderManager& getGLManager();
private:
    GTKManager* m_gtkManager;
    GLFWwindow* m_paintWindow;
    GTKWindow* m_toolWindow;
    OpenGLRenderManager* m_renderManager;
    Args m_startupArgs;

    //State stuf
    State* m_state = nullptr;
public:
    GLFWwindow *getM_paintWindow() const;
    bool isM_isEdited() const;
    bool isM_isDeleted() const;
    shapeInfo &getM_selectedShape();
    GtkWidget *getM_posxBox() const;
    GtkWidget *getM_posyBox() const;
    GtkWidget *getM_sizexBox() const;
    GtkWidget *getM_sizeyBox() const;
    GtkWidget *getM_labelposx() const;
    GtkWidget *getM_labelposy() const;
    GtkWidget *getM_labelsizex() const;
    GtkWidget *getM_labelsizey() const;
    GtkWidget *getM_delete_shape() const;
    GtkWidget *getM_box() const;
    GtkWidget *getM_topBox() const;
    GtkWidget *getM_bottomBox() const;
    GtkWidget *getM_null_mode_button() const;
    GtkWidget *getM_select_and_m_move_button() const;
    GtkWidget *getM_select_and_edit() const;
    GtkWidget *getM_new_rectangle() const;
    GtkWidget *getM_new_ellips() const;
    GtkWidget *getM_acceptBttn() const;
    GtkWidget *getM_infoBox() const;
    GtkWidget *getM_leftColumn() const;
    GtkWidget *getM_rightColumn() const;
private:
    bool m_isEdited = false;
    bool m_isDeleted = false;
    shapeInfo m_selectedShape { nullptr, shapeType::NullType};
    //ToolWindow pointers
    GtkWidget* m_box;
    GtkWidget* m_topBox;
    GtkWidget* m_bottomBox;
    GtkWidget* m_null_mode_button;
    GtkWidget* m_select_and_m_move_button;
    GtkWidget* m_select_and_edit;
    GtkWidget* m_new_rectangle;
    GtkWidget* m_new_ellips;
    GtkWidget* m_acceptBttn;
    GtkWidget* m_infoBox;
    GtkWidget* m_leftColumn;
    GtkWidget* m_rightColumn;
    GtkWidget* m_posxBox;
    GtkWidget* m_posyBox;
    GtkWidget* m_sizexBox;
    GtkWidget* m_sizeyBox;
    GtkWidget* m_labelposx;
    GtkWidget* m_labelposy;
    GtkWidget* m_labelsizex;
    GtkWidget* m_labelsizey;
    GtkWidget* m_delete_shape;
private:
    friend class OpenGLRenderManager;
};

inline void Application::setStartupArgs(Args _args) {
    m_startupArgs = _args;
}

inline Args Application::getStartupArgs() {
    return m_startupArgs;
}

#endif //OPEN_SKETCH_APPLICATION_H
