/********************************************************************************
** Form generated from reading UI file 'TextureEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREEDITOR_H
#define UI_TEXTUREEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureEditor
{
public:

    void setupUi(QWidget *TextureEditor)
    {
        if (TextureEditor->objectName().isEmpty())
            TextureEditor->setObjectName(QStringLiteral("TextureEditor"));
        TextureEditor->resize(400, 300);

        retranslateUi(TextureEditor);

        QMetaObject::connectSlotsByName(TextureEditor);
    } // setupUi

    void retranslateUi(QWidget *TextureEditor)
    {
        TextureEditor->setWindowTitle(QApplication::translate("TextureEditor", "TextureEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class TextureEditor: public Ui_TextureEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREEDITOR_H
