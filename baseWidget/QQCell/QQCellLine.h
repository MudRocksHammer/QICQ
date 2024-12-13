#pragma once

#include <QString>

class Cell
{
public:
    enum CellRole
    {
        NameRole = Qt::UserRole + 1,
        HeadRole,
        StateRole,
        StaPicRole,
        TimeStampRole,
        CtrlPicRole
    };
    Cell(const QString &name, const QString &head, const QString &state, const QString &staPic, const QString &lastTime, const QString &ctrl) : name(name), head(head), state(state), staPic(staPic), lastTime(lastTime), ctrlPic(ctrl) {}
    Cell() : name(), head(), state(), staPic(), lastTime(), ctrlPic() {}

    QString getName() const
    {
        return name;
    }
    QString getHead() const
    {
        return head;
    }
    QString getState() const
    {
        return state;
    }
    QString getStaPic() const
    {
        return staPic;
    }
    QString getLastTime() const
    {
        return lastTime;
    }
    QString getCtrlPic() const
    {
        return ctrlPic;
    }

    void setName(const QString &name)
    {
        this->name = name;
    }
    void setHead(const QString &head)
    {
        this->head = head;
    }
    void setState(const QString &state)
    {
        this->state = state;
    }
    void setStaPic(const QString &staPic)
    {
        this->staPic = staPic;
    }
    void setLastTime(const QString &last)
    {
        this->lastTime = last;
    }
    void setCtrlPic(const QString &ctrl)
    {
        this->ctrlPic = ctrl;
    }

private:
    QString name, head, state, staPic, lastTime, ctrlPic;
};