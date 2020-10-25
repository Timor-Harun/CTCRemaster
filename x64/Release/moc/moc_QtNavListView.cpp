/****************************************************************************
** Meta object code from reading C++ file 'QtNavListView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../QtNavListView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtNavListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtNavListView_t {
    QByteArrayData data[20];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtNavListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtNavListView_t qt_meta_stringdata_QtNavListView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtNavListView"
QT_MOC_LITERAL(1, 14, 8), // "readData"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "xmlFileName"
QT_MOC_LITERAL(4, 36, 7), // "setData"
QT_MOC_LITERAL(5, 44, 8), // "listItem"
QT_MOC_LITERAL(6, 53, 14), // "setInfoVisible"
QT_MOC_LITERAL(7, 68, 7), // "visible"
QT_MOC_LITERAL(8, 76, 14), // "setLineVisible"
QT_MOC_LITERAL(9, 91, 17), // "setIconBgcVisible"
QT_MOC_LITERAL(10, 109, 12), // "setIconStyle"
QT_MOC_LITERAL(11, 122, 9), // "IconStyle"
QT_MOC_LITERAL(12, 132, 5), // "style"
QT_MOC_LITERAL(13, 138, 12), // "setLineColor"
QT_MOC_LITERAL(14, 151, 5), // "color"
QT_MOC_LITERAL(15, 157, 12), // "setBackColor"
QT_MOC_LITERAL(16, 170, 11), // "normalColor"
QT_MOC_LITERAL(17, 182, 13), // "selectedColor"
QT_MOC_LITERAL(18, 196, 10), // "hoverColor"
QT_MOC_LITERAL(19, 207, 12) // "setTextColor"

    },
    "QtNavListView\0readData\0\0xmlFileName\0"
    "setData\0listItem\0setInfoVisible\0visible\0"
    "setLineVisible\0setIconBgcVisible\0"
    "setIconStyle\0IconStyle\0style\0setLineColor\0"
    "color\0setBackColor\0normalColor\0"
    "selectedColor\0hoverColor\0setTextColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtNavListView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       6,    1,   65,    2, 0x0a /* Public */,
       8,    1,   68,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      13,    1,   77,    2, 0x0a /* Public */,
      15,    3,   80,    2, 0x0a /* Public */,
      19,    3,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QColor,   14,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor, QMetaType::QColor,   16,   17,   18,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor, QMetaType::QColor,   16,   17,   18,

       0        // eod
};

void QtNavListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtNavListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setData((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->setInfoVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setLineVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setIconBgcVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setIconStyle((*reinterpret_cast< IconStyle(*)>(_a[1]))); break;
        case 6: _t->setLineColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 7: _t->setBackColor((*reinterpret_cast< const QColor(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3]))); break;
        case 8: _t->setTextColor((*reinterpret_cast< const QColor(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< const QColor(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtNavListView::staticMetaObject = { {
    QMetaObject::SuperData::link<QListView::staticMetaObject>(),
    qt_meta_stringdata_QtNavListView.data,
    qt_meta_data_QtNavListView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtNavListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtNavListView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtNavListView.stringdata0))
        return static_cast<void*>(this);
    return QListView::qt_metacast(_clname);
}

int QtNavListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
struct qt_meta_stringdata_QtNavListModel_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtNavListModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtNavListModel_t qt_meta_stringdata_QtNavListModel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QtNavListModel"
QT_MOC_LITERAL(1, 15, 8), // "readData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "xmlFileName"
QT_MOC_LITERAL(4, 37, 8), // "setItems"
QT_MOC_LITERAL(5, 46, 8), // "listItem"
QT_MOC_LITERAL(6, 55, 8), // "collapse"
QT_MOC_LITERAL(7, 64, 11), // "QModelIndex"
QT_MOC_LITERAL(8, 76, 5) // "index"

    },
    "QtNavListModel\0readData\0\0xmlFileName\0"
    "setItems\0listItem\0collapse\0QModelIndex\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtNavListModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void QtNavListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtNavListModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setItems((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->collapse((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtNavListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_QtNavListModel.data,
    qt_meta_data_QtNavListModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtNavListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtNavListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtNavListModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int QtNavListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_QtNavListDelegate_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtNavListDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtNavListDelegate_t qt_meta_stringdata_QtNavListDelegate = {
    {
QT_MOC_LITERAL(0, 0, 17) // "QtNavListDelegate"

    },
    "QtNavListDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtNavListDelegate[] = {

 // content:
       8,       // revision
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

void QtNavListDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QtNavListDelegate::staticMetaObject = { {
    QMetaObject::SuperData::link<QStyledItemDelegate::staticMetaObject>(),
    qt_meta_stringdata_QtNavListDelegate.data,
    qt_meta_data_QtNavListDelegate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtNavListDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtNavListDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtNavListDelegate.stringdata0))
        return static_cast<void*>(this);
    return QStyledItemDelegate::qt_metacast(_clname);
}

int QtNavListDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
