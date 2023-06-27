#ifndef DEF_GUI_IMAGE
#define DEF_GUI_IMAGE

#include <QWidget>

class QPushButton;
namespace GUI{
class Image : public QWidget {
public:
    explicit Image(QWidget *parent = 0);
    ~Image();
private:
    QPushButton *button_;
};
}//namespace GUI
#endif //DEF_GUI_IMAGE
