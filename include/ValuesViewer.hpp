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

  double getValue(const QString& label) const;

private:
  QFormLayout* m_layout;
  QMap<QString, QLineEdit*> m_values;

  void addNewField(const QString& fieldName);

public Q_SLOTS:
  void dataReceived(const QString& data, double value);
};

#endif
