#include <ValuesViewer.hpp>

ValuesViewer::ValuesViewer(QWidget* parent) : QWidget(parent) {
  m_layout = new QFormLayout;
  m_valuesName = {"Vitesse", "Altitude"};

  setupFields();

  setLayout(m_layout);
}

void ValuesViewer::setupFields() {
  for (const auto& valueName : m_valuesName) {
    auto* value = new QLineEdit("0");
    value->setReadOnly(true);

    value->setStyleSheet("background-color: green;");

    m_layout->addRow(valueName, value);
    m_values.insert(valueName, value);
  }
}
