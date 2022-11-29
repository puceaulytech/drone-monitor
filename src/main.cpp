#include <MainWindow.hpp>
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char** argv) {
  qputenv("QT3D_RENDERER", "opengl");
  QApplication app(argc, argv);

#if defined(USE_CUSTOM_STYLESHEET) && !defined(__linux__)
  QFile file(":/darkorange.stylesheet");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  app.setStyleSheet(styleSheet);
#elif defined(_WIN32)
  QApplication::setStyle(QStyleFactory::create("Fusion"));
#endif
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
