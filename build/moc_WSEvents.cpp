/****************************************************************************
** Meta object code from reading C++ file 'WSEvents.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/WSEvents.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WSEvents.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WSEvents_t {
    QByteArrayData data[11];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WSEvents_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WSEvents_t qt_meta_stringdata_WSEvents = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WSEvents"
QT_MOC_LITERAL(1, 9, 22), // "deferredInitOperations"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "StreamStatus"
QT_MOC_LITERAL(4, 46, 9), // "Heartbeat"
QT_MOC_LITERAL(5, 56, 25), // "TransitionDurationChanged"
QT_MOC_LITERAL(6, 82, 2), // "ms"
QT_MOC_LITERAL(7, 85, 20), // "SelectedSceneChanged"
QT_MOC_LITERAL(8, 106, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 123, 7), // "current"
QT_MOC_LITERAL(10, 131, 4) // "prev"

    },
    "WSEvents\0deferredInitOperations\0\0"
    "StreamStatus\0Heartbeat\0TransitionDurationChanged\0"
    "ms\0SelectedSceneChanged\0QListWidgetItem*\0"
    "current\0prev"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WSEvents[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    2,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,

       0        // eod
};

void WSEvents::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WSEvents *_t = static_cast<WSEvents *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deferredInitOperations(); break;
        case 1: _t->StreamStatus(); break;
        case 2: _t->Heartbeat(); break;
        case 3: _t->TransitionDurationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SelectedSceneChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject WSEvents::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WSEvents.data,
      qt_meta_data_WSEvents,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WSEvents::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WSEvents::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WSEvents.stringdata0))
        return static_cast<void*>(const_cast< WSEvents*>(this));
    return QObject::qt_metacast(_clname);
}

int WSEvents::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
