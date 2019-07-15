#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QAbstractAnimation>
#include <QAbstractTableModel>
#include <QParallelAnimationGroup>
#include <QVector>
#include "core_global.h"
#include "layer.h"

namespace SchMatrix {

enum FrameTypes { Frame, EndOfFrame, Key, BlankKey, PotentialFrame };

class CORESHARED_EXPORT AnimationModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AnimationModel(QObject *parent = nullptr);

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
  int getTime() const;
  int getDuration() const;
  const SchMatrix::Layer *getLayer(int row = 0) const;
  int elementCount(int row);

 private:
  QParallelAnimationGroup root;  // root animation
  QVector<QVector<int>> animTimeline;
  QVector<int> animTimelineRow;
  static int lastLayerNumber;
};

}  // namespace SchMatrix

#endif  // ANIMATIONMODEL_H
