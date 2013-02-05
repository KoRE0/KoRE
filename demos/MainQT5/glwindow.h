#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>

class GLWindow : public QWindow
{
    Q_OBJECT

public:
    GLWindow(QScreen* screen = 0);
    ~GLWindow();

protected:
    void keyPressEvent(QKeyEvent * evnt);

private:
    void initializeGL();

protected slots:
    void resizeGL();
    void paintGL();
    void updateScene();

private:
    QOpenGLContext* _context;

};
#endif // MAINWINDOW_H