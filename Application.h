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

#include <iostream>
#include "includeLibs.h"
#include "GTK/GTKManager.h"
#include "GTK/GTKWindow.h"

//prototypes
class OpenGLRenderManager;


//Args struct
struct Args
{
    int m_argc = 0;
    char** m_argv = nullptr;
};

class Application {
public:
    static Application& getInstance();
private:
    Application();
public:
    Application(const Application&) = delete;
    Application(const Application&&) = delete;
    void operator=(const Application&) = delete;
    void operator=(const Application&&) = delete;
    ~Application();
private:
    bool initGLFW();
    bool initGLEW();
    void initGTK();
public:
    void initialize();
    void run();
    void getPaintWindowSize(int& _width, int& _height);
    inline void setStartupArgs(Args _args);
    inline Args getStartupArgs();
private:
    GTKManager* m_gtkManager;
    GLFWwindow* m_paintWindow;
    GTKWindow* m_toolWindow;
    OpenGLRenderManager* m_renderManager;
    Args m_startupArgs;
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
