#ifndef CORE_H
#define CORE_H

#include "enums.h"
#include "diskinfo.h"
#include "gui.h"

#include <functional>
#include <stdio.h>

// Includes for backtrace
#ifdef Q_OS_UNIX
#include <execinfo.h>
#endif // defined(Q_OS_UNIX)

#include <QObject>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <QMetaType>
#include <QThread>
#include <QRegularExpression>

#define CONFIG_NAME "config.ini"
#define CONFIG_PROFILES_DIR "profiles"


#define CALLSTACK_SIZE 2048

namespace yasem {
namespace SDK {
class StorageInfo;
class Config;
class Statistics;
class BlockDeviceInfo;
class CoreNetwork;

class Core: public QObject
{
    Q_OBJECT
    Q_ENUMS(VirtualMachine)
public:
    enum VirtualMachine
    {
        VM_NOT_SET, // VM value is not set yet
        VM_NONE,
        VM_UNKNOWN,
        VM_VIRTUAL_BOX,
        VM_VMWARE
    };

    enum Feature {
        FEATURE_OPENGL = 1
    };

    Q_DECLARE_FLAGS(Features, Feature)

    static Core* setInstance(Core* inst = 0)
    {
        static Core* instance = inst;

        if(instance == NULL)
            instance = static_cast<Core*>(qApp->property("Core").value<QObject*>());

        Q_CHECK_PTR(instance);
        return instance;
    }

    static Core* instance()
    {
        return setInstance();
    }

    virtual void init() = 0;

    virtual QSettings* settings() = 0;
    virtual QSettings* settings(const QString &filename) = 0;
    virtual Config* yasem_settings() const = 0;

    virtual QList<StorageInfo*> storages() = 0;
    virtual CoreNetwork* network() const = 0;
    virtual Statistics* statistics() const = 0;
    virtual VirtualMachine getVM() = 0;

    virtual QThread* mainThread() = 0;
    virtual bool featureAvailable(const Feature feature) const = 0;

    static void printCallStack()
    {
        #ifdef Q_OS_UNIX
            //print call stack (needs #include <execinfo.h>)
            void* callstack[CALLSTACK_SIZE];
            int i, frames = backtrace(callstack, CALLSTACK_SIZE);
            char** strs = backtrace_symbols(callstack, frames);

            printf("\nCallstack:\n");

            for(i = 0; i < frames; i++){
                printf("%d: %s\n", i, strs[i]);
            }
            free(strs);
        #else
            printf("[FIXME]: printCallStack() is only supported in desktop Unix-based systems\n");
        #endif // Q_OS_UNIX
    }

    virtual QString version() const = 0;
    virtual QString revision() const = 0;
    virtual QString compiler() const = 0;
    QHash<QString, BlockDeviceInfo*> getBlockDeviceTree() {
        return block_device_tree;
    }
    virtual QString getConfigDir() const = 0;
    virtual QHash<QString, QString> arguments() const = 0;

protected:
    Core(QObject* parent): QObject(parent){}
    Core(Core const&);

    virtual void parseCommandLineArgs() = 0;

    QHash<QString, GUI::RcKey> keycode_hashes;
    QHash<QString, BlockDeviceInfo*> block_device_tree;
    QHash<HwinfoLineTypes, QRegularExpression> hwinfo_regex_list;
private:

    void operator=(Core const&);
signals:
    void methodNotImplemented(const QString &name);

public slots:
    virtual void onClose() = 0;
    virtual void mountPointChanged() = 0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Core::Features)

}

}

#endif // CORE_H
