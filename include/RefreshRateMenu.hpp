#pragma once

#ifndef DRONE_MONITOR_REFRESH_RATE_MENU_HPP
#define DRONE_MONITOR_REFRESH_RATE_MENU_HPP

#include <QMenu>
#include <QActionGroup>

class RefreshRateMenu : public QMenu {
public:
  explicit RefreshRateMenu(const QString& title, QWidget* parent = nullptr);

  int refreshRate;
private:
  QVector<QPair<int, QAction*>> m_refreshActions;
  QActionGroup* m_actionGroup;
};

#endif
