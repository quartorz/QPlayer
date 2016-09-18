#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(R"(
        QSlider::groove:horizontal {
            height: 5px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);
            margin: 0 0;
        }

        QSlider::handle:horizontal {
            border: 1px solid #5c5c5c;
            width: 5px;
            margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */
        }
    )");

    MainWindow w;
    w.show();

    return a.exec();
}
