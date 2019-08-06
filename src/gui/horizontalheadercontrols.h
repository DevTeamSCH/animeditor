#ifndef HORIZONTALHEADERCONTROLS_H
#define HORIZONTALHEADERCONTROLS_H

#include <QHeaderView>
#include <QTimeLine>
#include <QWidget>

namespace Ui {
class HorizontalHeaderControls;
}

namespace SchMatrix {

class HorizontalHeader;
class AnimationModel;

class HorizontalHeaderControls : public QWidget {
  Q_OBJECT

 public:
  explicit HorizontalHeaderControls(QHeaderView *parent = nullptr);
  ~HorizontalHeaderControls() override;

  void setModel(SchMatrix::AnimationModel *model);

 public slots:
  void updateFrame(int newFrame, int oldFrame);

 signals:
  void frameLengthChanged(int newFramelength, int oldFramelength,
                          int currentFrame);

 private slots:
  void updateTimeline();

  void on_resetZoom_clicked();

  void on_zoomIn_clicked();

  void on_zoomSlider_valueChanged(int value);

  void on_zoomOut_clicked();

  void on_currentFrame_valueChanged(int value);

  void on_ellapsedTime_valueChanged(double seconds);

  void on_frameRate_valueChanged(int fps);

  void on_prevKeyframe_clicked();

  void on_insertKeyframe_clicked();

  void on_nextKeyframe_clicked();

  void on_firstFrame_clicked();

  void on_prevFrame_clicked();

  void on_play_clicked();

  void on_nextFrame_clicked();

  void on_lastFrame_clicked();

  void timelineFinished();

  void timelineFrameChanged(int frame);

 private:
  Ui::HorizontalHeaderControls *ui;
  QTimeLine m_timeLine;
  SchMatrix::HorizontalHeader *m_horizontalHeader;
  int m_defaultSectionSize = 10;
  SchMatrix::AnimationModel *m_animationModel = nullptr;

  void toggleTimeline();
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADERCONTROLS_H
