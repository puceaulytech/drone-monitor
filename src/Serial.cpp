#include <Serial.hpp>

Serial::Serial(QWidget* parent)
    : QWidget(parent), m_serialPort() {
  m_layout = new QVBoxLayout;
  m_configLayout = new QHBoxLayout;
  m_configWidget = new QWidget;
  m_errorReporter = new QLabel;

  m_portChooser = new QComboBox;
  m_baudRateChooser = new QComboBox;

  for (auto baudRate : availableBaudRates)
    m_baudRateChooser->addItem(QString::number(baudRate), baudRate);

  connect(m_baudRateChooser, &QComboBox::currentIndexChanged, this, &Serial::changeBaudRate);
  connect(m_portChooser, &QComboBox::currentIndexChanged, this, &Serial::changePort);

  m_configLayout->addWidget(m_portChooser);
  m_configLayout->addWidget(m_baudRateChooser);
  m_configWidget->setLayout(m_configLayout);

  m_layout->addWidget(m_configWidget);
  m_layout->addWidget(m_errorReporter);
  m_layout->addStretch();

  setLayout(m_layout);

  refreshPorts();
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
  m_serialPort.close();
  auto newValue = m_portChooser->currentText();
  m_serialPort.setPortName(newValue);

  if (!m_serialPort.open(QIODevice::ReadOnly)) {
    m_errorReporter->setText("Error: " + m_serialPort.errorString());
  } else {
    m_errorReporter->clear();
  }
}