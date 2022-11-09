#include <Commands.hpp>
#include <QPushButton>

Commands::Commands(QWidget* parent) : QWidget(parent) {
  m_layout = new QVBoxLayout;
  m_startDrone = new QPushButton("Start drone");
  m_stopDrone = new QPushButton("Stop drone");
  m_doSomething = new QPushButton("Do something");
  m_autoDestruction = new QPushButton("Auto-destruction");

  m_layout->addWidget(m_startDrone);
  connect(m_startDrone, &QPushButton::clicked, this, [=]() {
    emit startDrone();
  });

  m_layout->addWidget(m_stopDrone);
  connect(m_stopDrone, &QPushButton::clicked, this, [=]() {
    emit stopDrone();
  });

  m_layout->addWidget(m_doSomething);
  connect(m_doSomething, &QPushButton::clicked, this, [=]() {
    emit doSomething();
  });

  m_layout->addWidget(m_autoDestruction);
  connect(m_autoDestruction, &QPushButton::clicked, this, [=]() {
    emit autoDestruction();
  });

  m_layout->addStretch();

  setLayout(m_layout);
}
