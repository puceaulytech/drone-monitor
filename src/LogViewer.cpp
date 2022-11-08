#include <LogViewer.hpp>

LogViewer::LogViewer() {
  setDisabled(true);
}

void LogViewer::printLog(const QString& log) {
  auto currentText = toPlainText();
  currentText += log + "\n";
  setText(currentText);
}
