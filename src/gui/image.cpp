#include "gui/image.h"

#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QImageReader>
#include <QMessageBox>
#include <QPushButton>

namespace GUI{
    Image::Image(QString folder, QWidget *parent):
        folder_(folder),
        QWidget(parent) {
            setWindowTitle(folder_);
            setFixedSize(500,250);
            button_ = new QPushButton("Next", this);
            button_->setGeometry(10, 10, 80, 30);
            image_label_ = new QLabel();
    }

    bool Image::load(){
        QString file_name = folder_ + "/805_HC.png";
        QImageReader reader(file_name);
        reader.setAutoTransform(true);
        const QImage current_image = reader.read();
        if (current_image.isNull()) {
            QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                    QFileDialog::tr("Cannot load %1: %2")
                    .arg(QDir::toNativeSeparators(file_name),reader.errorString()));
            return false;
        }

        double scale_factor = 1;

        //scrollArea->setVisible(true);
        //printAct->setEnabled(true);
        //fitToWindowAct->setEnabled(true);
        //updateActions();

        //if (!fitToWindowAct->isChecked()){
        //    imageLabel->adjustSize();
        //}

        image_label_->setPixmap(QPixmap::fromImage(current_image));
        image_label_->show();

        return true;
    }

    Image::~Image(){
    }
}
