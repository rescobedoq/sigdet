#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QIcon>
#include <QColor>
#include <QString>
#include <QSize>
#include <QPushButton>

class iconhelper
{
public:
    // Recolorea un SVG y devuelve un QIcon
    static QIcon recolorSvg(const QString &path, const QColor &color, const QSize &size = QSize(20, 20));

    // Configura un QPushButton para que cambie de color al estar toggled (seleccionado)
    static void setToggleIcon(QPushButton *button, const QString &iconPath,
                              const QColor &activeColor = QColor(37, 99, 235),
                              const QColor &inactiveColor = QColor(227, 227, 227),
                              const QSize &size = QSize(20, 20));
};

#endif // ICONHELPER_H
