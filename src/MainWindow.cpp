/* CODE WRITTEN ENTIRELY BY A BIG GAY GUY WITH NO BITCHES NO LIFE NO MUSCLE NO MONEY NO FUTURE NO SELF ESTEEM NO FRIENDS NO WILL TO LIVE */


#include <MainWindow.hpp>
#include <QDockWidget>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_mainLayout = new QGridLayout;
  m_mainWidget = new QWidget;
  m_logViewer = new LogViewer;
  m_commands = new Commands;

  setWindowTitle("Drone Monitoring");
  resize(1920, 1080);

  setupActions();
  setupMenus();

  // Top left
  m_mainLayout->addWidget(new QLabel("Truc 1"), 0, 0, Qt::AlignCenter);

  // Top right
  m_mainLayout->addWidget(new QLabel("Truc 2"), 0, 1, Qt::AlignCenter);

  // Bottom left
  m_logViewer->setSizePolicy(
      QSizePolicy::Minimum,
      QSizePolicy::Minimum);  // To make logViewer fill the whole cell without
                              // growing too much
  m_mainLayout->addWidget(m_logViewer, 1, 0);

  // Bottom right
  m_mainLayout->addWidget(new QLabel("Truc 4"), 1, 1, Qt::AlignCenter);

  m_mainWidget->setLayout(m_mainLayout);
  setCentralWidget(m_mainWidget);

  // Left dock
  auto* leftDockWidget = new QDockWidget("Commands");
  leftDockWidget->setWidget(m_commands);
  addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget);

  m_logViewer->printLog("Starting Drone Monitor...");

  // Commands
  connect(m_commands, &Commands::startDrone, this, [=]() {
    m_logViewer->printLog("Starting THE drone");
  });

  connect(m_commands, &Commands::stopDrone, this, [=]() {
    m_logViewer->printLog("Stopping the drone :(");
  });

  connect(m_commands, &Commands::doSomething, this, [=]() {
    m_logViewer->printLog("Doing something!");
  });

  connect(m_commands, &Commands::autoDestruction, this, [=]() {
    m_logViewer->printLog("KABOOM");
  });
}

void MainWindow::setupMenus() {
  m_helpMenu = menuBar()->addMenu(tr("&Help"));
  m_helpMenu->insertActions(nullptr, {m_aboutQtAction, m_aboutAction});
}

void MainWindow::setupActions() {
  m_aboutQtAction = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQt);

  m_aboutAction = new QAction(tr("&About"), this);
  connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::showAbout() {
  QMessageBox::about(
      this, "About",
      "Drone Monitor, made by Romain Chardiny and Robin Perdreau");
}

void MainWindow::showAboutQt() {
  QMessageBox::aboutQt(this);
}
