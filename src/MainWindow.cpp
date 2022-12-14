#include <MainWindow.hpp>
#include <QDockWidget>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_mainLayout = new QGridLayout;
  m_mainWidget = new QWidget;
  m_logViewer = new LogViewer;
  m_valuesViewer = new ValuesViewer;
  m_commands = new Commands;
  m_view3d = new View3D;
  m_serial = new Serial;

  setWindowTitle("Drone Monitoring");
  resize(1920, 1080);

  setupActions();
  setupMenus();
  setupToolbar();
  // Top left
  m_mainLayout->addWidget(QWidget::createWindowContainer(m_view3d), 0, 0);

  // Top right

  // Bottom left
  m_logViewer->setSizePolicy(
      QSizePolicy::Minimum,
      QSizePolicy::Minimum);  // To make logViewer fill the whole cell without
                              // growing too much

  // Bottom right

  m_mainWidget->setLayout(m_mainLayout);
  setCentralWidget(m_mainWidget);

  // Bottom dock
  auto* logDockWidget = new QDockWidget("Logs");
  logDockWidget->setWidget(m_logViewer);
  addDockWidget(Qt::BottomDockWidgetArea, logDockWidget);
  m_viewMenu->addAction(logDockWidget->toggleViewAction());

  auto* serialDockWidget = new QDockWidget("Serial");
  serialDockWidget->setWidget(m_serial);
  addDockWidget(Qt::RightDockWidgetArea, serialDockWidget);
  m_viewMenu->addAction(serialDockWidget->toggleViewAction());

  auto* valuesDockWidget = new QDockWidget("Values");
  valuesDockWidget->setWidget(m_valuesViewer);
  addDockWidget(Qt::RightDockWidgetArea, valuesDockWidget);
  m_viewMenu->addAction(valuesDockWidget->toggleViewAction());

  m_logViewer->printLog("Starting Drone Monitor...");

  // Commands

  connect(m_commands, &Commands::autoDestruction, this, [=]() {
    m_logViewer->printLog("KABOOM");

    for (auto object : m_biteObject) delete object;

    m_biteObject.clear();
  });

  connect(m_serial, &Serial::onReceiveData, m_valuesViewer, &ValuesViewer::dataReceived);
}

void MainWindow::setupMenus() {
  m_viewMenu = menuBar()->addMenu(tr("&View"));
  m_settingsMenu = menuBar()->addMenu(tr("&Settings"));
  m_helpMenu = menuBar()->addMenu(tr("&Help"));

  m_refreshRateMenu = new RefreshRateMenu("Refresh Rate");

  m_helpMenu->insertActions(nullptr, {m_aboutQtAction, m_aboutAction});
  m_settingsMenu->insertMenu(nullptr, m_refreshRateMenu);

}

void MainWindow::setupActions() {
  m_aboutQtAction = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQt);

  m_aboutAction = new QAction(tr("&About"), this);
  connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::showAbout() {
  QMessageBox::about(this, "About",
                     "Drone Monitor, made by Robin 'Peasant' Perdreau and "
                     "debbuged by Romain 'Chad' Chardiny");
}

void MainWindow::showAboutQt() {
  QMessageBox::aboutQt(this);
}

void MainWindow::setupToolbar() {
  QPixmap draw(":/images/draw.png");
  QPixmap center(":/images/center.png");

  m_toolbar = addToolBar("Toolbar");

  m_drawFileAction = m_toolbar->addAction(QIcon(draw), "Draw File");

  connect(m_drawFileAction, &QAction::triggered, this, [=] {
    auto targetFilename = QFileDialog::getOpenFileName(
        this, "Open 3D Object", QDir::currentPath(), "Text files (*.txt)");
    if (targetFilename.isEmpty()) return;

    m_biteObject = m_view3d->drawFile(targetFilename);
  });

  m_toolbar->addSeparator();
  m_centerCamAction = m_toolbar->addAction(QIcon(center), "Center Camera");

  connect(m_centerCamAction, &QAction::triggered, this, [=]() {
    m_logViewer->printLog("Centering the camera");
    m_view3d->centerCamera();
  });
}

void MainWindow::setupTimer() {
  m_refreshRateMenu->refreshRate = 1000;
  m_mainTimer = new QTimer;
  m_mainTimer->setInterval(m_refreshRateMenu->refreshRate);

  m_mainTimer->start();
}
