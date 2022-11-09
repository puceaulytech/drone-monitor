#pragma once

#ifndef DRONE_MONITOR_COMMANDS_HPP
#define DRONE_MONITOR_COMMANDS_HPP

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Commands : public QWidget {
  Q_OBJECT

public:
  explicit Commands(QWidget* parent = nullptr);

private:
  QVBoxLayout* m_layout;

  QPushButton* m_startDrone;
  QPushButton* m_stopDrone;
  QPushButton* m_doSomething;
  QPushButton* m_autoDestruction;

Q_SIGNALS:
  void startDrone();
  void stopDrone();
  void doSomething();
  void autoDestruction();
};

#endif
