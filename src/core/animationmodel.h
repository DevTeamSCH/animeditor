#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QAbstractAnimation>
#include <QAbstractTableModel>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QVector>
#include "core_global.h"

namespace SchMatrix {

class Layer;

enum FrameTypes {
  Frame,
  EndOfFrame,
  Key,
  BlankKey,
  PotentialFrame,
  TweenedFrame
};

class CORESHARED_EXPORT AnimationModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AnimationModel(QGraphicsScene *scene, QObject *parent = nullptr);
  explicit AnimationModel(const AnimationModel &other);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  // Add data:
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool insertColumns(int column, int count,
                     const QModelIndex &parent = QModelIndex()) override;

  // Remove data:
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

  // QAbstractItemModel interface
  // Used for Frame insertion, addition, modification
  // Not used for deletion!
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  // Used for Frame deletion only
  bool removeData(const QModelIndex &index);

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void setTime(int mscec);
  void setFrame(int frame);
  int currentTime() const;
  double currentTimeDouble() const;
  int duration() const;
  double durationDouble() const;
  int currentFrame() const;
  int lastFrame() const;
  SchMatrix::Layer *layerAt(int row = 0) const;
  int rowSize(int row) const;
  SchMatrix::Layer *currentLayer() const;
  int currentLayerIdx() const;
  void setCurrentLayer(SchMatrix::Layer *current);
  void setCurrentLayer(int layerIdx);
  bool createClassicTween();
  const QParallelAnimationGroup *rootAnimation() const;
  QParallelAnimationGroup *rootAnimation();

 public slots:
  void updateFrameLength(int newFramelength, int oldFramelength,
                         int currentFrame);

 signals:
  void frameChanged(int newFrame, int oldFrame);
  void timelineChanged();
  void currentLayerChanged(SchMatrix::Layer *current);

 private:
  QGraphicsScene *m_scene;
  QParallelAnimationGroup m_rootAnimation;
  QVector<QVector<int>> m_animTimeline;
  QVector<int> m_animTimelineRow;
  quint32 m_lastLayerNumber = 1;
  SchMatrix::Layer *m_currentLayer;
};

}  // namespace SchMatrix

#endif  // ANIMATIONMODEL_H
