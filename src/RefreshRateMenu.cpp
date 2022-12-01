#include <RefreshRateMenu.hpp>

RefreshRateMenu::RefreshRateMenu(const QString& title, QWidget* parent) : QMenu(title, parent) {
  m_actionGroup = new QActionGroup(parent);
  QVector<int> initialRefreshRates = {1000, 100, 50, 10};

  for (auto targetRefreshRate : initialRefreshRates) {
    auto* action = new QAction(QString::number(targetRefreshRate) + " ms");
    action->setActionGroup(m_actionGroup);
    action->setCheckable(true);
    m_refreshActions.append(qMakePair(targetRefreshRate, action));
  }

  QAction* previous = nullptr;
  for (const auto& refreshAction : m_refreshActions) {
    insertAction(previous, refreshAction.second);
    connect(refreshAction.second, &QAction::triggered, this, [=] {
      refreshRate = refreshAction.first;
      Q_EMIT updateRefreshRate(refreshRate);
    });

    previous = refreshAction.second;
  }
}
