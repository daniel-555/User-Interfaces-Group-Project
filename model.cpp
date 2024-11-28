// COMP2811 Coursework 2: data model

#include "model.hpp"


void SampleModel::updateFromFile(const QString& filename)
{
  beginResetModel();
  dataset.loadData(filename.toStdString());
  endResetModel();
}


QVariant SampleModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignRight | Qt::AlignVCenter);
  }
  else if (role == Qt::DisplayRole) {
    Sample q = dataset[index.row()];
    switch (index.column()) {
      case 0: return QVariant(q.getTime().c_str());
      case 1: return QVariant(q.getLabel().c_str());
      case 2: return QVariant(q.getDefinition().c_str());
      case 3: return QVariant(q.getQualifier().c_str());
      case 4: return QVariant(q.getResult());
      case 5: return QVariant(q.getUnit().c_str());
      case 6: return QVariant(q.getNorthing());
      case 7: return QVariant(q.getEasting());
    }
  }

  return QVariant();
}


QVariant SampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Vertical) {
    return QVariant(section + 1);
  }

  switch (section) {
    case 0: return QString("Time");
    case 1: return QString("Label");
    case 2: return QString("Definition");
    case 3: return QString("Result Qualifier");
    case 4: return QString("Result");
    case 5: return QString("Unit");
    case 6: return QString("Northing");
    case 7: return QString("Easting");
    default: return QVariant();
  }
}
