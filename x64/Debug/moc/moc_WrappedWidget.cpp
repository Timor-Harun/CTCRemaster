/****************************************************************************
** Meta object code from reading C++ file 'WrappedWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../WrappedWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WrappedWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WrappedWidget_t {
    QByteArrayData data[13];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WrappedWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WrappedWidget_t qt_meta_stringdata_WrappedWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WrappedWidget"
QT_MOC_LITERAL(1, 14, 23), // "signal_ButtonClickEvent"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "objectName"
QT_MOC_LITERAL(4, 50, 19), // "signal_EditFinished"
QT_MOC_LITERAL(5, 70, 27), // "signal_CheckBoxStageChanged"
QT_MOC_LITERAL(6, 98, 32), // "signal_TableSelectedIndexChanged"
QT_MOC_LITERAL(7, 131, 3), // "row"
QT_MOC_LITERAL(8, 135, 26), // "signal_SpinBoxValueChanged"
QT_MOC_LITERAL(9, 162, 5), // "value"
QT_MOC_LITERAL(10, 168, 25), // "signal_ButtonGroupToggled"
QT_MOC_LITERAL(11, 194, 5), // "index"
QT_MOC_LITERAL(12, 200, 12) // "signal_close"

    },
    "WrappedWidget\0signal_ButtonClickEvent\0"
    "\0objectName\0signal_EditFinished\0"
    "signal_CheckBoxStageChanged\0"
    "signal_TableSelectedIndexChanged\0row\0"
    "signal_SpinBoxValueChanged\0value\0"
    "signal_ButtonGroupToggled\0index\0"
    "signal_close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WrappedWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,
       6,    2,   58,    2, 0x06 /* Public */,
       8,    2,   63,    2, 0x06 /* Public */,
      10,    3,   68,    2, 0x06 /* Public */,
      12,    0,   75,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    3,   11,    9,
    QMetaType::Void,

       0        // eod
};

void WrappedWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WrappedWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_ButtonClickEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->signal_EditFinished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->signal_CheckBoxStageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->signal_TableSelectedIndexChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->signal_SpinBoxValueChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signal_ButtonGroupToggled((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: _t->signal_close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WrappedWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_ButtonClickEvent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_EditFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_CheckBoxStageChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_TableSelectedIndexChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_SpinBoxValueChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)(const QString & , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_ButtonGroupToggled)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WrappedWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WrappedWidget::signal_close)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WrappedWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WrappedWidget.data,
    qt_meta_data_WrappedWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WrappedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WrappedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WrappedWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WrappedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WrappedWidget::signal_ButtonClickEvent(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WrappedWidget::signal_EditFinished(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WrappedWidget::signal_CheckBoxStageChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WrappedWidget::signal_TableSelectedIndexChanged(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WrappedWidget::signal_SpinBoxValueChanged(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WrappedWidget::signal_ButtonGroupToggled(const QString & _t1, int _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WrappedWidget::signal_close()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
