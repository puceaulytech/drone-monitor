#pragma once

#ifndef DRONE_MONITOR_SERIAL_FETCHER_HPP
#define DRONE_MONITOR_SERIAL_FETCHER_HPP

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QActionGroup>
#include <QMenu>

class SerialMenu : public QMenu {
public:
  explicit SerialMenu(const QString& title, QWidget* parent = nullptr);

private:
  QActionGroup* m_actionGroup;
  QSerialPort m_serialPort;

private Q_SLOTS:
  void refreshPorts();
};

#endif