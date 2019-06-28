#include "animationmodel.h"

#include <QList>
#include <QModelIndex>
#include <QSequentialAnimationGroup>
#include <algorithm>
#include <cstdlib>
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

int AnimationModel::lastLayerNumber = 1;

AnimationModel::AnimationModel(QObject *parent)
    : QAbstractTableModel(parent), root(this) {
  // build basic animation tree
  auto layer_1 = new SchMatrix::Layer(&root, "layer 1");
  root.addAnimation(layer_1);
  auto keyframe = new SchMatrix::Keyframe(layer_1);
  layer_1->addAnimation(keyframe);

  // init animTimeline
  animTimelineRow.reserve(180 * fps);
  animTimelineRow.insert(0, FrameTypes::BlankKey);

  animTimeline.insert(0, animTimelineRow);
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
      auto colSize = animTimeline[row].size() - 1;
      if (col > colSize) return FrameTypes::PotentialFrame;

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
        new Layer(&root, QString("layer %1").arg(lastLayerNumber++), row);
    root.insertAnimation(row, layer);
    layer->addAnimation(new Keyframe(layer));

    animTimeline.insert(row, animTimelineRow);

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

  for (auto &list : animTimeline) {
    for (int i = 0; i < count; ++i) {
      list.insert(column, FrameTypes::PotentialFrame);
    }
  }

  endInsertColumns();
  return true;
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

bool SchMatrix::AnimationModel::setData(const QModelIndex &index,
                                        const QVariant &value, int role) {
  auto row = index.row();
  auto col = index.column();

  if (row > root.animationCount()) return false;

  auto val = value.toInt();
  auto layerSize = animTimeline[row].size();
  auto layer = static_cast<Layer *>(root.animationAt(row));
  auto currentAnimation = layer->currentAnimation();
  auto currentAnimationIdx = layer->indexOfAnimation(currentAnimation);
  auto currentIsPause = qobject_cast<QPauseAnimation *>(currentAnimation);

  QPauseAnimation *pause =
      (currentIsPause) ? static_cast<QPauseAnimation *>(currentAnimation)
                       : nullptr;

  if (col > layerSize) {  // setting data in PotentialFrame
    auto start = animTimeline[row].end();

    if (val == FrameTypes::Frame)
      animTimeline[row].insert(col, FrameTypes::EndOfFrame);
    else
      animTimeline[row].insert(col, val);

    // this can only be calculated after the insertion
    auto pauseDuration = animTimeline[row].size() - layerSize;

    if (currentIsPause) {
      // replace EndOfFrame with Frame
      animTimeline[row][layerSize - 1] = FrameTypes::Frame;
      pause->setDuration(pause->duration() + frameLength * pauseDuration);
    } else {  // current is (Blank)Keyframe
      layer->addPause(frameLength * pauseDuration);  // Add missing pause
    }

    std::fill(start + 1, animTimeline[row].end(), FrameTypes::Frame);

    // data changes from layerSize(original size) to animTimeline[row].size()
    emit dataChanged(createIndex(row, layerSize),
                     createIndex(row, animTimeline[row].size()));
  } else {  // setting data inside, before potentialFrames
    if (currentIsPause) {
      if (val == FrameTypes::Frame) {
        animTimeline[row].insert(col, val);
        pause->setDuration(pause->duration() + frameLength);
      }

      if (val == FrameTypes::BlankKey || val == FrameTypes::Key) {
        animTimeline[row][col] = val;
        animTimeline[row][col - 1] = FrameTypes::EndOfFrame;

        // TODO find builtin algorithm
        int pauseStartIdx = col;
        for (; pauseStartIdx != 0 ||
               animTimeline[row][pauseStartIdx] != FrameTypes::Frame;
             --pauseStartIdx)

          pauseStartIdx++;

        auto pauseLeftDuration = frameLength * (col - pauseStartIdx);
        auto pauseRightDuration =
            frameLength * (pause->duration() - pauseLeftDuration + frameLength);

        // shrink current pause
        pause->setDuration(pauseLeftDuration);

        // insert Keyframe inside Frame
        if (val == FrameTypes::Key) {
          auto currentKey = layer->currentKeyframe();
          auto newKey = new Keyframe(currentKey);
          layer->insertAnimation(currentAnimationIdx + 1, newKey);
        } else if (val == FrameTypes::BlankKey) {  // insert BlankKeyframe
          layer->insertAnimation(currentAnimationIdx + 1, new Keyframe(&root));
        }

        // add new pause after (Blank)Keyframe
        layer->insertPause(currentAnimationIdx + 2,
                           frameLength * pauseRightDuration);
      }

      // data changes from col - 1 to col + 1
      emit dataChanged(createIndex(row, col - 1), createIndex(row, col + 1));
    } else {  // current is (Blank)Keyframe
      auto nextIsFrame = qobject_cast<QPauseAnimation *>(
          root.animationAt(currentAnimationIdx + 1));

      if (val == FrameTypes::Frame) {
        if (col + 1 > layerSize || !nextIsFrame) {
          animTimeline[row].insert(col + 1, FrameTypes::EndOfFrame);
          layer->insertPause(currentAnimationIdx + 1, frameLength);
        } else {  // next is Frame and inside before PotentialFrame
          animTimeline[row].insert(col + 1, val);

          auto nextPause = static_cast<QPauseAnimation *>(
              root.animationAt(currentAnimationIdx + 1));
          nextPause->setDuration(nextPause->duration() + frameLength);
        }
      }

      // insert Keyframe after (Blank)Keyframe
      if (val == FrameTypes::Key) {
        auto currentKey = layer->currentKeyframe();
        auto newKey = new Keyframe(currentKey);
        layer->insertAnimation(currentAnimationIdx + 1, newKey);
      } else if (val == FrameTypes::BlankKey) {  // insert BlankKeyframe
        layer->insertAnimation(currentAnimationIdx + 1, new Keyframe(&root));
      }

      // data changes from col to col + 1
      emit dataChanged(createIndex(row, col), createIndex(row, col + 1));
    }
  }

  return true;
}

bool AnimationModel::removeData(const QModelIndex &index) {
  auto row = index.row();
  auto col = index.column();

  if (row > root.animationCount() || col == 0) return false;

  auto layerSize = animTimeline[row].size();
  auto layer = static_cast<Layer *>(root.animationAt(row));
  auto currentAnimation = layer->currentAnimation();
  auto currentAnimationIdx = layer->indexOfAnimation(currentAnimation);
  auto currentIsPause = qobject_cast<QPauseAnimation *>(currentAnimation);

  QPauseAnimation *pause =
      (currentIsPause) ? static_cast<QPauseAnimation *>(currentAnimation)
                       : nullptr;

  if (currentIsPause) {  // current is Frame
    // decrase current pause by one frame
    pause->setDuration(pause->duration() - frameLength);
  } else {  // current is (Blank)Keyframe
    // check for pause merge
    auto leftIsPause = qobject_cast<QPauseAnimation *>(
        layer->animationAt(currentAnimationIdx - 1));
    auto rightIsPause = qobject_cast<QPauseAnimation *>(
        layer->animationAt(currentAnimationIdx + 1));
    auto leftPause = (leftIsPause)
                         ? static_cast<QPauseAnimation *>(
                               layer->animationAt(currentAnimationIdx - 1))
                         : nullptr;
    auto rightPause = (rightIsPause)
                          ? static_cast<QPauseAnimation *>(
                                layer->animationAt(currentAnimationIdx + 1))
                          : nullptr;

    if (col - 1 != 0 && col + 1 != layerSize && leftIsPause && rightIsPause) {
      // remove right pause
      layer->removeAnimation(rightPause);
      leftPause->setDuration(leftPause->duration() + rightPause->duration());
    }
  }

  delete currentAnimation;
  animTimeline[row].removeAt(col);

  return true;
}

Qt::ItemFlags SchMatrix::AnimationModel::flags(const QModelIndex &index) const {
  return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |
         Qt::ItemIsEnabled;
}

}  // namespace SchMatrix
