#pragma once

#ifndef DRONE_MONITOR_VALUES_VIEWER_HPP
#define DRONE_MONITOR_VALUES_VIEWER_HPP

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class ValuesViewer : public QWidget {
  Q_OBJECT

public:
  explicit ValuesViewer(QWidget* parent = nullptr);

private:
  QFormLayout* m_layout;
  QStringList m_valuesName;
  QMap<QString, QLineEdit*> m_values;

  void setupFields();
};

#endif
