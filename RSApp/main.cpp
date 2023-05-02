#include "rsapp.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char* argv[]) {
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QApplication a(argc, argv);
    RSApp w;
    w.show();
    return a.exec();
}
