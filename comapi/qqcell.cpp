#include "qqcell.h"

QQCell::QQCell()
{
    isOpen = false;
}

void QQCell::setSubtitle(const QString &text){
    if(text.isEmpty()) return;
    subTitle = text;
}

void QQCell::setIconPath(const QString &path){
    if(path.isEmpty()) return;
    iconPath = path;
}

void QQCell::setStatus(const quint8 &val){
    status = val;
}
