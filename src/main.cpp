#include <MainWindow.hpp>
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char** argv) {
  QApplication app(argc, argv);

#ifdef _WIN32
  QApplication::setStyle(QStyleFactory::create("Fusion"));
#endif

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
