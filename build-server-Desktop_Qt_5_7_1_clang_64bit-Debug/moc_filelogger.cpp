/****************************************************************************
** Meta object code from reading C++ file 'filelogger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QtWebApp/logging/filelogger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filelogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_amiltonjunior__FileLogger_t {
    QByteArrayData data[1];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_amiltonjunior__FileLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_amiltonjunior__FileLogger_t qt_meta_stringdata_amiltonjunior__FileLogger = {
    {
QT_MOC_LITERAL(0, 0, 25) // "amiltonjunior::FileLogger"

    },
    "amiltonjunior::FileLogger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_amiltonjunior__FileLogger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void amiltonjunior::FileLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject amiltonjunior::FileLogger::staticMetaObject = {
    { &Logger::staticMetaObject, qt_meta_stringdata_amiltonjunior__FileLogger.data,
      qt_meta_data_amiltonjunior__FileLogger,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *amiltonjunior::FileLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *amiltonjunior::FileLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_amiltonjunior__FileLogger.stringdata0))
        return static_cast<void*>(const_cast< FileLogger*>(this));
    return Logger::qt_metacast(_clname);
}

int amiltonjunior::FileLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Logger::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
