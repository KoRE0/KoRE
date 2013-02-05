#include "glwindow.h"
#include <gl/glew.h>

#include <QGuiApplication>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QTimer>
#include <string>

#include "KoRE/Shader.h"
#include "KoRE/Components/Mesh.h"
#include "KoRE/Operations/RenderMesh.h"
#include "KoRE/ResourceManager.h"
#include "KoRE/RenderManager.h"

GLWindow::GLWindow(QScreen* screen) 
    : QWindow(screen)
{
    setSurfaceType(OpenGLSurface);

    QSurfaceFormat sformat;
    sformat.setDepthBufferSize(24);
    sformat.setMajorVersion(4);
    sformat.setMinorVersion(3);
    //sformat.setSamples(4);        MSAA
    sformat.setProfile(QSurfaceFormat::CoreProfile);

    resize(800,600);
    setFormat(sformat);
    create();

    _context = new QOpenGLContext;
    _context->setFormat(sformat);
    _context->create();

    glewInit();

    initializeGL();
    connect(this,SIGNAL(widthChanged(int)), this, SLOT(resizeGL()));
    connect(this,SIGNAL(heightChanged(int)), this, SLOT(resizeGL()));
    resizeGL();

    QTimer* timer = new QTimer(this);
}

GLWindow::~GLWindow()
{

}

void GLWindow::initializeGL()
{
    _context->makeCurrent(this);
   
    kore::Log::getInstance()->write(
        "Render Device: %s\n",
        reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    kore::Log::getInstance()->write(
        "Vendor: %s\n",
        reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    kore::Log::getInstance()->write(
        "OpenGL version: %s\n",
        reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    kore::Log::getInstance()->write(
        "GLSL version: %s\n",
        reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

void GLWindow::resizeGL()
{
    _context->makeCurrent(this);
    //resize scene(width(),height());
}

void GLWindow::paintGL()
{
    _context->makeCurrent(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    kore::RenderManager::getInstance()->renderFrame();

    _context->swapBuffers(this);
}

void GLWindow::updateScene()
{
    //update scene
    paintGL();
}

void GLWindow::keyPressEvent(QKeyEvent * evnt)
{
    if (evnt->key() == Qt::Key_Escape) QGuiApplication::quit();
}
