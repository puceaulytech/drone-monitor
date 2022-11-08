#pragma once

#ifndef DRONE_MONITOR_MAIN_WINDOW_HPP
#define DRONE_MONITOR_MAIN_WINDOW_HPP

#include <LogViewer.hpp>
#include <QAction>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private:
  void setupMenus();
  void setupActions();

  QGridLayout* m_mainLayout;
  QWidget* m_mainWidget;

  LogViewer* m_logViewer;

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