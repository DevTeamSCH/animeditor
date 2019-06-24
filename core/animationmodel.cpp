#include "animationmodel.h"

#include <QList>
#include <QSequentialAnimationGroup>
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

AnimationModel::AnimationModel(QObject *parent)
    : QAbstractTableModel(parent), root(this) {
  // build basic animation tree
  auto layer_1 = new SchMatrix::Layer(&root);
  root.addAnimation(layer_1);
  auto keyframe = new SchMatrix::Keyframe(layer_1);
  layer_1->addAnimation(keyframe);
}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  // FIXME: Implement me!
  return QVariant();
}

int AnimationModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return root.animationCount();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  auto longestAnim = root.duration();
  auto basicAnimLength = 180 * fps;  // 3 min * FPS

  return (longestAnim > basicAnimLength) ? longestAnim : basicAnimLength;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int row = index.row();
  int col = index.column();

  switch (role) {
    case Qt::DisplayRole:
      return animTimeline[row][col];
      break;
  }

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
