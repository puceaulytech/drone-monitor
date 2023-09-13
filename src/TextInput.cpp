#include <format>

#include <TextInput.hpp>

TextInput::TextInput(QWidget* parent) : QWidget(parent) {
    m_db = new Database("zireael-db", "api", "Test1234", "zireael");

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
    QString input = m_input->displayText();
    m_input->clear();
    m_db->execute(QString("INSERT INTO test (value) VALUES ('%1')").arg(input));
    return QString("Added '%1' to the table").arg(input);
}
