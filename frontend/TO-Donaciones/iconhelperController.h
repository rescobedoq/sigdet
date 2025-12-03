#ifndef ICONHELPERCONTROLLER_H
#define ICONHELPERCONTROLLER_H

#include <QIcon>
#include <QColor>
#include <QString>
#include <QSize>
#include <QPushButton>

class IconHelper
{
public:
    static QIcon recolorSvg(const QString &path, const QColor &color, const QSize &size = QSize(20, 20));

    static void setToggleIcon(QPushButton *button, const QString &iconPath,
                              const QColor &activeColor = QColor(37, 99, 235),
                              const QColor &inactiveColor = QColor(227, 227, 227),
                              const QSize &size = QSize(20, 20),
                              std::function<void(bool)> onToggled = nullptr);
};

#endif // ICONHELPERCONTROLLER_H
