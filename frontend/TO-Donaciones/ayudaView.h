#ifndef AYUDAVIEW_H
#define AYUDAVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QPixmap>
#include <QHBoxLayout>

class AyudaView : public QWidget {
    Q_OBJECT
public:
    explicit AyudaView(QWidget *parent = nullptr);
};

#endif // AYUDAVIEW_H
