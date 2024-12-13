INCLUDEPATH +=  $$PWD
DEPENDPATH  +=  $$PWD

INCLUDEPATH  +=  $$PWD/qqlist
INCLUDEPATH  +=  $$PWD/qqlist  $$PWD/picture

include($$PWD/QQCell/QQCell.pri)

HEADERS += \
    $$PWD/animationstackedwidget.h \
    $$PWD/chatbubble.h \
    $$PWD/customwidget.h \
    $$PWD/pictureedit/cutdialog.h \
    $$PWD/pictureedit/photoshotdialog.h \
    $$PWD/pictureedit/pictureeditwidget.h \
    $$PWD/rotatestackedwidget.h \
    $$PWD/customedit.h

SOURCES += \
    $$PWD/animationstackedwidget.cpp \
    $$PWD/chatbubble.cpp \
    $$PWD/customwidget.cpp \
    $$PWD/pictureedit/cutdialog.cpp \
    $$PWD/pictureedit/photoshotdialog.cpp \
    $$PWD/pictureedit/pictureeditwidget.cpp \
    $$PWD/rotatestackedwidget.cpp \
    $$PWD/customedit.cpp


FORMS += \
    $$PWD/pictureedit/pictureeditwidget.ui 