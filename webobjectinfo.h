#ifndef WEBOBJECTINFO_H
#define WEBOBJECTINFO_H

#include <QString>
#include <QList>
#include <QSharedPointer>

#include <functional>

class QWidget;

namespace yasem {
namespace SDK {

typedef std::function<QWidget* ()> WidgetFactory;

struct WebObjectInfo {
    QString name;
    QWidget* webObject;
    QString mimeType;
    QList<QString> fileExtensions;
    QString description;
    QString classid;
    WidgetFactory widgetFactory;
};

}

}



#endif // WEBOBJECTINFO_H
