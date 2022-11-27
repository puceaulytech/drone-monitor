#pragma once

#ifndef DRONE_MONITOR_SERIAL_FETCHER_HPP
#define DRONE_MONITOR_SERIAL_FETCHER_HPP

#include <QActionGroup>
#include <QComboBox>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

class Serial : public QWidget {
  Q_OBJECT

public:
  explicit Serial(QWidget* parent = nullptr);

private:
  QSerialPort m_serialPort;
  QVBoxLayout* m_layout;
  QHBoxLayout* m_configLayout;
  QLabel* m_errorReporter;
  QWidget* m_configWidget;
  QComboBox* m_portChooser;
  QComboBox* m_baudRateChooser;

  const QVector<qint32> availableBaudRates = {1200,  2400,  4800,  9600,
                                              19200, 38400, 57600, 115200};

private Q_SLOTS:
  void refreshPorts();
  void changeBaudRate();
  void changePort();
};

#endif
