#ifndef SIDEBARVIEW_H
#define SIDEBARVIEW_H

#include <QFrame>

class Sidebar : public QFrame
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    void resetToDefault();
signals:
    void menuSelected(const QString &menuName);  // 👈 señal que estás emitiendo
};


#endif // SIDEBARVIEW_H
