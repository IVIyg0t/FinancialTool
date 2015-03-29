#include "keyreceive.h"

bool keyReceive::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *key = static_cast<QKeyEvent *>(Event);

        if((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return)){
            //Enter or Return was Pressed
        }
        else{
            return QObject::eventFilter(obj,event);
        }
        return true;
    }
    else{
        return QObject::eventFilter(obj,event);
    }
    return false;
}


//keyReceive::keyReceive(QObject *parent) : QObject(parent)
//{

//}

//keyReceive::~keyReceive()
//{

//}

