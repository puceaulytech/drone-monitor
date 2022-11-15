#include <SerialMenu.hpp>

SerialMenu::SerialMenu(const QString& title, QWidget* parent) : QMenu(title, parent), m_serialPort() {
  connect(this, &SerialMenu::aboutToShow, this, &SerialMenu::refreshPorts);
}

void SerialMenu::refreshPorts() {
  clear();

  auto availablePorts = QSerialPortInfo::availablePorts();

  QAction* previous = nullptr;

  for (const auto& portInfo : availablePorts) {
    auto* portAction = new QAction(portInfo.portName());
    insertActions(previous, {portAction});
    connect(portAction, &QAction::triggered, this, [=]() {
      m_serialPort.setPort(portInfo);
    });
    previous = portAction;
  }
}