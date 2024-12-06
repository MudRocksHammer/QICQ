#ifndef QQCELL_H
#define QQCELL_H

#include <QString>
#include <QList>

typedef enum tagQQCellType_e{
    QQCellType_Group = 0,
    QQCellType_Child,
    QQCellType_GroupEx,
} QQCellType_e;

class QQCell
{
public:
    QQCell();

    void setSubtitle(const QString& text);
    void setIconPath(const QString& path);
    void setStatus(const quint8& val);

public:
    QString iconPath;
    QString name;
    QString subTitle;

    QString ipAddr;
    QString groupName;      //组名
    int id;                 //qq号
    int status;

    //
    QQCellType_e type;

    //下面几项用于组(QQCellType_Group)状态, 对于子(QQCellType_Child)状态无用
    //是否打开状态
    bool isOpen;
    //子项
    QList<QQCell*> childs;
};

#endif // QQCELL_H
