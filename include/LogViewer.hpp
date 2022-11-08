#pragma once

#ifndef DRONE_MONITOR_LOG_VIEWER_HPP
#define DRONE_MONITOR_LOG_VIEWER_HPP

#include <QTextEdit>

class LogViewer : public QTextEdit {
public:
  LogViewer();

  void printLog(const QString& log);
};

#endif
