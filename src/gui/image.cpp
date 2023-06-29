#include "gui/image.h"

#include <string>

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
        QWidget(parent){
            setWindowTitle(folder_);
            setFixedSize(500,250);
            button_next_ = new QPushButton("Next", this);
            button_previous_ = new QPushButton("Previous", this);
            check_box_ellipse_ = new QCheckBox("Ellipse",this);
            image_label_ = new QLabel("Ultrasound image",this);
            image_label_->setScaledContents(true);

            connect(button_next_, &QPushButton::released, this, [=]{Image::handle_button(Load::Next);}); 
            connect(button_previous_, &QPushButton::released, this, [=]{Image::handle_button(Load::Previous);}); 
            connect(check_box_ellipse_, &QAbstractButton::clicked, this, &Image::handle_checkbox); 

            check_box_ellipse_->setGeometry((LEFT_MARGIN_*3) + (BUTTON_WIDTH_*2), (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_next_->setGeometry((LEFT_MARGIN_*2) + BUTTON_WIDTH_, (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_previous_->setGeometry(LEFT_MARGIN_, (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            image_label_->setGeometry(LEFT_MARGIN_,TOP_MARGIN_,IMAGE_WIDTH_,IMAGE_HEIGHT_);
    }

    Image::~Image(){
    }

    bool Image::load_file(){
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

        //image_label_->adjustSize();


        image_label_->setPixmap(QPixmap::fromImage(current_image));
        image_label_->show();

        return true;
    }

    //private slot
    void Image::handle_button(Load direction){
        std::string message;
        if (direction == Load::Next) {
            message = "next";
        } else if (direction == Load::Previous) {
            message = "previous";
        } else {
            message = "empty";
        }

        QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                QFileDialog::tr(message.c_str()));
    }

    void Image::handle_checkbox(bool checked){
        std::string message; 
        if (checked){
            message = "You have checked the box";
        } else {
            message = "You have UNchecked the box";
        }
        QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                QFileDialog::tr(message.c_str()));
    }

}
