#include "iconhelperController.h"
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QObject>


QIcon IconHelper::recolorSvg(const QString &path, const QColor &color, const QSize &size)
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

void IconHelper::setToggleIcon(QPushButton *button, const QString &iconPath,
                               const QColor &activeColor, const QColor &inactiveColor,
                               const QSize &size,
                               std::function<void(bool)> onToggled)
{
    if (!button) return;

    button->setIcon(IconHelper::recolorSvg(iconPath, inactiveColor, size));

    QObject::connect(button, &QPushButton::toggled, button,
                     [button, iconPath, activeColor, inactiveColor, size, onToggled](bool checked) {
                         button->setIcon(IconHelper::recolorSvg(iconPath, checked ? activeColor : inactiveColor, size));

                         // 👉 Aquí ejecuta la acción adicional si se pasa
                         if (onToggled)
                             onToggled(checked);
                     });
}
