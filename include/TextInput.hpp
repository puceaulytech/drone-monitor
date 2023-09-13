#pragma once

#ifndef DRONE_MONITOR_TEXT_INPUT_HPP
#define DRONE_MONITOR_TEXT_INPUT_HPP

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

class TextInput : public QWidget {
    Q_OBJECT

public:
    explicit TextInput(QWidget* parent = nullptr);
    QString sendInput();

private:
    QLineEdit* m_input;
    QPushButton* m_send;
    QHBoxLayout* m_layout;

    void emitSignal();

Q_SIGNALS:
    void buttonClicked();
};

#endif
