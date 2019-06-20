#include "animationmodel.h"

namespace SchMatrix {

AnimationModel::AnimationModel(QObject *parent) : QAbstractTableModel(parent) {}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  // FIXME: Implement me!
  return QVariant();
}

int AnimationModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  // FIXME: Implement me!
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  // FIXME: Implement me!
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  // FIXME: Implement me!
  return QVariant();
}

bool AnimationModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endInsertRows();
  return false;
}

bool AnimationModel::insertColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginInsertColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endInsertColumns();
  return false;
}

bool AnimationModel::removeRows(int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();
  return false;
}

bool AnimationModel::removeColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginRemoveColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endRemoveColumns();
  return false;
}

}  // namespace SchMatrix
