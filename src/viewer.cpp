#include <QApplication>
#include <QLabel>

int main(int argc, char **argv){
    QApplication app(argc,argv);
    QLabel viewer("Ultrasound viewer");
    viewer.show();
    return app.exec();
}
