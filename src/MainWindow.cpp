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
  setupToolBar ();
  // Top left
  m_mainLayout->addWidget(QWidget::createWindowContainer(m_view3d), 0, 0);

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
  m_viewMenu->addAction(leftDockWidget->toggleViewAction());

  m_logViewer->printLog("Starting Drone Monitor...");

  // Commands
  connect(m_commands, &Commands::startDrone, this, [=]() {
    m_logViewer->printLog("DRAWING THE THING");

    auto targetFilename = QFileDialog::getOpenFileName(
        this, "Open 3D Object", QDir::currentPath(), "Text files (*.txt)");
    if (targetFilename.isEmpty()) return;

    m_biteObject = m_view3d->drawFile(targetFilename);
  });

  connect(m_commands, &Commands::stopDrone, this, [=]() {
    m_logViewer->printLog("Centering the camera");
    m_view3d->centerCamera ();
  });

  connect(m_commands, &Commands::doSomething, this, [=]() {
    m_logViewer->printLog("Doing something!");
  });

  connect(m_commands, &Commands::autoDestruction, this, [=]() {
    m_logViewer->printLog("KABOOM");

    for (auto object : m_biteObject) delete object;

    m_biteObject.clear();
  });
}

void MainWindow::setupMenus() {
  m_viewMenu = menuBar()->addMenu(tr("&View"));

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
      "Drone Monitor, made by Robin 'Peasant' Perdreau and debbuged by Romain 'Chad' Chardiny");
}

void MainWindow::showAboutQt() {
  QMessageBox::aboutQt(this);
}
void MainWindow::setupToolBar(){
    QPixmap newpix("../drone-monitor/save.png");


    m_toolBar = addToolBar ("Gorgeous toolbar");
    QAction* drawfile = m_toolBar->addAction(QIcon(newpix), "Draw File");
    connect(drawfile, &QAction::triggered, m_view3d,[=]{

        auto targetFilename = QFileDialog::getOpenFileName(
            this, "Open 3D Object", QDir::currentPath(), "Text files (*.txt)");
        if (targetFilename.isEmpty()) return;

        m_biteObject = m_view3d->drawFile(targetFilename);

    });
    m_toolBar->addSeparator();





}
