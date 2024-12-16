INCLUDEPATH +=  $$PWD
DEPENDPATH  +=  $$PWD

HEADERS += \
    $$files($$PWD/*.h) 
    
SOURCES += \
    $$files($$PWD/*.cc)

FORMS += \
    $$files($$PWD/*.ui)