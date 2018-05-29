/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      26,   11,   11,   11, 0x08,
      39,   11,   11,   11, 0x08,
      53,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      75,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     142,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     174,  168,  164,   11, 0x08,
     213,  205,  197,   11, 0x08,
     241,  237,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0sendMessage()\0proceedCmd()\0"
    "funcConnect()\0funcQuit()\0funcJoin()\0"
    "funcNick()\0funcUsers()\0funcPart()\0"
    "funcNames()\0funcMsg()\0funcFile()\0"
    "funcUser()\0funcList()\0int\0c,str\0"
    "findPos(char,QString&)\0QString\0pos,str\0"
    "cutString(int,QString&)\0str\0"
    "printUsers(QString&)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->sendMessage(); break;
        case 1: _t->proceedCmd(); break;
        case 2: _t->funcConnect(); break;
        case 3: _t->funcQuit(); break;
        case 4: _t->funcJoin(); break;
        case 5: _t->funcNick(); break;
        case 6: _t->funcUsers(); break;
        case 7: _t->funcPart(); break;
        case 8: _t->funcNames(); break;
        case 9: _t->funcMsg(); break;
        case 10: _t->funcFile(); break;
        case 11: _t->funcUser(); break;
        case 12: _t->funcList(); break;
        case 13: { int _r = _t->findPos((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->cutString((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: _t->printUsers((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
