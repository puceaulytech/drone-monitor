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

  enum DataType {
    Height,
    Speed,
  };

private:
  QSerialPort m_serialPort;
  QVBoxLayout* m_layout;
  QHBoxLayout* m_configLayout;
  QLabel* m_reporter;
  QWidget* m_configWidget;
  QComboBox* m_portChooser;
  QComboBox* m_baudRateChooser;
  QPushButton* m_connect;

  const QVector<qint32> availableBaudRates = {1200,  2400,  4800,  9600,
                                              19200, 38400, 57600, 115200};

  static QPair<QString, double> parsePacket(const QString& data);
  void setupConnection();

private Q_SLOTS:
  void refreshPorts();
  void changeBaudRate();
  void changePort();
  void connectSerial();
  void handleSerialError();
  void handleRead();

Q_SIGNALS:
  void onReceiveData(const QString& label, double value);
};

#endif
