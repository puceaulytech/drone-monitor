#include <MainWindow.hpp>
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char** argv) {
  qputenv("QT3D_RENDERER", "opengl");
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
