#include "mainstyle.h"

MainStyle::MainStyle()
{
    // Настраиваем палитру для цветовых ролей элементов интерфейса
    this->setColor(QPalette::NoRole, QColor(53, 53, 53));
    this->setColor(QPalette::Window, QColor(53, 53, 53));
    this->setColor(QPalette::WindowText, Qt::white);
    this->setColor(QPalette::Base, QColor(248, 248, 248));
    this->setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    this->setColor(QPalette::ToolTipBase, QColor(228, 228, 228));
    this->setColor(QPalette::ToolTipText, Qt::white);
    this->setColor(QPalette::Text, QColor(53, 53, 53));
    this->setColor(QPalette::Button, QColor(53, 53, 53));
    this->setColor(QPalette::ButtonText, QColor(53, 53, 53));
    this->setColor(QPalette::BrightText, Qt::red);
    this->setColor(QPalette::Link, QColor(42, 130, 218));
    this->setColor(QPalette::Highlight, QColor(42, 130, 218));
    this->setColor(QPalette::HighlightedText, Qt::white);
}
