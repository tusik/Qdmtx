include(include.pri)
#QT -= gui

TEMPLATE = lib
DEFINES += QDMTX_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/qdmtx.cpp \
    src/qdmtxdata.cpp \
    thirdpart/libdmtx/dmtx.c \
    thirdpart/libdmtx/dmtxbytelist.c \
    thirdpart/libdmtx/dmtxdecode.c \
    thirdpart/libdmtx/dmtxdecodescheme.c \
    thirdpart/libdmtx/dmtxencode.c \
    thirdpart/libdmtx/dmtxencodeascii.c \
    thirdpart/libdmtx/dmtxencodebase256.c \
    thirdpart/libdmtx/dmtxencodec40textx12.c \
    thirdpart/libdmtx/dmtxencodeedifact.c \
    thirdpart/libdmtx/dmtxencodeoptimize.c \
    thirdpart/libdmtx/dmtxencodescheme.c \
    thirdpart/libdmtx/dmtxencodestream.c \
    thirdpart/libdmtx/dmtximage.c \
    thirdpart/libdmtx/dmtxmatrix3.c \
    thirdpart/libdmtx/dmtxmessage.c \
    thirdpart/libdmtx/dmtxplacemod.c \
    thirdpart/libdmtx/dmtxreedsol.c \
    thirdpart/libdmtx/dmtxregion.c \
    thirdpart/libdmtx/dmtxscangrid.c \
    thirdpart/libdmtx/dmtxsymbol.c \
    thirdpart/libdmtx/dmtxtime.c \
    thirdpart/libdmtx/dmtxvector2.c

HEADERS += \
    include/Qdmtx_global.h \
    include/qdmtx.h \
    include/qdmtxdata.h \
    thirdpart/libdmtx/dmtx.h \
    thirdpart/libdmtx/dmtxstatic.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


DESTDIR = ../../bin
INCLUDEPATH += thirdpart/libdmtx
INCLUDEPATH += include
