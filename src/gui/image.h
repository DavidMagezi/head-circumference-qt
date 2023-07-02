#ifndef DEF_GUI_IMAGE
#define DEF_GUI_IMAGE

#include <filesystem>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <QCheckBox>
#include <QLabel>
#include <QWidget>

class QPushButton;
namespace GUI{
class Image : public QWidget {
public:
    explicit Image(std::string folder, QWidget *parent = 0);
    ~Image();
    bool load_file();
    enum class Load{First,Last,Previous,Next};
    void scan_directory();

private slots:
    void handle_button(Load direction);
    void handle_checkbox(bool checked);

private:
    QCheckBox *check_box_ellipse_;
    QPushButton *button_first_, *button_last_, *button_previous_, *button_next_;
    std::string displayed_image_; 
    std::filesystem::path folder_, mask_path_;
    std::vector<std::string> image_files_, mask_files_;
    QLabel *image_label_, *mask_label_,*text_label_;
    int image_index_, number_of_images_, number_of_masks_;
    bool mask_available_;

    static constexpr int BUTTON_HEIGHT_ = 30;
    static constexpr int BUTTON_WIDTH_ = 80;
    static constexpr int IMAGE_HEIGHT_ = 200;
    static constexpr int IMAGE_WIDTH_ = IMAGE_HEIGHT_;
    static constexpr int TOP_MARGIN_ = 5;
    static constexpr int LEFT_MARGIN_ = 5;

    //static constexpr std::string_view IMAGE_PATTERN = '.jpg';
};
}//namespace GUI
#endif //DEF_GUI_IMAGE
