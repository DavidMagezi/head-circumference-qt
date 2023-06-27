#ifndef DEF_GUI_SELECT
#define DEF_GUI_SELECT

#include <QFileDialog>

namespace GUI{
class Select : public QFileDialog {
public:
    explicit Select(QFileDialog *parent = 0);
    ~Select();
};
}//namespace GUI
#endif //DEF_GUI_SELECT
