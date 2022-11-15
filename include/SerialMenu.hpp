#pragma once

#ifndef DRONE_MONITOR_SERIAL_FETCHER_HPP
#define DRONE_MONITOR_SERIAL_FETCHER_HPP

#include <QActionGroup>
#include <QMenu>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialMenu : public QMenu {
  Q_OBJECT

public:
  explicit SerialMenu(const QString& title, QWidget* parent = nullptr);

private:
  QActionGroup* m_actionGroup;
  QSerialPort m_serialPort;

private Q_SLOTS:
  void refreshPorts();
};

#endif
