#include "settings.h"
#include <QSettings>
#include <QMetaEnum>
#include <QRegExp>
#include <QStringList>

Settings::Settings(){
    const QMetaObject &mo = staticMetaObject;
    int idx = mo.indexOfEnumerator("Key");
    m_keys = mo.enumerator(idx);

    idx = mo.indexOfEnumerator("Section");
    m_sections = mo.enumerator(idx);
}

QVariant Settings::get(Key k, Section s){
    Settings &self = instance();
    QString key = self.keyPath(s, k);
    return self.m_conf.value(key, self.m_defaults[key]);
}

Settings::ValueRef Settings::set(Key k, Section s){
    Settings &self = instance();
    return ValueRef(self, self.keyPath(s, k));
}

void Settings::setDefaults(const QString &str){
    Settings &self = instance();

    //section/key : value
    //section - optional
    QRegExp rxRecord("^\\s*(((\\w+)/)?(\\w+))\\s*:\\s*([^\\s].{0,})\\b\\s*$");

    auto kvs = str.split(QRegExp(";\\W*"), QString::SkipEmptyParts); //key-values
    for(auto kv : kvs){
        if(rxRecord.indexIn(kv) != -1){
            QString section = rxRecord.cap(3);
            QString key = rxRecord.cap(4);
            QString value = rxRecord.cap(5);

            int iKey = self.m_keys.keyToValue(key.toLocal8Bit().data());
            if(iKey != -1){
                int iSection = self.m_sections.keyToValue(section.toLocal8Bit().data());
                if(section.isEmpty() || iSection != -1){
                    self.m_defaults[rxRecord.cap(1)] = value;
                }
            }
        }
    }
}

//Settings::ValueRef-----------------------------------------------------------
Settings::ValueRef & Settings::ValueRef::operator = (const QVariant &data){
    m_parent.m_conf.setValue(m_keyPath, data);
    return *this;
}

//PRIVATE METHODS--------------------------------------------------------------
QString Settings::keyPath(Section s, Key k){
    auto szSection = m_sections.valueToKey(s);
    auto szKey = m_keys.valueToKey(k);
    return QString(s == General ? "%1" : "%2/%1").arg(szKey).arg(szSection);
}

Settings & Settings::instance(){
    static Settings singleton;
    return singleton;
}
