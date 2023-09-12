#include <TextInput.hpp>

TextInput::TextInput(QWidget* parent) : QWidget(parent) {
    m_layout = new QHBoxLayout;

    m_send = new QPushButton("Send to database");
    m_input = new QLineEdit;

    m_layout->addWidget(m_send);
    m_layout->addWidget(m_input);

    setLayout(m_layout);
}

void TextInput::sendInput(const QString& input) {
}
