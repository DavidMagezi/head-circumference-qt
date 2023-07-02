#include <string>

#include <QApplication>
#include <QFileDialog>
#include <QString>

#include "gui/image.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    QString folder; 
    folder = QFileDialog::getExistingDirectory(nullptr,
            QFileDialog::tr("Select directory"),
            QDir(QDir::homePath()).filePath("local/ultrasound/"),
            QFileDialog::ShowDirsOnly 
            | QFileDialog::DontResolveSymlinks);
    GUI::Image image(folder.toStdString());
    image.show();
    
    return app.exec();
}
