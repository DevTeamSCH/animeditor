#include "animationmodel.h"

#include <QDebug>
#include <QModelIndex>
#include <QSequentialAnimationGroup>
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
  layer_1->addKeyframe(keyframe);
  setCurrentLayer(layer_1);
}

AnimationModel::AnimationModel(QObject *parent) : QAbstractTableModel(parent) {}

AnimationModel::AnimationModel(const AnimationModel &other) {
  auto &rootAnim = other.m_rootAnimation;

  // Copy important member variables
  m_scene = other.m_scene;
  m_lastLayerNumber = other.m_lastLayerNumber;
  m_currentLayer = other.m_currentLayer;

  // Clone rootAnimation
  m_rootAnimation = rootAnim;
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
      auto layer =
          qobject_cast<SchMatrix::Layer *>(m_rootAnimation.animationAt(row));
      if (col * SchMatrix::frameLength >= layer->duration())
        return FrameTypes::PotentialFrame;

      return layer->keyframeAtFrame(col)->paint(col);
  }

  return QVariant();
}

bool AnimationModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);

  auto longestAnimDuration = m_rootAnimation.duration();

  for (int i = 0; i < count; ++i) {
    auto layer = new Layer(m_scene, &m_rootAnimation,
                           QString("layer %1").arg(++m_lastLayerNumber), row);

    m_rootAnimation.insertAnimation(row, layer);
    layer->addKeyframe(new Keyframe(layer));

    if (m_rootAnimation.animationCount() > 1 &&
        longestAnimDuration > SchMatrix::frameLength) {
      layer->currentKeyframe()->setDuration(longestAnimDuration);
    }
  }

  for (int i = row; i < count; ++i) {
    qobject_cast<Layer *>(m_rootAnimation.animationAt(i))->setZValue(i);
  }

  endInsertRows();
  return true;
}

bool AnimationModel::insertColumns(int column, int count,
                                   const QModelIndex &parent) {
  beginInsertColumns(parent, column, column + count - 1);

  // TODO extend editable range

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
  }

  for (int i = row; i < animCount; ++i) {
    qobject_cast<Layer *>(m_rootAnimation.animationAt(i))->setZValue(i);
  }

  endRemoveRows();
  return true;
}

bool SchMatrix::AnimationModel::setData(const QModelIndex &index,
                                        const QVariant &value, int role) {
  auto row = index.row();
  auto col = index.column();

  auto val = value.toInt();
  auto layer = qobject_cast<Layer *>(m_rootAnimation.animationAt(row));
  auto layerFrameDuration = layer->duration() / SchMatrix::frameLength;

  if (row > m_rootAnimation.animationCount() || col < 0) return false;

  auto currentKeyframe = layer->currentKeyframe();
  auto currentKeyframeIdx = layer->indexOfAnimation(currentKeyframe);

  if (col >= layerFrameDuration) {  // setting data outside, in PotentialFrame
    if (val == FrameTypes::Key || val == FrameTypes::BlankKey) {
      if (currentKeyframe->empty() || val == FrameTypes::BlankKey) {
        layer->addKeyframe(new Keyframe(nullptr, col), col);
      } else {
        auto newKey = new Keyframe(*currentKeyframe);
        newKey->setStartFrame(col);
        layer->addKeyframe(newKey, col);
      }

      currentKeyframe->setDuration(currentKeyframe->duration() +
                                   (col - currentKeyframe->endFrame()) *
                                       SchMatrix::frameLength);
    } else if (val == FrameTypes::Frame) {
      currentKeyframe->setDuration(currentKeyframe->duration() +
                                   (col - currentKeyframe->endFrame() + 1) *
                                       SchMatrix::frameLength);
    }

    // data changes from layerSize(original size) to animTimeline[row].size()
    emit dataChanged(createIndex(row, currentKeyframe->endFrame()),
                     createIndex(row, col));
  } else {  // setting data inside, before potentialFrames
    if (val == FrameTypes::Frame) {
      currentKeyframe->setDuration(currentKeyframe->duration() +
                                   SchMatrix::frameLength);

      layer->updateFrameToKeyframe(currentKeyframe);

      emit dataChanged(createIndex(row, currentKeyframe->endFrame()),
                       createIndex(row, layerFrameDuration));
    } else if (val == FrameTypes::Key || val == FrameTypes::BlankKey) {
      if (col == currentKeyframe->startFrame()) {
        if (currentKeyframe->endFrame() * SchMatrix::frameLength ==
            layer->duration()) {
          if (currentKeyframe->empty() || val == FrameTypes::BlankKey) {
            layer->insertKeyframe(currentKeyframeIdx + 1,
                                  new Keyframe(nullptr, col + 1), col + 1);
          } else {
            auto newKey = new Keyframe(*layer->currentKeyframe());
            newKey->setDuration(SchMatrix::frameLength);
            layer->insertKeyframe(currentKeyframeIdx + 1, newKey, col + 1);
          }

          emit dataChanged(createIndex(row, col), createIndex(row, col + 1));
        } else if (currentKeyframe->duration() > SchMatrix::frameLength) {
          currentKeyframe->setDuration(currentKeyframe->duration() -
                                       SchMatrix::frameLength);

          if (currentKeyframe->empty() || val == FrameTypes::BlankKey) {
            layer->insertKeyframe(currentKeyframeIdx,
                                  new Keyframe(nullptr, col), col);
          } else {
            auto newKey = new Keyframe(*layer->currentKeyframe());
            newKey->setDuration(SchMatrix::frameLength);
            layer->insertKeyframe(currentKeyframeIdx, newKey, col);
          }

          emit dataChanged(createIndex(row, col - 1),
                           createIndex(row, col + 1));
        }
      } else if (col == currentKeyframe->endFrame() - 1) {
        if (currentKeyframe->duration() > SchMatrix::frameLength)
          currentKeyframe->setDuration(currentKeyframe->duration() -
                                       SchMatrix::frameLength);

        if (currentKeyframe->empty() || val == FrameTypes::BlankKey) {
          layer->insertKeyframe(currentKeyframeIdx + 1,
                                new Keyframe(nullptr, col), col);
        } else {
          auto newKey = new Keyframe(*layer->currentKeyframe());
          newKey->setStartFrame(col);
          newKey->setDuration(SchMatrix::frameLength);
          layer->insertKeyframe(currentKeyframeIdx + 1, newKey, col);
        }

        emit dataChanged(createIndex(row, col), createIndex(row, col - 1));
      } else {
        auto duration = currentKeyframe->duration();
        currentKeyframe->setDuration((col - currentKeyframe->startFrame()) *
                                     SchMatrix::frameLength);

        if (currentKeyframe->empty() || val == FrameTypes::BlankKey) {
          auto newKey = new Keyframe(nullptr, col);
          newKey->setDuration(duration - currentKeyframe->duration());
          layer->insertKeyframe(currentKeyframeIdx + 1, newKey, col);
        } else {
          auto newKey = new Keyframe(*layer->currentKeyframe());
          newKey->setStartFrame(col);
          newKey->setDuration(duration - currentKeyframe->duration());
          layer->insertKeyframe(currentKeyframeIdx + 1, newKey, col);
        }

        emit dataChanged(createIndex(row, col - 1), createIndex(row, col));
      }
    }
  }

  emit timelineChanged();
  return true;
}

bool AnimationModel::removeData(const QModelIndex &index) {
  auto row = index.row();
  auto col = index.column();
  auto layer = qobject_cast<Layer *>(m_rootAnimation.animationAt(row));
  auto layerFrameDuration = layer->duration() / SchMatrix::frameLength;
  auto currentKeyframe = layer->currentKeyframe();

  if (row > m_rootAnimation.animationCount() ||
      (m_rootAnimation.animationCount() == 1 &&
       currentKeyframe->duration() == SchMatrix::frameLength) ||
      col > layerFrameDuration || col < 0)
    return false;

  if (currentKeyframe->duration() > SchMatrix::frameLength) {
    currentKeyframe->setDuration(currentKeyframe->duration() -
                                 SchMatrix::frameLength);
  } else if (currentKeyframe->duration() == SchMatrix::frameLength) {
    layer->deleteKeyframe(currentKeyframe);
  }

  layer->updateFrameToKeyframe(currentKeyframe);

  emit dataChanged(createIndex(row, currentKeyframe->startFrame()),
                   createIndex(row, layerFrameDuration));
  emit timelineChanged();
  return true;
}

Qt::ItemFlags SchMatrix::AnimationModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |
         Qt::ItemIsEnabled;
}

void AnimationModel::setTime(int mscec) {
  // Workaround
  if (m_rootAnimation.state() == m_rootAnimation.Stopped) {
    m_rootAnimation.start();
    m_rootAnimation.pause();
  }

  m_rootAnimation.setCurrentTime(mscec);
}

void AnimationModel::setFrame(int frame) {
  auto oldFrame = currentFrame();
  auto lastFrame = this->lastFrame();

  // Workaround
  if (m_rootAnimation.state() == m_rootAnimation.Stopped) {
    m_rootAnimation.start();
    m_rootAnimation.pause();
  }

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

int AnimationModel::rowSize(int row) const {
  return m_rootAnimation.animationAt(row)->duration() / SchMatrix::frameLength;
}

void AnimationModel::updateFrameLength(int newFramelength, int oldFramelength,
                                       int currentFrame) {
  /*
for (int i = 0; i < m_rootAnimation.animationCount(); ++i) {
auto layer = qobject_cast<Layer *>(m_rootAnimation.animationAt(i));


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
  }
}

}

// Prevent FPS change issues
setFrame(currentFrame);
*/
}

const QParallelAnimationGroup *AnimationModel::rootAnimation() const {
  return &m_rootAnimation;
}

QParallelAnimationGroup *AnimationModel::rootAnimation() {
  return &m_rootAnimation;
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

bool AnimationModel::createClassicTween() {
  auto leftKeyframe = m_currentLayer->currentKeyframe();
  auto rigthKeyframe = m_currentLayer->nextKeyframe();

  if (!leftKeyframe || !rigthKeyframe ||
      leftKeyframe->canInterpolate() == false ||
      rigthKeyframe->canInterpolate() == false)
    return false;


  leftKeyframe->interpolate(rigthKeyframe);

  m_rootAnimation.setCurrentTime(m_rootAnimation.currentTime());
  return true;
}

}  // namespace SchMatrix
