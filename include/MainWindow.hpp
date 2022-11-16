#pragma once

#ifndef DRONE_MONITOR_MAIN_WINDOW_HPP
#define DRONE_MONITOR_MAIN_WINDOW_HPP

#include <Commands.hpp>
#include <LogViewer.hpp>
#include <Q3DSurface>
#include <QAction>
#include <QDebug>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QToolBar>
#include <QWidget>
#include <Surface.hpp>
#include <View3D.hpp>
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  /*!
   * Setup menus
   */
  void setupMenus();

  /*!
   * Setup menu's actions
   */
  void setupActions();
  /*!
   * Setup toolbar
   */
  void setupToolbar();
  // Timer initialization
  void setupTimer();

  QGridLayout* m_mainLayout{nullptr};
  QWidget* m_mainWidget{nullptr};
  QWidget* m_geoViewer;
  LogViewer* m_logViewer{nullptr};
  Commands* m_commands{nullptr};
  View3D* m_view3d{nullptr};

  Surface* m_geoSurface{nullptr};
  // Menus
  QMenu* m_viewMenu{nullptr};
  QMenu* m_helpMenu{nullptr};
  QMenu* m_settingsMenu{nullptr};
  QMenu* m_timerMenu{nullptr};

  // Actions
  QAction* m_aboutQtAction{nullptr};
  QAction* m_aboutAction{nullptr};
  QAction* m_drawFileAction{nullptr};
  QAction* m_centerCamAction{nullptr};
  QAction* m_loadAscii;
  // Refresh Rates
  QVector<QPair<int, QAction*>> m_refreshActions;

  QToolBar* m_toolbar;
  QVector<Qt3DCore::QEntity*> m_biteObject;
  QTimer* m_mainTimer{nullptr};
  int m_refreshRate;
private Q_SLOTS:
  void showAbout();
  void showAboutQt();
};

#endif
