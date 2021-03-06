VERSION = 0.1.0
TARGET = yasem-sdk
TEMPLATE = lib

include($${top_srcdir}/common.pri) 

QT += core widgets network
equals(QT_MAJOR_VERSION, 5): {
    QT -= gui
}

INCLUDEPATH += ./
DEPENDPATH += ./

SOURCES += \
    plugin.cpp \
    yasemsettings.cpp \
    sambanode.cpp \
    diskinfo.cpp \
    gui.cpp \
    plugindependency.cpp \
    pluginmanager.cpp \
    browser.cpp \
    abstractpluginobject.cpp \
    profilemanager.cpp \
    datasourcefactory.cpp \
    datasource.cpp \
    datasourceclass.cpp \
    webpage.cpp \
    timeshift.cpp \
    webpage_p.cpp \
    utils.cpp

HEADERS += \
    plugin.h \
    plugin_p.h \
    core.h \
    statistics.h \
    networkstatistics.h \
    pluginmanager.h \
    profilemanager.h \
    crashhandler.h \
    macros.h \
    enums.h \
    core-network.h \
    samba.h \
    sambanode.h \
    plugindependency.h \
    profile_config_parser.h \
    webobjectinfo.h \
    stbsubmodel.h \
    systemstatistics.h \
    mediaplayer.h \
    browser.h \
    webpage.h \
    gui.h \
    yasemsettings.h \
    datasourcefactory.h \
    datasource.h \
    datasourceclass.h \
    timeshift.h \
    webpage_p.h \
    utils.h

# Plugin headers

SOURCES += \
    abstracthttpproxy.cpp \
    stbpluginobject.cpp \
    webserverplugin.cpp \
    mediaplayerpluginobject.cpp \
    stbprofile.cpp

HEADERS += \
    abstractpluginobject.h \
    abstracthttpproxy.h \
    abstracthttpproxy_p.h \
    webserverplugin.h \
    webserverplugin_p.h \
    stbpluginobject.h \
    stbpluginobject_p.h \
    diskinfo.h \
    customkeyevent.h \
    stbprofile.h

OTHER_FILES += \
    LICENSE \
    README.md \

DISTFILES += \
    LICENSE
