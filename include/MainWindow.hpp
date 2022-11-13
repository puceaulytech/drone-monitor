#pragma once

#ifndef DRONE_MONITOR_MAIN_WINDOW_HPP
#define DRONE_MONITOR_MAIN_WINDOW_HPP

#include <Commands.hpp>
#include <LogViewer.hpp>
#include <QAction>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QWidget>
#include <View3D.hpp>
#include <QToolBar>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  /*!
   * Setup ugly menus
   */
  void setupMenus();

  /*!
   * Setup ugly menu's actions
   */
  void setupActions();
   //Setup Good looking toolbar
  void setupToolBar();


  QGridLayout* m_mainLayout{nullptr};
  QWidget* m_mainWidget{nullptr};

  LogViewer* m_logViewer{nullptr};
  Commands* m_commands{nullptr};
  View3D* m_view3d{nullptr};

  // Menus
  QMenu* m_viewMenu{nullptr};
  QMenu* m_helpMenu{nullptr};

  // Actions
  QAction* m_aboutQtAction{nullptr};
  QAction* m_aboutAction{nullptr};
  QToolBar* m_toolBar;
  QVector<Qt3DCore::QEntity*> m_biteObject;

private Q_SLOTS:
  void showAbout();
  void showAboutQt();
};

#endif
