#include <QApplication>
#include <QFileDialog>
#include <QString>

#include "gui/image.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    QString folder; 
    folder = QFileDialog::getOpenFileName();

    GUI::Image image(folder);
    image.show();
    
    return app.exec();
}
