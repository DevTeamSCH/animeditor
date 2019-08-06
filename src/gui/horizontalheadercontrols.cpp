#include "horizontalheadercontrols.h"
#include "ui_horizontalheadercontrols.h"

#include <QDebug>
#include <QSignalBlocker>
#include "animationmodel.h"
#include "config.h"
#include "horizontalheader.h"
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

HorizontalHeaderControls::HorizontalHeaderControls(QHeaderView *parent)
    : QWidget(parent),
      ui(new Ui::HorizontalHeaderControls),
      timeLine(SchMatrix::frameLength, this),
      parentHeader(static_cast<SchMatrix::HorizontalHeader *>(parent)),
      defaultSectionSize(10),
      animModel(nullptr) {
  ui->setupUi(this);

  // Timeline init
  timeLine.setUpdateInterval(SchMatrix::fps);
  timeLine.setFrameRange(0, 1);
  timeLine.setCurveShape(QTimeLine::LinearCurve);

  connect(&timeLine, SIGNAL(finished()), this, SLOT(timelineFinished()));
  connect(&timeLine, SIGNAL(frameChanged(int)), this,
          SLOT(timelineFrameChanged(int)));
}

HorizontalHeaderControls::~HorizontalHeaderControls() { delete ui; }

void HorizontalHeaderControls::setModel(AnimationModel *model) {
  if (model == animModel) return;

  if (animModel) {
    disconnect(animModel, SIGNAL(frameChanged(int, int)), this,
               SLOT(updateFrame(int, int)));
    disconnect(animModel, SIGNAL(timelineChanged()), this,
               SLOT(updateTimeline()));
  }

  if (model) {
    animModel = model;

    connect(animModel, SIGNAL(frameChanged(int, int)), this,
            SLOT(updateFrame(int, int)));
    connect(animModel, SIGNAL(timelineChanged()), this, SLOT(updateTimeline()));

    // Only connect this once
    connect(this, SIGNAL(frameLengthChanged(int, int, int)), animModel,
            SLOT(updateFrameLength(int, int, int)), Qt::UniqueConnection);
  }
}

void HorizontalHeaderControls::updateFrame(int newFrame, int oldFrame) {
  // Prevent recursion
  QSignalBlocker b(ui->currentFrame);
  QSignalBlocker b2(ui->ellapsedTime);
  QSignalBlocker b3(timeLine);

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(newFrame + 1);
  ui->ellapsedTime->setValue(animModel->currentTimeDouble() / 1000.0);

  if (timeLine.state() == QTimeLine::Running) toggleTimeline();
  timeLine.setCurrentTime(animModel->currentTime());
}

void HorizontalHeaderControls::updateTimeline() {
  auto lastFrame = animModel->lastFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setMaximum(lastFrame + 1);
  ui->ellapsedTime->setMaximum(animModel->durationDouble() / 1000.0);

  // Update timeline
  timeLine.setDuration(animModel->duration());
  timeLine.setFrameRange(0, lastFrame);
}

}  // namespace SchMatrix

void SchMatrix::HorizontalHeaderControls::on_resetZoom_clicked() {
  ui->zoomSlider->setValue(defaultSectionSize);
}

void SchMatrix::HorizontalHeaderControls::on_zoomIn_clicked() {
  ui->zoomSlider->setValue(ui->zoomSlider->value() + 5);
}

void SchMatrix::HorizontalHeaderControls::on_zoomSlider_valueChanged(
    int value) {
  parentHeader->setDefaultSectionSize(value);
}

void SchMatrix::HorizontalHeaderControls::on_zoomOut_clicked() {
  ui->zoomSlider->setValue(ui->zoomSlider->value() - 5);
}

void SchMatrix::HorizontalHeaderControls::on_currentFrame_valueChanged(
    int val) {
  auto frame = val - 1;
  auto oldFrame = animModel->currentFrame();

  // Prevent recursion
  QSignalBlocker b(animModel);
  QSignalBlocker b2(ui->ellapsedTime);
  QSignalBlocker b3(timeLine);

  animModel->setFrame(frame);
  timeLine.setCurrentTime(animModel->currentTime());
  ui->ellapsedTime->setValue(animModel->currentTimeDouble() / 1000);
  parentHeader->updateFrame(frame, oldFrame);
}

void SchMatrix::HorizontalHeaderControls::on_ellapsedTime_valueChanged(
    double seconds) {
  // Prevent recursion
  QSignalBlocker b(animModel);
  QSignalBlocker b2(ui->currentFrame);
  QSignalBlocker b3(timeLine);

  auto oldFrame = animModel->currentFrame();

  animModel->setTime(qRound(seconds * 1000));
  timeLine.setCurrentTime(animModel->currentTime());
  auto frame = animModel->currentFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  parentHeader->updateFrame(frame, oldFrame);
}

void SchMatrix::HorizontalHeaderControls::on_frameRate_valueChanged(int fps) {
  // Udate interval is in milliseconds
  timeLine.setUpdateInterval(1000 / fps);

  auto oldFrameLength = SchMatrix::frameLength;
  auto currentFrame = animModel->currentFrame();

  SchMatrix::fps = fps;
  SchMatrix::frameLength = 1000 / SchMatrix::fps;
  SchMatrix::frameLengthDouble = 1000.0 / SchMatrix::fps;

  emit frameLengthChanged(SchMatrix::frameLength, oldFrameLength, currentFrame);
}

void SchMatrix::HorizontalHeaderControls::on_prevKeyframe_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = animModel->currentLayer();
  auto prevKeyframe = layer->prevKeyframe();

  if (!prevKeyframe) return;

  auto keyframePos = layer->animFramePosition(prevKeyframe);

  animModel->setFrame(keyframePos);
}

void SchMatrix::HorizontalHeaderControls::on_insertKeyframe_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = animModel->currentLayer();
  auto layerIdx = animModel->currentLayerIdx();
  auto index = animModel->index(layerIdx, animModel->currentFrame());

  // Set data and check if current Keyframe is empty
  animModel->setData(index, (layer->currentKeyframe()->empty())
                                ? SchMatrix::FrameTypes::BlankKey
                                : SchMatrix::FrameTypes::Key);

  animModel->setFrame(index.column() + 1);
}

void SchMatrix::HorizontalHeaderControls::on_nextKeyframe_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = animModel->currentLayer();
  auto nextKeyframe = layer->nextKeyframe();

  if (!nextKeyframe) return;

  auto keyframePos = layer->animFramePosition(nextKeyframe);

  animModel->setFrame(keyframePos);
}

void SchMatrix::HorizontalHeaderControls::on_firstFrame_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();
  animModel->setFrame(0);
}

void SchMatrix::HorizontalHeaderControls::on_prevFrame_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto currentFrame = animModel->currentFrame();
  auto prevFrame = (currentFrame == 0) ? 0 : currentFrame - 1;
  animModel->setFrame(prevFrame);
}

void SchMatrix::HorizontalHeaderControls::on_play_clicked() {
  toggleTimeline();
}

void SchMatrix::HorizontalHeaderControls::on_nextFrame_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto currentFrame = animModel->currentFrame();
  auto lastFrame = animModel->lastFrame();
  auto nextFrame = (currentFrame > lastFrame) ? lastFrame : currentFrame + 1;

  animModel->setFrame(nextFrame);
}

void SchMatrix::HorizontalHeaderControls::on_lastFrame_clicked() {
  if (timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto lastFrame = animModel->lastFrame();
  animModel->setFrame(lastFrame);
}

void SchMatrix::HorizontalHeaderControls::toggleTimeline() {
  if (timeLine.state() == QTimeLine::Running) {
    timeLine.setPaused(true);
    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-start.svg"));
  } else {
    if (timeLine.state() == QTimeLine::NotRunning &&
        animModel->currentFrame() == animModel->lastFrame())
      timeLine.start();
    else
      timeLine.resume();

    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-pause.svg"));
  }
}

void SchMatrix::HorizontalHeaderControls::timelineFinished() {
  ui->play->setIcon(QIcon(
      ":/resources/breeze-icons/icons/actions/16/media-playback-start.svg"));
}

void SchMatrix::HorizontalHeaderControls::timelineFrameChanged(int frame) {
  qDebug() << "timeline" << frame;

  auto oldFrame = animModel->currentFrame();

  // Prevent recursion
  QSignalBlocker b(animModel);
  QSignalBlocker b1(ui->currentFrame);
  QSignalBlocker b2(ui->ellapsedTime);

  animModel->setFrame(frame);

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  ui->ellapsedTime->setValue(animModel->currentTimeDouble() / 1000.0);
  parentHeader->updateFrame(frame, oldFrame);
}
