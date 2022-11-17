#include <MainWindow.hpp>
#include <QDockWidget>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_mainLayout = new QGridLayout;
  m_mainWidget = new QWidget;
  m_logViewer = new LogViewer;
  m_commands = new Commands;
  m_view3d = new View3D;

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

  m_logViewer->printLog("Starting Drone Monitor...");

  // Commands

  connect(m_commands, &Commands::autoDestruction, this, [=]() {
    m_logViewer->printLog("KABOOM");

    for (auto object : m_biteObject) delete object;

    m_biteObject.clear();
  });
}

void MainWindow::setupMenus() {
  m_viewMenu = menuBar()->addMenu(tr("&View"));
  m_settingsMenu = menuBar()->addMenu(tr("&Settings"));
  m_helpMenu = menuBar()->addMenu(tr("&Help"));

  m_timerMenu = new QMenu("Refresh Rate");
  m_helpMenu->insertActions(nullptr, {m_aboutQtAction, m_aboutAction});
  m_settingsMenu->insertMenu(nullptr, m_timerMenu);

  QAction* previous = nullptr;
  for (const auto& refreshAction : m_refreshActions) {
    m_timerMenu->insertAction(previous, refreshAction.second);
    previous = refreshAction.second;
  }
}

void MainWindow::setupActions() {
  m_aboutQtAction = new QAction(tr("About &Qt"), this);
  connect(m_aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQt);

  m_aboutAction = new QAction(tr("&About"), this);
  connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

  QVector<int> initialRefreshRates = {1000, 100, 50, 10};

  for (auto targetRefreshRate : initialRefreshRates)
    m_refreshActions.append(
        qMakePair(targetRefreshRate,
                  new QAction(QString::number(targetRefreshRate) + " ms")));
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
  QPixmap ez(":/images/load.png");
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

  m_loadAscii = m_toolbar->addAction(QIcon(ez), "Load Ascii");
  connect(m_loadAscii, &QAction::triggered, this, [=]() {
    m_geoSurface = new Surface(0, 0, 0);
    m_geoViewer = QWidget::createWindowContainer(m_geoSurface);
    auto* geoDockWidget = new QDockWidget("Geo Viewer");
    geoDockWidget->setWidget(m_geoViewer);
    addDockWidget(Qt::LeftDockWidgetArea, geoDockWidget);
    m_viewMenu->addAction(geoDockWidget->toggleViewAction());
    m_geoSurface->show();
  });
}
void MainWindow::setupTimer() {
  m_refreshRate = 1000;
  m_mainTimer = new QTimer;
  m_mainTimer->setInterval(m_refreshRate);

  for (const auto& refreshAction : m_refreshActions)
    connect(refreshAction.second, &QAction::triggered, this, [=] {
      m_refreshRate = refreshAction.first;
    });

  m_mainTimer->start();
}
