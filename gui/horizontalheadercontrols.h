#ifndef HORIZONTALHEADERCONTROLS_H
#define HORIZONTALHEADERCONTROLS_H

#include <QHeaderView>
#include <QTimeLine>
#include <QWidget>
#include "animationmodel.h"

namespace Ui {
class HorizontalHeaderControls;
}

namespace SchMatrix {
class HorizontalHeader;
}

namespace SchMatrix {

class HorizontalHeaderControls : public QWidget {
  Q_OBJECT

 public:
  explicit HorizontalHeaderControls(QHeaderView *parent = nullptr);
  ~HorizontalHeaderControls();

  void setModel(SchMatrix::AnimationModel *model);

 public slots:
  void updateFrame(int frame);

 signals:
  void fpsChanged(int fps);

 private slots:
  void updateTimeline();

  void on_resetZoom_clicked();

  void on_zoomIn_clicked();

  void on_zoomSlider_valueChanged(int value);

  void on_zoomOut_clicked();

  void on_currentFrame_valueChanged(int arg1);

  void on_ellapsedTime_valueChanged(double arg1);

  void on_frameRate_valueChanged(int arg1);

  void on_prevKeyframe_clicked();

  void on_insertKeyframe_clicked();

  void on_nextKeyframe_clicked();

  void on_lastFrame_clicked();

  void on_firstFrame_clicked();

  void on_prevFrame_clicked();

  void on_play_clicked();

  void on_nextFrame_clicked();

 private:
  Ui::HorizontalHeaderControls *ui;
  QTimeLine timeLine;
  SchMatrix::HorizontalHeader *parentHeader;
  int defaultSectionSize;
  SchMatrix::AnimationModel *animModel;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADERCONTROLS_H
