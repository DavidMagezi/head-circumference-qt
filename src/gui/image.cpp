#include "gui/image.h"

#include <iostream>
#include <filesystem>
#include <string>

#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QImageReader>
#include <QMessageBox>
#include <QPushButton>

namespace GUI{
    Image::Image(std::string folder, QWidget *parent):
        folder_(folder),
        image_files_(0),
        mask_files_(0),
        QWidget(parent){
            scan_directory();
            setWindowTitle(folder_.c_str());
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
        std::string file_name = folder_ + "/805_HC.png";
        QImageReader reader(file_name.c_str());
        reader.setAutoTransform(true);
        const QImage current_image = reader.read();
        if (current_image.isNull()) {
            QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                    QFileDialog::tr("Cannot load %1: %2")
                    .arg(QDir::toNativeSeparators(file_name.c_str()),reader.errorString()));
            return false;
        }

        image_label_->setPixmap(QPixmap::fromImage(current_image));
        image_label_->show();

        return true;
    }

    void Image::scan_directory(){
        const std::filesystem::path folder(folder_);
        std::regex image_pattern("(.*)(_HC.png)");
        std::regex mask_pattern("(.*)(_HC_Annotation.png)");
        std::string next_file;
        for (auto& file: std::filesystem::directory_iterator(folder)){
            next_file = file.path().filename().string();
            if (std::regex_match(next_file,image_pattern)){
                image_files_.push_back(next_file);
            } else if (std::regex_match(next_file,mask_pattern)){
                mask_files_.push_back(next_file);
            }
        }
        std::cout << "Number of images: " << image_files_.size() << "\n";
        std::cout << "Number of masks: " << mask_files_.size() << "\n";
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
