#include <ValuesViewer.hpp>

ValuesViewer::ValuesViewer(QWidget* parent) : QWidget(parent) {
  m_layout = new QFormLayout;

  setLayout(m_layout);
}

void ValuesViewer::addNewField(const QString& fieldName) {
  qInfo() << fieldName;
  auto* field = new QLineEdit;
  field->setReadOnly(true);
  m_values.insert(fieldName, field);
  m_layout->addRow(fieldName, field);
}

void ValuesViewer::dataReceived(const QString& label, double value) {
  if (!m_values.contains(label))
    addNewField(label);

  auto field = m_values.value(label);
  field->setText(QString::number(value));
}

double ValuesViewer::getValue(const QString& label) const {
  return 69.666;
}
