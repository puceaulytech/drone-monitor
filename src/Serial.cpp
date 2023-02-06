#include <Serial.hpp>

Serial::Serial(QWidget* parent) : QWidget(parent), m_serialPort() {
  m_layout = new QVBoxLayout;
  m_configLayout = new QHBoxLayout;
  m_configWidget = new QWidget;
  m_reporter = new QLabel;

  m_portChooser = new QComboBox;
  m_baudRateChooser = new QComboBox;
  m_connect = new QPushButton("Connect");

  for (auto baudRate : availableBaudRates)
    m_baudRateChooser->addItem(QString::number(baudRate), baudRate);

  m_baudRateChooser->setCurrentIndex(m_baudRateChooser->findData(9600));

  connect(&m_serialPort, &QSerialPort::errorOccurred, this,
          &Serial::handleSerialError);
  connect(&m_serialPort, &QSerialPort::readyRead, this, &Serial::handleRead);

  connect(m_baudRateChooser, &QComboBox::currentIndexChanged, this,
          &Serial::changeBaudRate);
  connect(m_portChooser, &QComboBox::currentIndexChanged, this,
          &Serial::changePort);
  connect(m_connect, &QPushButton::clicked, this, &Serial::connectSerial);

  m_configLayout->setContentsMargins(0, 0, 0, 0);
  m_configLayout->addWidget(m_portChooser);
  m_configLayout->addWidget(m_baudRateChooser);
  m_configWidget->setLayout(m_configLayout);

  m_layout->addWidget(m_configWidget);
  m_layout->addWidget(m_connect);
  m_layout->addWidget(m_reporter);
  m_layout->addStretch();

  setLayout(m_layout);

  refreshPorts();
}

void Serial::setupConnection() {
  m_serialPort.setDataBits(QSerialPort::Data8);
  m_serialPort.setParity(QSerialPort::NoParity);
  m_serialPort.setStopBits(QSerialPort::OneStop);
  m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
  m_serialPort.setDataTerminalReady(true);
}

void Serial::refreshPorts() {
  auto availablePorts = QSerialPortInfo::availablePorts();

  m_portChooser->clear();

  for (const auto& port : availablePorts) {
    m_portChooser->addItem(port.portName());
  }
}

void Serial::changeBaudRate() {
  auto newValue = m_baudRateChooser->currentData().value<qint32>();
  m_serialPort.setBaudRate(newValue);
}

void Serial::changePort() {
  auto newValue = m_portChooser->currentText();
  m_serialPort.setPortName(newValue);
}

void Serial::connectSerial() {
  if (m_serialPort.isOpen()) m_serialPort.close();

  if (!m_serialPort.open(QIODevice::ReadOnly)) {
    m_reporter->setText("Error: " + m_serialPort.errorString());
  } else {
    setupConnection();
    m_reporter->setText("Connected successfully");
  }
}

void Serial::handleSerialError() {
  m_reporter->setText("Serial Error: " + m_serialPort.errorString());
}

void Serial::handleRead() {
  QByteArray data;
  while (m_serialPort.canReadLine()) {
    data.append(m_serialPort.readLine());
  }
  QString stringData = data;
  QString totest = data;
  if (!stringData.isEmpty() && verifyPacket(totest)) {
    auto parseResult = parsePacket(stringData);
    Q_EMIT onReceiveData(parseResult.first, parseResult.second);
  }
}
QPair<QString, double> Serial::parsePacket(const QString& data) {
  auto split = data.split(" ");
  auto label = split.at(0);
  auto value = split.at(1).toDouble();

  return qMakePair(label, value);
}
bool Serial::verifyPacket(const QString& data) {
  bool is_valid;
  if (!data.contains("/")) {
    return false;
  }
  auto splited = data.split("/");
  if (!splited[0].contains(":") || !splited[1].contains(":")) {
    return false;
  }
  auto left = splited[0].split(":");
  auto right = splited[1].split(":");
  int get_sumed = 0;
  for (auto& i : left[1]) {
    get_sumed += i.digitValue();
  }
  QString get_shifted;
  for (auto i : right[0]) {
    get_shifted.append(QChar(i.unicode() - 1));
  }

  if (left[0] == get_shifted && right[1].toInt() == get_sumed) {
    return true;
  }
  return false;
}
