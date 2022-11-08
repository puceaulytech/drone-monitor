#pragma once

#ifndef DRONE_MONITOR_LOG_VIEWER_HPP
#define DRONE_MONITOR_LOG_VIEWER_HPP

#include <QTextEdit>

class LogViewer : public QTextEdit {
public:
  LogViewer();

  /*!
   * Add a line of log to the log viewer
   * @param log The line of log
   */
  void printLog(const QString& log);
};

#endif
