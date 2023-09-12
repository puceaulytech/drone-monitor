#include <TextInput.hpp>

TextInput::TextInput(QWidget* parent) : QWidget(parent) {
    m_layout = new QHBoxLayout;

    m_send = new QPushButton("Send to database");
    m_input = new QLineEdit;

    connect(m_send, &QPushButton::released, this, &TextInput::emitSignal);

    m_layout->addWidget(m_send);
    m_layout->addWidget(m_input);

    setLayout(m_layout);
}

void TextInput::emitSignal() {
    Q_EMIT buttonClicked();
}

QString TextInput::sendInput() {
    return m_input->displayText();
}
