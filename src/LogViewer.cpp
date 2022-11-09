#include <LogViewer.hpp>
#include <QDateTime>
#include <QScrollBar>

LogViewer::LogViewer(QWidget* parent) : QTextEdit(parent) {
  setReadOnly(true);
  setFontFamily("Consolas");
}

void LogViewer::printLog(const QString& log) {
  auto currentText = toPlainText();
  currentText += "[" + getTimestamp() + "] " + log + "\n";
  setText(currentText);

  // Scroll to bottom
  verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

QString LogViewer::getTimestamp() {
  return QDateTime::currentDateTime().toString("hh:mm:ss");
}
