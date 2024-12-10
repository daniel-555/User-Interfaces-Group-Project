// COMP2811 Coursework 2: data model edited from starter code

#pragma once

#include <QAbstractTableModel>
#include "dataset.hpp"

class SampleModel : public QAbstractTableModel
{
public:
  SampleModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}
  void updateFromFile(const QString &);
  bool hasData() const { return dataset.size() > 0; }

  int rowCount(const QModelIndex &index) const { return dataset.size(); }
  int columnCount(const QModelIndex &index) const { return 8; }
  QVariant data(const QModelIndex &, int) const;
  QVariant headerData(int, Qt::Orientation, int) const;

private:
  SampleDataset dataset;
};
