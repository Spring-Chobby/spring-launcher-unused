/****************************************************************************
** Meta object code from reading C++ file 'spring_downloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/spring_downloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spring_downloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SpringDownloader_t {
    QByteArrayData data[11];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpringDownloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpringDownloader_t qt_meta_stringdata_SpringDownloader = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SpringDownloader"
QT_MOC_LITERAL(1, 17, 15), // "downloadStarted"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "name"
QT_MOC_LITERAL(4, 39, 4), // "type"
QT_MOC_LITERAL(5, 44, 16), // "downloadFinished"
QT_MOC_LITERAL(6, 61, 14), // "downloadFailed"
QT_MOC_LITERAL(7, 76, 3), // "msg"
QT_MOC_LITERAL(8, 80, 16), // "downloadProgress"
QT_MOC_LITERAL(9, 97, 7), // "current"
QT_MOC_LITERAL(10, 105, 5) // "total"

    },
    "SpringDownloader\0downloadStarted\0\0"
    "name\0type\0downloadFinished\0downloadFailed\0"
    "msg\0downloadProgress\0current\0total"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpringDownloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    0,   39,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,
       8,    2,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,

       0        // eod
};

void SpringDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpringDownloader *_t = static_cast<SpringDownloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadStarted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->downloadFinished(); break;
        case 2: _t->downloadFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->downloadProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SpringDownloader::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpringDownloader::downloadStarted)) {
                *result = 0;
            }
        }
        {
            typedef void (SpringDownloader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpringDownloader::downloadFinished)) {
                *result = 1;
            }
        }
        {
            typedef void (SpringDownloader::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpringDownloader::downloadFailed)) {
                *result = 2;
            }
        }
        {
            typedef void (SpringDownloader::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpringDownloader::downloadProgress)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject SpringDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SpringDownloader.data,
      qt_meta_data_SpringDownloader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpringDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpringDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpringDownloader.stringdata0))
        return static_cast<void*>(const_cast< SpringDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int SpringDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SpringDownloader::downloadStarted(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpringDownloader::downloadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SpringDownloader::downloadFailed(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpringDownloader::downloadProgress(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
