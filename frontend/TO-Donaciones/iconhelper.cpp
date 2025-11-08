#include "iconhelper.h"
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QObject>

QIcon iconhelper::recolorSvg(const QString &path, const QColor &color, const QSize &size)
{
    QSvgRenderer renderer(path);
    QPixmap pix(size);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    renderer.render(&p);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(pix.rect(), color);
    p.end();

    return QIcon(pix);
}

void iconhelper::setToggleIcon(QPushButton *button, const QString &iconPath,
                               const QColor &activeColor, const QColor &inactiveColor,
                               const QSize &size)
{
    if (!button) return;

    // Ícono inicial (apagado)
    button->setIcon(iconhelper::recolorSvg(iconPath, inactiveColor, size));

    // Conectar para que cambie de color al hacer toggle
    QObject::connect(button, &QPushButton::toggled, button,
                     [button, iconPath, activeColor, inactiveColor, size](bool checked){
                         button->setIcon(iconhelper::recolorSvg(iconPath, checked ? activeColor : inactiveColor, size));
                     });
}
