#include "animationmodel.h"

#include <QList>
#include <QSequentialAnimationGroup>
#include <cstdlib>
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

int AnimationModel::lastLayerNumber = 1;

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
  if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
    auto layer = static_cast<Layer *>(root.animationAt(section));
    return layer->getName();
  }

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

  auto longestAnim = root.duration();

  for (int i = 0; i < count; ++i) {
    auto layer =
        new Layer(QString("layer %1").arg(lastLayerNumber++), row, &root);
    root.insertAnimation(row, layer);

    layer->addAnimation(new Keyframe(layer));
    animTimeline.insert(row, {FrameTypes::Key});

    if (root.animationCount() > 1) {
      layer->addPause(longestAnim);

      for (int i = 0; i < (longestAnim / frameLength) - 1; ++i) {
        animTimeline[row].push_back(FrameTypes::Frame);
      }

      animTimeline[row].push_back(FrameTypes::EndOfFrame);
    }
  }

  for (int i = row; i < count; ++i) {
    static_cast<Layer *>(root.animationAt(i))->setZOrder(i);
  }

  endInsertRows();
  return true;
}

bool AnimationModel::insertColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginInsertColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endInsertColumns();
  return false;
}

bool AnimationModel::removeRows(int row, int count, const QModelIndex &parent) {
  if (root.animationCount() < count || abs(root.animationCount() - count) == 1)
    return false;

  beginRemoveRows(parent, row, row + count - 1);
  auto animCount = root.animationCount();

  if (animCount < count) return false;

  for (int i = row; i < count; ++i) {
    root.takeAnimation(i);
    animTimeline.removeAt(i);
  }

  for (int i = row; i < animCount; ++i) {
    static_cast<Layer *>(root.animationAt(i))->setZOrder(i);
  }

  endRemoveRows();
  return true;
}

bool AnimationModel::removeColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginRemoveColumns(parent, column, column + count - 1);
  // FIXME: Implement me!
  endRemoveColumns();
  return false;
}

}  // namespace SchMatrix
