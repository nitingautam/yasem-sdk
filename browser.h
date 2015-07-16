#ifndef BROWSERPLUGIN_H
#define BROWSERPLUGIN_H

#include "enums.h"
#include "abstractpluginobject.h"
#include "gui.h"

#include <QSize>
#include <QObject>
#include <QMetaMethod>

class QRect;
class QUrl;
class QResizeEvent;
class QWidget;
class QEvent;

namespace yasem {
namespace SDK {
class StbPluginObject;
class CustomKeyEvent;
class WebPage;

class Browser: public AbstractPluginObject
{
    Q_OBJECT
public:
    Browser(Plugin* plugin): AbstractPluginObject(plugin){}
    virtual ~Browser(){
        m_use_qml = false;
    }

    enum TopWidget {
        TOP_WIDGET_BROWSER,
        TOP_WIDGET_PLAYER
    };

    virtual void setParentWidget(QWidget *parent) = 0;
    virtual QWidget* getParentWidget() = 0;
    virtual QWidget* widget() = 0 ;
    virtual void resize(QResizeEvent* = 0) = 0;
    virtual void rect(const QRect &rect) = 0;
    virtual QRect rect() = 0;
    virtual void scale(qreal scale) = 0;
    virtual qreal scale() = 0;
    virtual void stb(StbPluginObject* stbPlugin) = 0;
    virtual StbPluginObject* stb() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void fullscreen(bool setFullscreen) = 0;
    virtual bool fullscreen() = 0;

    virtual QUrl url() = 0;
    virtual QString browserRootDir() = 0;
    virtual void setUserAgent(const QString &userAgent) = 0;
    virtual void addFont(const QString &fileName) = 0;
    virtual void registerKeyEvent(GUI::RcKey rc_key, int keyCode) = 0;
    virtual void registerKeyEvent(GUI::RcKey rc_key, int keyCode, int which, bool alt = false, bool ctrl = false, bool shift = false) = 0;
    virtual void registerKeyEvent(GUI::RcKey rc_key, int keyCode, int which, int keyCode2, int which2, bool alt = false, bool ctrl = false, bool shift = false) = 0;
    virtual void clearKeyEvents() = 0;
    virtual void passEvent(QEvent *event) = 0;

    virtual void setupMousePositionHandler(const QObject *receiver, const char* method) = 0;

    virtual WebPage* getFirstPage() = 0;

    virtual QString getQmlComponentName() { return ""; }

    virtual WebPage* createNewPage(bool child = false) = 0;
    virtual WebPage* getActiveWebPage() = 0;

    virtual void setUseQml(bool use) { m_use_qml = use; }
    virtual bool isUsingQml() const { return m_use_qml; }


    virtual void setTopWidget(TopWidget top) {
        m_top_widget = top;
        emit topWidgetChanged();
    }
    virtual TopWidget getTopWidget() { return m_top_widget; }

protected:
    QWidget* activeWebView;
    bool m_use_qml;
    TopWidget m_top_widget;

Q_SIGNALS:
    void topWidgetChanged();

};
}
}

#endif // BROWSERPLUGIN_H