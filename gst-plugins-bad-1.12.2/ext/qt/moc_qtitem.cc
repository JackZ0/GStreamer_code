/****************************************************************************
** Meta object code from reading C++ file 'qtitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtGLVideoItem_t {
    QByteArrayData data[7];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGLVideoItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGLVideoItem_t qt_meta_stringdata_QtGLVideoItem = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtGLVideoItem"
QT_MOC_LITERAL(1, 14, 19), // "handleWindowChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 13), // "QQuickWindow*"
QT_MOC_LITERAL(4, 49, 3), // "win"
QT_MOC_LITERAL(5, 53, 23), // "onSceneGraphInitialized"
QT_MOC_LITERAL(6, 77, 23) // "onSceneGraphInvalidated"

    },
    "QtGLVideoItem\0handleWindowChanged\0\0"
    "QQuickWindow*\0win\0onSceneGraphInitialized\0"
    "onSceneGraphInvalidated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGLVideoItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       5,    0,   32,    2, 0x08 /* Private */,
       6,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtGLVideoItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGLVideoItem *_t = static_cast<QtGLVideoItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleWindowChanged((*reinterpret_cast< QQuickWindow*(*)>(_a[1]))); break;
        case 1: _t->onSceneGraphInitialized(); break;
        case 2: _t->onSceneGraphInvalidated(); break;
        default: ;
        }
    }
}

const QMetaObject QtGLVideoItem::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_QtGLVideoItem.data,
      qt_meta_data_QtGLVideoItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtGLVideoItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGLVideoItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtGLVideoItem.stringdata0))
        return static_cast<void*>(const_cast< QtGLVideoItem*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< QtGLVideoItem*>(this));
    return QQuickItem::qt_metacast(_clname);
}

int QtGLVideoItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
