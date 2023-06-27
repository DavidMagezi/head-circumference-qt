#include <QApplication>

#include "gui/image.h"
#include "gui/select.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    //GUI::Select select;
    //select.setFileMode(QFileDialog::AnyFile);
    GUI::Image image;
    image.show();
    return app.exec();
}
