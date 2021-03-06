#ifndef DISKINFO_H
#define DISKINFO_H

#include <QObject>
#include <QString>
#include <QStringList>

namespace yasem {
namespace SDK {

class StorageInfo {
public:
    int index;
    QString blockDevice;
    QString mountPoint;
    int percentComplete;
    qint64 size;
    qint64 used;
    qint64 available;
    QString model;
    QString vendor;
    bool writable = true;
    QString m_file_system;

    QString toString();

};

enum ConnectionInterface {
    NONE,
    IDE,
    SATA
};

enum BlockDeviceType {
    DEVICE_TYPE_UNKNOWN,
    DEVICE_TYPE_DISK,
    DEVICE_TYPE_PARTITION,
    DEVICE_TYPE_CD_ROM
};

enum HwinfoLineTypes {
    TITLE,
    HARDWARE_CLASS,
    UNIQUE_ID,
    PARENT_ID,
    SYS_FS_ID,
    MODEL,
    VENDOR,
    DEVICE,
    REVISION,
    DEVICE_FILE
};

class BlockDeviceInfo: public QObject
{
    Q_OBJECT
public:
    BlockDeviceInfo(QObject* parent = 0);
    virtual ~BlockDeviceInfo();
    int m_index;
    ConnectionInterface m_conn_interface;
    BlockDeviceType m_hardware_type;
    QString unique_id;
    QString parent_id;
    QString sys_fs_id;
    QString model;
    QString vendor;
    QString device;
    QString revision;
    QStringList drivers;
    QString device_file;

    QString toString();

    QList<BlockDeviceInfo*> children;
};

}

}





#endif // DISKINFO_H
