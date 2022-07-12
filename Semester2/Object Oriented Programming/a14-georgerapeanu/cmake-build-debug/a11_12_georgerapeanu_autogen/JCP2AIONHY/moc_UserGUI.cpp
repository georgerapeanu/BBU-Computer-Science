/****************************************************************************
** Meta object code from reading C++ file 'UserGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/ui/UserGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserGUI_t {
    QByteArrayData data[14];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserGUI_t qt_meta_stringdata_UserGUI = {
    {
QT_MOC_LITERAL(0, 0, 7), // "UserGUI"
QT_MOC_LITERAL(1, 8, 14), // "logout_clicked"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 19), // "handle_genre_change"
QT_MOC_LITERAL(4, 44, 16), // "reload_highlight"
QT_MOC_LITERAL(5, 61, 11), // "handle_play"
QT_MOC_LITERAL(6, 73, 11), // "handle_next"
QT_MOC_LITERAL(7, 85, 15), // "handle_transfer"
QT_MOC_LITERAL(8, 101, 11), // "handle_like"
QT_MOC_LITERAL(9, 113, 13), // "handle_remove"
QT_MOC_LITERAL(10, 127, 22), // "handle_watchlist_click"
QT_MOC_LITERAL(11, 150, 3), // "row"
QT_MOC_LITERAL(12, 154, 13), // "handle_logout"
QT_MOC_LITERAL(13, 168, 24) // "handle_display_watchlist"

    },
    "UserGUI\0logout_clicked\0\0handle_genre_change\0"
    "reload_highlight\0handle_play\0handle_next\0"
    "handle_transfer\0handle_like\0handle_remove\0"
    "handle_watchlist_click\0row\0handle_logout\0"
    "handle_display_watchlist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    1,   77,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UserGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logout_clicked(); break;
        case 1: _t->handle_genre_change(); break;
        case 2: _t->reload_highlight(); break;
        case 3: _t->handle_play(); break;
        case 4: _t->handle_next(); break;
        case 5: _t->handle_transfer(); break;
        case 6: _t->handle_like(); break;
        case 7: _t->handle_remove(); break;
        case 8: _t->handle_watchlist_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->handle_logout(); break;
        case 10: _t->handle_display_watchlist(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserGUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserGUI::logout_clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserGUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_UserGUI.data,
    qt_meta_data_UserGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserGUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void UserGUI::logout_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
