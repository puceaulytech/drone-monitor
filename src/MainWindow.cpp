#include <MainWindow.hpp>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow()
    : m_mainLayout(new QGridLayout()),
      m_mainWidget(new QWidget()),
      m_logViewer(new LogViewer()) {
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

  m_logViewer->printLog("Starting Drone Monitor...");
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
