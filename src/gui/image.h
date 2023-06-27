#ifndef DEF_GUI_IMAGE
#define DEF_GUI_IMAGE

#include <QString>
#include <QWidget>

class QPushButton;
namespace GUI{
class Image : public QWidget {
public:
    explicit Image(QString folder, QWidget *parent = 0);
    ~Image();
private:
    QPushButton *button_;
    QString folder_;
};
}//namespace GUI
#endif //DEF_GUI_IMAGE
