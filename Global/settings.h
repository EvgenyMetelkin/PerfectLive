#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>

class Settings{
    Q_GADGET
    Q_ENUMS(Section)
    Q_ENUMS(Key)
public:
    enum Section{
        General
    };

    enum Key{
        Mode,
        DiaryPath
    };

    class ValueRef{
    public:
        ValueRef(Settings &st, const QString &kp) :
            m_parent(st), m_keyPath(kp){}
        ValueRef & operator = (const QVariant &d);
    private:
        Settings &m_parent;
        const QString m_keyPath;
    };

    static void setDefaults(const QString &str);
    static QVariant get(Key, Section /*s*/ = General);
    static ValueRef set(Key, Section /*s*/ = General);

private:
    QString keyPath(Section, Key);

    static Settings & instance();

    Settings();
    Settings(const Settings &);
    Settings & operator = (const Settings &);

private:
    QMetaEnum m_keys;
    QMetaEnum m_sections;
    QMap<QString, QVariant> m_defaults;
    QSettings m_conf;
};

#endif // SETTINGS_H
