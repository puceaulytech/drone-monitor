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

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);

private:
  /*!
   * Setup toolbar menus
   */
  void setupMenus();

  /*!
   * Setup toolbar actions
   */
  void setupActions();

  QGridLayout* m_mainLayout{nullptr};
  QWidget* m_mainWidget{nullptr};

  LogViewer* m_logViewer{nullptr};
  Commands* m_commands{nullptr};

  // Menus
  QMenu* m_helpMenu{nullptr};

  // Actions
  QAction* m_aboutQtAction{nullptr};
  QAction* m_aboutAction{nullptr};

private Q_SLOTS:
  void showAbout();
  void showAboutQt();
};

#endif
