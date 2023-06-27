#include "gui/image.h"

#include <QPushButton>

namespace GUI{
    Image::Image(QString folder, QWidget *parent):
        folder_(folder),
        QWidget(parent) {
            setWindowTitle(folder_);
            setFixedSize(500,250);
            button_ = new QPushButton("Next", this);
            button_->setGeometry(10, 10, 80, 30);
    }

    Image::~Image(){
    }
}
