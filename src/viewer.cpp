#include <QApplication>

#include "gui/image.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    GUI::Image image;
    image.show();
    return app.exec();
}
