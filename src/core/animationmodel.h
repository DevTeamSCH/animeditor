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

enum FrameTypes { Frame, EndOfFrame, Key, BlankKey, PotentialFrame };

class CORESHARED_EXPORT AnimationModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AnimationModel(QGraphicsScene *scene, QObject *parent = nullptr);

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
  int getTime() const;
  double getTimeDouble() const;
  int getDuration() const;
  double getDurationDouble() const;
  int getCurrentFrame() const;
  int getLastFrame() const;
  SchMatrix::Layer *getLayer(int row = 0) const;
  int elementCount(int row);
  QGraphicsScene *getScene();
  SchMatrix::Layer *getCurrentLayer() const;
  void setCurrentLayer(SchMatrix::Layer *current);
  void setCurrentLayer(int layerIdx);
  int getCurrentLayerIdx() const;

 public slots:
  void updateFrameLength(int newFramelength, int oldFramelength,
                         int currentFrame);

 signals:
  void frameChanged(int newFrame, int oldFrame);
  void timelineChanged();
  void currentLayerChanged(SchMatrix::Layer *current);

 private:
  QGraphicsScene *scene;
  QParallelAnimationGroup root;  // root animation
  QVector<QVector<int>> animTimeline;
  QVector<int> animTimelineRow;
  int lastLayerNumber = 1;
  SchMatrix::Layer *currentLayer;
};

}  // namespace SchMatrix

#endif  // ANIMATIONMODEL_H