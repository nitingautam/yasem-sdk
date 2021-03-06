#ifndef CONFIGITEM
#define CONFIGITEM

#include "core.h"

#include <QString>
#include <QVariant>
#include <QList>
#include <QHash>

namespace yasem {

class ConfigImpl;
class CoreImpl;

namespace SDK {

class ConfigTreeGroup;
class Config;

class ConfigItem: public QObject
{
    Q_OBJECT
public:
    enum ItemType {
        CONTAINER, // Internal use only!
        STRING,
        BOOL,
        INT,
        LONG,
        DOUBLE,
        LIST,
        GROUPBOX
    };

    ConfigItem(const QString &key, const QString &title, const QVariant &value = "", ItemType type = STRING);
    virtual ~ConfigItem();

    ItemType getType();
    QVariant getValue();
    QString getTitle();
    QString getKey() const;
    ConfigItem* getParentItem() const;
    QList<ConfigItem*> getItems() const;
    void addItem(ConfigItem* item);
    ConfigItem* item(const QString &key) const;
    void setDirty(bool dirty = true);
    bool isDirty() const;
    QVariant value() const;
    void setValue(const QVariant& value);
    bool isEnabled() const;
    void setEnabled(bool enabled);
    QVariant getDefaultValue() const;
    void reset();
    bool isContainer();
    ConfigItem* findItemByKey(const QString& key);
    ConfigItem* findItemByPath(const QString &path);
    ConfigItem* findItemByPath(const QStringList &path);
signals:
    void reseted();
    void saved();

protected:
    QString m_key;
    QString m_title;
    QVariant m_value;
    QVariant m_default_value;
    ItemType m_type;
    bool m_is_dirty;
    bool m_is_enabled;
    QList<SDK::ConfigItem*> m_items;


friend class Config;
friend class yasem::ConfigImpl;
};

class ListConfigItem: public ConfigItem
{
    Q_OBJECT
public:
    ListConfigItem(const QString &key, const QString &title, const QVariant &value = "");

    QMap<QString, QVariant>& options();
    void setOptions(QMap<QString, QVariant> options);

protected:
    QMap<QString, QVariant> m_options;
};

class ConfigContainer: public ConfigItem
{
    Q_OBJECT
public:
    enum ContainerType {
        ROOT,
        CONFIG_GROUP,
        PAGE
    };


    ConfigContainer(const QString &config_file, const QString& id, const QString &title, ContainerType type);
    virtual ~ConfigContainer();

    ContainerType getContainerType();
    QString getConfigFile() const;

protected:
    ContainerType m_container_type;
    QString m_config_file;
    bool m_is_built_in;


    friend class Config;
    friend class yasem::ConfigImpl;
};

class ConfigTreeGroup: public ConfigContainer {
    Q_OBJECT
public:

    ConfigTreeGroup(const QString &config_file, const QString& id, const QString &title);
    ConfigTreeGroup(const QString& id, const QString &title);
    virtual ~ConfigTreeGroup();

    bool isBuiltInGroup();

protected:

    friend class Config;
    friend class ConfigImpl;
};

class Config: public QObject
{
    Q_OBJECT

public:
    Config(QObject* parent): QObject(parent) {}
    virtual ~Config();

    virtual bool addConfigGroup(ConfigTreeGroup* group) = 0;

    virtual QHash<const QString&, ConfigTreeGroup*> getConfigGroups() = 0;
    virtual ConfigTreeGroup* getDefaultGroup(const QString &id) = 0;

public slots:
    virtual void save(ConfigContainer* container = 0) = 0;
    virtual void reset(ConfigContainer* container = 0) = 0;
    virtual void load(ConfigContainer* container = 0) = 0;
    virtual void setItemDirty(ConfigItem* item, bool value = true) = 0;
    virtual ConfigItem* findItem(const QStringList& path) = 0;
    virtual ConfigItem* findItem(const QString& path) = 0;
protected:
    QHash<const QString&, ConfigTreeGroup*> m_config_groups;
    virtual bool addBuiltInConfigGroup(ConfigTreeGroup* group) = 0;

    friend class Core;
    friend class yasem::CoreImpl;
};

template <typename T, typename N>
T __get_config_item(N name)
{
    return dynamic_cast<T>(Core::instance()->yasem_settings()->findItem(name));
}

}

}

#endif // CONFIGITEM

