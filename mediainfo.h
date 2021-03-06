#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QString>

namespace yasem
{

struct AudioLangInfo {
    int m_pid;
    QString m_code2; // ISO 639-1
    QString m_code3; // ISO 639-2

    AudioLangInfo(int pid, const QString& code2, const QString code3)
    {
        this->m_pid = pid;
        this->m_code2 = code2;
        this->m_code3 = code3;
    }
};

struct MediaMetadata {
    QString album;
    QString album_artist;
    QString artist;
    QString comment;
    QString composer;
    QString copyright;
    QString date;
    QString disk;
    QString encoder;
    QString encoded_by;
    QString filename;
    QString genre;
    QString language;
    QString performer;
    QString publisher;
    QString title;
    QString track;
};

}

#endif // MEDIAINFO_H

