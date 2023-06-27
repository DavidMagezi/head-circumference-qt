#include "gui/image.h"

#include <QPushButton>

namespace GUI{
    Image::Image(QWidget *parent):
        QWidget(parent){
            setFixedSize(500,250);
            button_ = new QPushButton("Select Folder", this);
            button_->setGeometry(10, 10, 80, 30);
    }

    Image::~Image(){
    }
}
