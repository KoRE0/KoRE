/****************************************************************************
** Meta object code from reading C++ file 'RenderViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RenderViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_koregui__RenderViewer_t {
<<<<<<< HEAD
    QByteArrayData data[4];
    char stringdata[39];
=======
    QByteArrayData data[8];
    char stringdata[104];
>>>>>>> hax
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_koregui__RenderViewer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_koregui__RenderViewer_t qt_meta_stringdata_koregui__RenderViewer = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 6),
QT_MOC_LITERAL(2, 29, 0),
<<<<<<< HEAD
QT_MOC_LITERAL(3, 30, 7)
    },
    "koregui::RenderViewer\0zoomIn\0\0zoomOut\0"
=======
QT_MOC_LITERAL(3, 30, 7),
QT_MOC_LITERAL(4, 38, 14),
QT_MOC_LITERAL(5, 53, 16),
QT_MOC_LITERAL(6, 70, 15),
QT_MOC_LITERAL(7, 86, 16)
    },
    "koregui::RenderViewer\0zoomIn\0\0zoomOut\0"
    "createFBOStage\0createShaderPass\0"
    "createEmptyNode\0createEmptyGroup\0"
>>>>>>> hax
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_koregui__RenderViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
       2,   14, // methods
=======
       6,   14, // methods
>>>>>>> hax
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
<<<<<<< HEAD
       1,    0,   24,    2, 0x0a,
       3,    0,   25,    2, 0x0a,
=======
       1,    0,   44,    2, 0x0a,
       3,    0,   45,    2, 0x0a,
       4,    0,   46,    2, 0x0a,
       5,    0,   47,    2, 0x0a,
       6,    0,   48,    2, 0x0a,
       7,    0,   49,    2, 0x0a,
>>>>>>> hax

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
=======
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
>>>>>>> hax

       0        // eod
};

void koregui::RenderViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderViewer *_t = static_cast<RenderViewer *>(_o);
        switch (_id) {
        case 0: _t->zoomIn(); break;
        case 1: _t->zoomOut(); break;
<<<<<<< HEAD
=======
        case 2: _t->createFBOStage(); break;
        case 3: _t->createShaderPass(); break;
        case 4: _t->createEmptyNode(); break;
        case 5: _t->createEmptyGroup(); break;
>>>>>>> hax
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject koregui::RenderViewer::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_koregui__RenderViewer.data,
      qt_meta_data_koregui__RenderViewer,  qt_static_metacall, 0, 0}
};


const QMetaObject *koregui::RenderViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *koregui::RenderViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_koregui__RenderViewer.stringdata))
        return static_cast<void*>(const_cast< RenderViewer*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int koregui::RenderViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< HEAD
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
=======
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
>>>>>>> hax
    }
    return _id;
}
QT_END_MOC_NAMESPACE
