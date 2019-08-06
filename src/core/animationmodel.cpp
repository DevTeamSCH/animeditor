#include "animationmodel.h"

#include <QDebug>
#include <QList>
#include <QModelIndex>
#include <QSequentialAnimationGroup>
#include <algorithm>
#include <cstdlib>
#include "config.h"
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

AnimationModel::AnimationModel(QGraphicsScene *scene, QObject *parent)
    : QAbstractTableModel(parent),
      m_scene(scene),
      m_rootAnimation(this),
      m_currentLayer(nullptr) {
  // build basic animation tree
  auto layer_1 = new SchMatrix::Layer(scene, &m_rootAnimation, "layer 1");
  m_rootAnimation.addAnimation(layer_1);
  auto keyframe = new SchMatrix::Keyframe(layer_1);
  layer_1->addAnimation(keyframe);
  setCurrentLayer(layer_1);

  // init animTimeline
  m_animTimelineRow.reserve(180 * fps);
  m_animTimelineRow.insert(0, FrameTypes::BlankKey);

  m_animTimeline.insert(0, m_animTimelineRow);
}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
    auto layer =
        static_cast<SchMatrix::Layer *>(m_rootAnimation.animationAt(section));
    return layer->objectName();
  }

  return QVariant();
}

int AnimationModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return m_rootAnimation.animationCount();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  auto longestAnim = m_rootAnimation.duration();
  auto basicAnimLength = 180 * fps;  // 3 min * FPS

  return (longestAnim > basicAnimLength) ? longestAnim : basicAnimLength;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int row = index.row();
  int col = index.column();

  switch (role) {
    case Qt::DisplayRole:
      auto colSize = m_animTimeline[row].size() - 1;
      if (col > colSize) return FrameTypes::PotentialFrame;

      return m_animTimeline[row][col];
  }

  return QVariant();
}

bool AnimationModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);

  auto longestAnim = m_rootAnimation.duration();

  if (row > m_animTimeline.size()) m_animTimeline.resize(row);

  for (int i = 0; i < count; ++i) {
    auto layer = new Layer(m_scene, &m_rootAnimation,
                           QString("layer %1").arg(++m_lastLayerNumber), row);

    m_rootAnimation.insertAnimation(row, layer);
    layer->addAnimation(new Keyframe(layer));

    m_animTimeline.insert(row, m_animTimelineRow);

    if (m_rootAnimation.animationCount() > 1 &&
        longestAnim > SchMatrix::frameLength) {
      layer->addPause(longestAnim);

      for (int i = 0; i < (longestAnim / SchMatrix::frameLength) - 1; ++i) {
        m_animTimeline[row].push_back(FrameTypes::Frame);
      }

      m_animTimeline[row].push_back(FrameTypes::EndOfFrame);
    }
  }

  for (int i = row; i < count; ++i) {
    static_cast<Layer *>(m_rootAnimation.animationAt(i))->setZValue(i);
  }

  endInsertRows();
  return true;
}

bool AnimationModel::insertColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginInsertColumns(parent, column, column + count - 1);

  for (auto &row : m_animTimeline) {
    for (int i = 0; i < count; ++i) {
      if (row.size() > column) row.resize(column);

      row.insert(column, FrameTypes::PotentialFrame);
    }
  }

  endInsertColumns();
  return true;
}

bool AnimationModel::removeRows(int row, int count, const QModelIndex &parent) {
  if (m_rootAnimation.animationCount() < count ||
      abs(m_rootAnimation.animationCount() - count) == 1)
    return false;

  beginRemoveRows(parent, row, row + count - 1);
  auto animCount = m_rootAnimation.animationCount();

  if (animCount < count) return false;

  for (int i = row; i < count; ++i) {
    auto anim = m_rootAnimation.takeAnimation(i);
    delete anim;

    m_animTimeline.removeAt(i);
  }

  for (int i = row; i < animCount; ++i) {
    static_cast<Layer *>(m_rootAnimation.animationAt(i))->setZValue(i);
  }

  endRemoveRows();
  return true;
}

bool SchMatrix::AnimationModel::setData(const QModelIndex &index,
                                        const QVariant &value, int role) {
  auto row = index.row();
  auto col = index.column();

  if (row > m_rootAnimation.animationCount()) return false;

  auto val = value.toInt();
  auto layerSize = m_animTimeline[row].size();
  auto layer = static_cast<Layer *>(m_rootAnimation.animationAt(row));
  auto currentAnimation = layer->currentAnimation();
  auto currentAnimationIdx = layer->indexOfAnimation(currentAnimation);

  QPauseAnimation *pause = qobject_cast<QPauseAnimation *>(currentAnimation);

  // set keyframe look
  if (role == Qt::UserRole) {
    auto keyframe = qobject_cast<SchMatrix::Keyframe *>(
        layer->animationAtMsec(col * SchMatrix::frameLength));

    if (!keyframe || col > m_animTimeline[row].size()) return false;

    m_animTimeline[row][col] = val;

    emit dataChanged(createIndex(row, col), createIndex(row, col));
    return true;
  }

  if (col >= layerSize) {  // setting data outside, in PotentialFrame
    int pauseDuration = 0;

    m_animTimeline[row].resize(col);

    auto &prevCell = m_animTimeline[row][col - 1];

    if (val == FrameTypes::Frame) {
      m_animTimeline[row].insert(col, FrameTypes::EndOfFrame);
      pauseDuration = m_animTimeline[row].size() - layerSize;
    } else {  // val is (Blank)Keyframe
      if (prevCell == FrameTypes::Frame) prevCell = FrameTypes::EndOfFrame;
      m_animTimeline[row].insert(col, val);
      pauseDuration = m_animTimeline[row].size() - layerSize - 1;
    }

    if (pause) {
      // replace EndOfFrame with Frame
      if (val == FrameTypes::Frame || col != layerSize)
        m_animTimeline[row][layerSize - 1] = FrameTypes::Frame;
      pause->setDuration(pause->duration() +
                         SchMatrix::frameLength * pauseDuration);
    } else if (pauseDuration > 0) {  // current is (Blank)Keyframe
      layer->addPause(SchMatrix::frameLength *
                      pauseDuration);  // Add missing pause
    }

    if (val == FrameTypes::Key) {
      auto newKey = new Keyframe(*layer->currentKeyframe());
      layer->insertAnimation(
          currentAnimationIdx + ((pause || pauseDuration == 0) ? 1 : 2),
          newKey);
    } else if (val == FrameTypes::BlankKey) {  // insert BlankKeyframe
      layer->insertAnimation(
          currentAnimationIdx + ((pause || pauseDuration == 0) ? 1 : 2),
          new Keyframe(&m_rootAnimation));
    }

    // data changes from layerSize(original size) to animTimeline[row].size()
    emit dataChanged(createIndex(row, layerSize),
                     createIndex(row, m_animTimeline[row].size()));
  } else {  // setting data inside, before potentialFrames
    if (pause) {
      if (val == FrameTypes::Frame) {
        m_animTimeline[row].insert(col, val);
        pause->setDuration(pause->duration() + SchMatrix::frameLength);
      }

      if (val == FrameTypes::BlankKey || val == FrameTypes::Key) {
        m_animTimeline[row][col] = val;

        // Frame/Pause split starts here
        // TODO find builtin algorithm
        int pauseStartIdx = col - 1;
        for (; pauseStartIdx != 0 &&
               m_animTimeline[row][pauseStartIdx] == FrameTypes::Frame;
             --pauseStartIdx) {
        }

        pauseStartIdx++;

        if (m_animTimeline[row][col - 1] == FrameTypes::Frame)
          m_animTimeline[row][col - 1] = FrameTypes::EndOfFrame;

        auto pauseLeftDuration = SchMatrix::frameLength * (col - pauseStartIdx);
        auto pauseRightDuration =
            pause->duration() - pauseLeftDuration - SchMatrix::frameLength;

        // shrink or delete current pause
        if (pauseLeftDuration == 0)
          delete pause;
        else
          pause->setDuration(pauseLeftDuration);

        // insert Keyframe inside Frame
        if (val == FrameTypes::Key) {
          auto newKey = new Keyframe(*layer->currentKeyframe());
          layer->insertAnimation(currentAnimationIdx + 1, newKey);
        } else if (val == FrameTypes::BlankKey) {  // insert BlankKeyframe
          layer->insertAnimation(currentAnimationIdx + 1,
                                 new Keyframe(&m_rootAnimation));
        }

        // add new pause after (Blank)Keyframe
        // only if pauseRightDuration is at least 1 frame long
        if (pauseRightDuration >= SchMatrix::frameLength) {
          layer->insertPause(currentAnimationIdx + 2, pauseRightDuration);
        }
      }

      // data changes from col - 1 to col + 1
      emit dataChanged(createIndex(row, col - 1), createIndex(row, col + 1));
    } else {  // current is (Blank)Keyframe
      QPauseAnimation *nextIsPause =
          (col + 1 >= layerSize)
              ? nullptr
              : qobject_cast<QPauseAnimation *>(
                    layer->animationAt(currentAnimationIdx + 1));

      if (val == FrameTypes::Frame) {
        if (col + 1 >= layerSize || !nextIsPause) {
          m_animTimeline[row].insert(col + 1, FrameTypes::EndOfFrame);
          layer->insertPause(currentAnimationIdx + 1, SchMatrix::frameLength);
        } else {  // next is Frame and inside before PotentialFrame
          m_animTimeline[row].insert(col + 1, val);

          auto nextPause = static_cast<QPauseAnimation *>(
              layer->animationAt(currentAnimationIdx + 1));
          nextPause->setDuration(nextPause->duration() +
                                 SchMatrix::frameLength);
        }
      }

      if (val == FrameTypes::Key || val == FrameTypes::BlankKey)
        m_animTimeline[row].insert(col + 1, val);

      // insert Keyframe after (Blank)Keyframe
      if (val == FrameTypes::Key) {
        auto newKey = new Keyframe(*layer->currentKeyframe());
        layer->insertAnimation(currentAnimationIdx + 1, newKey);
      } else if (val == FrameTypes::BlankKey) {  // insert BlankKeyframe
        layer->insertAnimation(currentAnimationIdx + 1,
                               new Keyframe(&m_rootAnimation));
      }

      // data changes from col to col + 1
      emit dataChanged(createIndex(row, col), createIndex(row, col + 1));
    }
  }

  emit timelineChanged();
  return true;
}

bool AnimationModel::removeData(const QModelIndex &index) {
  auto row = index.row();
  auto col = index.column();
  auto layerSize = m_animTimeline[row].size();

  if (row < 0 || row >= m_rootAnimation.animationCount() || col <= 0 ||
      col >= layerSize)
    return false;

  auto layer = static_cast<Layer *>(m_rootAnimation.animationAt(row));
  auto currentAnimation = layer->currentAnimation();
  auto currentAnimationIdx = layer->indexOfAnimation(currentAnimation);
  auto pause = qobject_cast<QPauseAnimation *>(currentAnimation);

  auto &prevCell = m_animTimeline[row][col - 1];

  if (pause) {
    // decrase current pause by one frame
    auto duration = pause->duration() - SchMatrix::frameLength;

    // shrink or delete current pause
    if (duration == 0)
      delete pause;
    else
      pause->setDuration(duration);

    if (prevCell == FrameTypes::Frame) prevCell = FrameTypes::EndOfFrame;

    // data changes from col - 1 to col
    emit dataChanged(createIndex(row, col - 1), createIndex(row, col));
  } else {  // current is (Blank)Keyframe
    // check for pause merge
    if (col - 1 != 0 && col + 1 != layerSize) {
      auto leftPause = qobject_cast<QPauseAnimation *>(
          layer->animationAt(currentAnimationIdx - 1));
      auto rightPause = qobject_cast<QPauseAnimation *>(
          layer->animationAt(currentAnimationIdx + 1));

      if (leftPause && rightPause) {
        // remove right pause
        layer->removeAnimation(rightPause);

        // pause merge
        leftPause->setDuration(leftPause->duration() + rightPause->duration());

        // delete right pause
        delete rightPause;

        prevCell = FrameTypes::Frame;
      }

      if (prevCell == FrameTypes::EndOfFrame) prevCell = FrameTypes::Frame;

      // data changes from col - 1 to col + 1
      emit dataChanged(createIndex(row, col - 1), createIndex(row, col + 1));
    } else {
      // data changes at col
      emit dataChanged(createIndex(row, col), createIndex(row, col));
    }

    delete currentAnimation;
  }

  m_animTimeline[row].removeAt(col);

  return true;
}

Qt::ItemFlags SchMatrix::AnimationModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |
         Qt::ItemIsEnabled;
}

void AnimationModel::setTime(int mscec) {
  m_rootAnimation.setCurrentTime(mscec);
}

void AnimationModel::setFrame(int frame) {
  auto oldFrame = currentFrame();
  auto lastFrame = this->lastFrame();

  m_rootAnimation.setCurrentTime(SchMatrix::frameLength * frame);

  emit frameChanged((frame > lastFrame) ? lastFrame : frame, oldFrame);
}

int AnimationModel::currentTime() const {
  auto time = m_rootAnimation.currentTime();
  return (time == m_rootAnimation.duration()) ? time - SchMatrix::frameLength
                                              : time;
}

double AnimationModel::currentTimeDouble() const {
  return currentFrame() * SchMatrix::frameLengthDouble;
}

int AnimationModel::duration() const { return m_rootAnimation.duration(); }

double AnimationModel::durationDouble() const {
  return lastFrame() * SchMatrix::frameLengthDouble;
}

int AnimationModel::currentFrame() const {
  return currentTime() / SchMatrix::frameLength;
}

int AnimationModel::lastFrame() const {
  return (m_rootAnimation.duration() / SchMatrix::frameLength) - 1;
}

Layer *AnimationModel::layerAt(int row) const {
  return static_cast<Layer *>(m_rootAnimation.animationAt(row));
}

int AnimationModel::rowSize(int row) { return m_animTimeline[row].size(); }

void AnimationModel::updateFrameLength(int newFramelength, int oldFramelength,
                                       int currentFrame) {
  for (int i = 0; i < m_rootAnimation.animationCount(); ++i) {
    auto layer = static_cast<QSequentialAnimationGroup *>(
        m_rootAnimation.animationAt(i));

    // Update layer contents
    for (int animIdx = 0; animIdx < layer->animationCount(); ++animIdx) {
      // Update keyframe
      auto currentAnim = layer->animationAt(animIdx);
      auto keyframe = qobject_cast<SchMatrix::Keyframe *>(currentAnim);

      if (keyframe) {
        // Update frameLength placeholder
        static_cast<QPauseAnimation *>(keyframe->animationAt(0))
            ->setDuration(newFramelength);

        // Update normal animations
        for (int i = 1; i < keyframe->animationCount(); ++i) {
          auto anim =
              static_cast<QVariantAnimation *>(keyframe->animationAt(i));

          // Recalc new frameLength
          auto frames = anim->duration() / oldFramelength;
          anim->setDuration(newFramelength * frames);
        }
      } else {  // Update pause
        auto pause = static_cast<QPauseAnimation *>(currentAnim);

        // Recalc new frameLength
        auto frames = pause->duration() / oldFramelength;
        pause->setDuration(newFramelength * frames);
      }
    }
  }

  // Prevent FPS change issues
  setFrame(currentFrame);
}

SchMatrix::Layer *AnimationModel::currentLayer() const {
  return m_currentLayer;
}

int AnimationModel::currentLayerIdx() const {
  return m_rootAnimation.indexOfAnimation(m_currentLayer);
}

void AnimationModel::setCurrentLayer(SchMatrix::Layer *current) {
  if (!current || m_currentLayer == current) return;

  m_currentLayer = current;
  emit currentLayerChanged(current);
}

void AnimationModel::setCurrentLayer(int layerIdx) {
  if (layerIdx < 0 || layerIdx > m_rootAnimation.animationCount()) return;

  auto layer =
      static_cast<SchMatrix::Layer *>(m_rootAnimation.animationAt(layerIdx));

  if (m_currentLayer == layer) return;

  m_currentLayer = layer;
  emit currentLayerChanged(layer);
}

}  // namespace SchMatrix
