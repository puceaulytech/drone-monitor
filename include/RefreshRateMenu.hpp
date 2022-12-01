#pragma once

#ifndef DRONE_MONITOR_REFRESH_RATE_MENU_HPP
#define DRONE_MONITOR_REFRESH_RATE_MENU_HPP

#include <QActionGroup>
#include <QMenu>

class RefreshRateMenu : public QMenu {
  Q_OBJECT

public:
  explicit RefreshRateMenu(const QString& title, QWidget* parent = nullptr);

  int refreshRate;

private:
  QVector<QPair<int, QAction*>> m_refreshActions;
  QActionGroup* m_actionGroup;

Q_SIGNALS:
  void updateRefreshRate(int newRefreshRate);
};

#endif
