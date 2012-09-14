TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    sf_v8.cpp \
    v8wrap.cpp \
    character.cpp

OTHER_FILES += \
    build.sh \
    build/build.sh \
    build/clean.sh \
    CMakeLists.txt \
    .gitignore \
    build/cmake/modules/FindSFML.cmake \
    build/clean-dsstore.sh \
    ResourcePath.mm \
    js/robot1.js

HEADERS += \
    v8wrap.h \
    sf_v8.h \
    ResourcePath.hpp \
    character.h

