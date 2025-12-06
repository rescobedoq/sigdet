#include "AyudaView.h"
#include <QFont>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPainter>
#include <QPainterPath>

AyudaView::AyudaView(QWidget *parent) : QWidget(parent)
{
    // --- Scroll principal ---
    auto *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);

    // --- Contenedor principal de contenido ---
    auto *content = new QWidget;
    content->setMaximumWidth(900);

    auto *mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 40, 40, 40);
    mainLayout->setSpacing(32);

    // --- Wrapper para centrar el contenido ---
    auto *wrapper = new QWidget;
    auto *wrapperLayout = new QHBoxLayout(wrapper);
    wrapperLayout->addStretch();      // margen izquierdo flexible
    wrapperLayout->addWidget(content);
    wrapperLayout->addStretch();      // margen derecho flexible

    scroll->setWidget(wrapper);

    // --- Título principal ---
    QLabel *title = new QLabel("Maximiza el Impacto de tu ONG con la Aplicación");
    title->setAlignment(Qt::AlignCenter);
    title->setWordWrap(true);
    title->setStyleSheet("font-size: 28px; font-weight: 800; color: #1e293b;");

    QLabel *desc = new QLabel(
        "Descubre cómo nuestra plataforma empodera a tu organización, optimizando cada acción y amplificando tu misión en el mundo.");
    desc->setAlignment(Qt::AlignCenter);
    desc->setWordWrap(true);
    desc->setStyleSheet("font-size: 16px; color: #475569;");

    mainLayout->addWidget(title);
    mainLayout->addWidget(desc);

    // --- Imagen principal con texto superpuesto ---
    QWidget *imageContainer = new QWidget;
    imageContainer->setFixedSize(770, 350);
    imageContainer->setStyleSheet("background: transparent;");
    // --- Imagen de fondo ---
    QLabel *imageLabel = new QLabel(imageContainer);
    imageLabel->setGeometry(0, 0, 770, 350);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    imageLabel->setStyleSheet("background: transparent; border-radius: 35px;");

    // Escalamos con recorte (ocupa todo el ancho)
    QPixmap pix(":/icons/ayudaImages/ayuda_1.png");
    int targetWidth = imageContainer->width();
    int targetHeight = imageContainer->height();

    QPixmap scaledToWidth = pix.scaledToWidth(targetWidth, Qt::SmoothTransformation);

    // Si la imagen queda más alta que el contenedor, la recortamos centrada
    if (scaledToWidth.height() > targetHeight) {
        int yOffset = (scaledToWidth.height() - targetHeight) / 2;
        scaledToWidth = scaledToWidth.copy(0, yOffset, targetWidth, targetHeight);
    }

    QPixmap scaled = scaledToWidth;

    // Aplicamos máscara redondeada al pixmap
    QPixmap rounded(scaled.size());
    rounded.fill(Qt::transparent);
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(0, 0, scaled.width(), scaled.height(), 35, 35);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, scaled);
    painter.end();

    imageLabel->setPixmap(rounded);

    // --- Gradiente encima de la imagen ---
    QLabel *overlayGradient = new QLabel(imageContainer);
    overlayGradient->setGeometry(0, 0, 770, 350);
    overlayGradient->setStyleSheet(
        "background: qlineargradient(x1:0, y1:1, x2:0, y2:0, "
        "stop:0 rgba(0,0,0,0.6), stop:1 rgba(0,0,0,0)); "
        "border-radius: 35px;"
        );
    overlayGradient->raise();

    // --- Texto superpuesto ---
    QLabel *overlayText = new QLabel("Tu Misión, Nuestro Propósito", imageContainer);
    overlayText->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    overlayText->setGeometry(0, 0, 770, 350);
    overlayText->setStyleSheet(
        "color: white;"
        "font-size: 28px;"
        "font-weight: bold;"
        "padding-bottom: 30px;"
        "padding-left: 30px;"
        "text-shadow: 2px 2px 6px rgba(0,0,0,0.8);"
        );
    overlayText->raise();

    // --- Añadir a layout principal ---
    mainLayout->addWidget(imageContainer, 0, Qt::AlignHCenter);

    QLabel *intro = new QLabel(
        "En el corazón de cada ONG reside la pasión por generar un cambio. Nuestra aplicación está diseñada para ser tu aliada más poderosa, simplificando la complejidad de la gestión y liberando tu tiempo para lo que realmente importa: la comunidad a la que sirves.");
    intro->setWordWrap(true);
    intro->setStyleSheet("font-size: 14px; color: #334155;");
    mainLayout->addWidget(intro);

    // --- Sección de tarjetas ---
    struct Card {
        QString titulo;
        QString texto;
        QStringList items;
        QString img;
    };

    QList<Card> cards = {
                         {"Análisis de Tendencias",
                          "Convierte datos complejos en conocimientos claros. Identifica patrones en tus donaciones y actividades para tomar decisiones estratégicas.",
                          {"Optimización de campañas futuras.", "Asignación eficiente de recursos.", "Mejora en la toma de decisiones."},
                          ":/icons/ayudaImages/ayuda_2.png"},
                         {"Gestión de Donaciones",
                          "Monitorea las donaciones entrantes y entregadas a las personas más necesitadas, asignando su estado.",
                          {"Transparencia total en el flujo de donaciones.", "Seguimiento preciso del ciclo de vida.", "Mejora de la confianza y rendición de cuentas."},
                          ":/icons/ayudaImages/ayuda_3.png"},
                         {"Gestión de Inventario",
                          "Gestiona tu inventario automáticamente: al agregar o enviar donaciones, el sistema actualiza tus existencias.",
                          {"Control de stock en tiempo real.", "Reducción de errores manuales.", "Optimización de la distribución de ayuda."},
                          ":/icons/ayudaImages/ayuda_4.png"},
                         {"Reportes Personalizados",
                          "Demuestra tu impacto con claridad y transparencia. Genera informes detallados para tus aliados.",
                          {"Credibilidad mejorada ante stakeholders.", "Facilitación de la búsqueda de fondos.", "Comunicación efectiva de resultados."},
                          ":/icons/ayudaImages/ayuda_5.png"},
                         {"Segmentación de Donantes",
                          "Identifica a tus donantes clave, entiende sus preferencias y personaliza la comunicación.",
                          {"Aumento de la retención de donantes.", "Campañas más efectivas.", "Fortalecimiento de relaciones duraderas."},
                          ":/icons/ayudaImages/ayuda_6.png"},
                         {"Gestión de Proyectos",
                          "Organiza y supervisa tus iniciativas, desde la planificación hasta la ejecución.",
                          {"Ejecución más eficiente.", "Mejor coordinación del equipo.", "Maximización del impacto en el campo."},
                          ":/icons/ayudaImages/ayuda_2.png"},
                         };

    auto *cardsLayout = new QGridLayout;
    cardsLayout->setHorizontalSpacing(20);
    cardsLayout->setVerticalSpacing(20);

    int row = 0, col = 0;
    for (const Card &c : cards) {
        QFrame *card = new QFrame;
        card->setFrameShape(QFrame::StyledPanel);
        card->setStyleSheet("background: white; border-radius: 12px; border: 1px solid #e2e8f0;");
        card -> setFixedWidth(260);

        auto *vbox = new QVBoxLayout(card);
        QLabel *img = new QLabel;
        img->setPixmap(QPixmap(c.img).scaled(240, 180, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        img->setFixedSize(240, 180);

        img->setStyleSheet("border-radius: 8px;");
        vbox->addWidget(img);

        QLabel *title = new QLabel(c.titulo);
        title->setStyleSheet("font-size: 16px; font-weight: 600; color: #1e293b;border:none;");
        vbox->addWidget(title);

        QLabel *text = new QLabel(c.texto);
        text->setWordWrap(true);
        text->setStyleSheet("font-size: 13px; color: #475569;border:none;");
        vbox->addWidget(text);

        QLabel *impact = new QLabel("<b>Impacto Clave:</b>");
        impact ->setStyleSheet("color:#135bec;border:none;");
        vbox->addWidget(impact);

        QString listHtml = "<ul>";
        for (auto &item : c.items)
            listHtml += "<li>" + item + "</li>";
        listHtml += "</ul>";

        QLabel *ul = new QLabel(listHtml);
        ul->setStyleSheet("font-size: 13px; color: #475569;border:none;");
        ul->setWordWrap(true);
        vbox->addWidget(ul);

        cardsLayout->addWidget(card, row, col);
        if (++col == 3) { col = 0; row++; }
    }

    mainLayout->addLayout(cardsLayout);

    // --- Layout final ---
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->addWidget(scroll);
    setLayout(rootLayout);

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;");
}
