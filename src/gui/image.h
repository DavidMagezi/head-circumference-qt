#ifndef DEF_GUI_IMAGE
#define DEF_GUI_IMAGE

#include <QCheckBox>
#include <QLabel>
#include <QString>
#include <QWidget>

class QPushButton;
namespace GUI{
class Image : public QWidget {
public:
    explicit Image(QString folder, QWidget *parent = 0);
    ~Image();
    bool load_file();
    enum class Load{Previous,Next};

private slots:
    void handle_button(Load direction);
    void handle_checkbox(bool checked);

private:

    QCheckBox *check_box_ellipse_;
    QPushButton *button_previous_, *button_next_;
    QString folder_;
    QLabel *image_label_;

    static constexpr double SCALE_FACTOR_ = 1.0;
    static constexpr int BUTTON_HEIGHT_ = 30;
    static constexpr int BUTTON_WIDTH_ = 80;
    static constexpr int IMAGE_HEIGHT_ = 200;
    static constexpr int IMAGE_WIDTH_ = IMAGE_HEIGHT_;
    static constexpr int TOP_MARGIN_ = 5;
    static constexpr int LEFT_MARGIN_ = 5;

};
}//namespace GUI
#endif //DEF_GUI_IMAGE
