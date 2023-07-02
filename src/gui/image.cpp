#include "gui/image.h"

#include <algorithm>
#include <iostream>
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
        displayed_image_("Filename of image to display"),
        folder_(folder),
        mask_path_(folder_),
        image_index_(0),
        image_files_(0),
        mask_available_(false),
        mask_files_(0),
        QWidget(parent){
            setWindowTitle(folder_.c_str());
            setFixedSize(500,250);
            button_first_ = new QPushButton("First", this);
            button_last_ = new QPushButton("Last", this);
            button_next_ = new QPushButton("Next", this);
            button_previous_ = new QPushButton("Previous", this);
            check_box_ellipse_ = new QCheckBox("Ellipse",this);
            image_label_ = new QLabel("Ultrasound image",this);
            image_label_->setScaledContents(true);
            mask_label_ = new QLabel("Mask image",this);
            mask_label_->setScaledContents(true);
            text_label_ = new QLabel("File name of ultrasound image",this);

            connect(button_first_, &QPushButton::released, this, [=]{Image::handle_button(Load::First);}); 
            connect(button_last_, &QPushButton::released, this, [=]{Image::handle_button(Load::Last);}); 
            connect(button_next_, &QPushButton::released, this, [=]{Image::handle_button(Load::Next);}); 
            connect(button_previous_, &QPushButton::released, this, [=]{Image::handle_button(Load::Previous);}); 
            connect(check_box_ellipse_, &QAbstractButton::clicked, this, &Image::handle_checkbox); 

            check_box_ellipse_->setGeometry((LEFT_MARGIN_*5) + (BUTTON_WIDTH_*4), (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_first_->setGeometry(LEFT_MARGIN_, (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_previous_->setGeometry((LEFT_MARGIN_*2) + BUTTON_WIDTH_, (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_next_->setGeometry((LEFT_MARGIN_*3) + (BUTTON_WIDTH_*2), (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            button_last_->setGeometry((LEFT_MARGIN_*4) + (BUTTON_WIDTH_*3), (TOP_MARGIN_*2) + IMAGE_HEIGHT_ , BUTTON_WIDTH_, BUTTON_HEIGHT_);
            image_label_->setGeometry(LEFT_MARGIN_,TOP_MARGIN_,IMAGE_WIDTH_,IMAGE_HEIGHT_);
            mask_label_->setGeometry((LEFT_MARGIN_*2) + BUTTON_WIDTH_ +  IMAGE_WIDTH_,TOP_MARGIN_,IMAGE_WIDTH_,IMAGE_HEIGHT_);
            text_label_->setGeometry((LEFT_MARGIN_*2) + IMAGE_WIDTH_ ,TOP_MARGIN_,IMAGE_WIDTH_,IMAGE_HEIGHT_);

            scan_directory();
            int initial_index(0);
            if (number_of_images_ > 0) {
                displayed_image_ = image_files_[initial_index];
            }
            folder_.append(displayed_image_);
            if (mask_available_){
                //check_box_ellipse_->show();
                mask_path_.append(mask_files_[initial_index]);
            } else {
                check_box_ellipse_->hide();
                mask_label_->hide();
            }
            load_file(); 

    }

    Image::~Image(){
    }

    bool Image::load_file(){
        QImageReader reader(folder_.c_str());
        reader.setAutoTransform(true);
        const QImage current_image = reader.read();
        if (current_image.isNull()) {
            QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                    QFileDialog::tr("Cannot load %1: %2")
                    .arg(QDir::toNativeSeparators(folder_.c_str()),reader.errorString()));
            return false;
        }

        image_label_->setPixmap(QPixmap::fromImage(current_image));
        image_label_->show();
        if (mask_available_){
            QImageReader mask_reader(mask_path_.c_str());
            reader.setAutoTransform(true);
            const QImage current_mask = mask_reader.read();
            if (current_mask.isNull()) {
                QMessageBox::information(this,QGuiApplication::applicationDisplayName(),
                        QFileDialog::tr("Cannot load %1: %2")
                        .arg(QDir::toNativeSeparators(mask_path_.c_str()),mask_reader.errorString()));
                return false;
            }
            mask_label_->setPixmap(QPixmap::fromImage(current_mask));
            mask_label_->show();
        }
        text_label_->setText(folder_.stem().c_str());
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
        std::sort(image_files_.begin(),image_files_.end());
        std::sort(mask_files_.begin(),mask_files_.end());
        number_of_images_ = image_files_.size();
        number_of_masks_ = mask_files_.size();
        mask_available_ = number_of_masks_ > 0;
    }

    //private slot
    void Image::handle_button(Load direction){
        switch (direction){
            case Load::First :
                image_index_ = 0;
                break;
            case Load::Last:
                image_index_ = number_of_images_-1;
                break;
            case Load::Next :
                if (++image_index_ >= number_of_images_) {
                    image_index_ = number_of_images_-1;
                }
                break;
            case Load::Previous:
                if (--image_index_ < 0) {
                    image_index_ = 0;
                }
                break;
        }
        displayed_image_ = image_files_[image_index_];
        folder_.replace_filename(displayed_image_);
        if (mask_available_){
            mask_path_.replace_filename(mask_files_[image_index_]);
        }
        load_file();
    }

    void Image::handle_checkbox(bool checked){
        std::string message; 
        if (checked){
            mask_label_->show();
        } else {
            mask_label_->hide();
        }
    }

}
