#include "horizontalheadercontrols.h"
#include "ui_horizontalheadercontrols.h"

#include <QDebug>
#include <QSignalBlocker>
#include "config.h"
#include "horizontalheader.h"

namespace SchMatrix {

HorizontalHeaderControls::HorizontalHeaderControls(QHeaderView *parent)
    : QWidget(parent),
      ui(new Ui::HorizontalHeaderControls),
      timeLine(SchMatrix::frameLength, this),
      parentHeader(static_cast<SchMatrix::HorizontalHeader *>(parent)),
      defaultSectionSize(10) {
  ui->setupUi(this);

  timeLine.setUpdateInterval(SchMatrix::fps);
  timeLine.setFrameRange(0, 1);
}

HorizontalHeaderControls::~HorizontalHeaderControls() { delete ui; }

void HorizontalHeaderControls::setModel(AnimationModel *model) {
  animModel = model;

  connect(animModel, SIGNAL(frameChanged(int)), this, SLOT(updateFrame(int)));
  connect(animModel, SIGNAL(timelineChanged()), this, SLOT(updateTimeline()));
}

void HorizontalHeaderControls::updateFrame(int frame) {
  // Prevent recursion
  QSignalBlocker b(ui->currentFrame);
  QSignalBlocker b2(ui->ellapsedTime);

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  ui->ellapsedTime->setValue(animModel->getTimeDouble() / 1000.0);
}

void HorizontalHeaderControls::updateTimeline() {
  auto lastFrame = animModel->getLastFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setMaximum(lastFrame + 1);
  ui->ellapsedTime->setMaximum(animModel->getDurationDouble() / 1000.0);
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

  // Prevent recursion
  QSignalBlocker b(animModel);
  QSignalBlocker b2(ui->ellapsedTime);

  animModel->setFrame(frame);
  timeLine.setCurrentTime(animModel->getTime());
  ui->ellapsedTime->setValue(animModel->getTimeDouble() / 1000);
  parentHeader->updateFrame(frame);
}

void SchMatrix::HorizontalHeaderControls::on_ellapsedTime_valueChanged(
    double seconds) {
  // Prevent recursion
  QSignalBlocker b(animModel);
  QSignalBlocker b2(ui->currentFrame);

  animModel->setTime(qRound(seconds * 1000));
  timeLine.setCurrentTime(animModel->getTime());
  auto frame = animModel->getCurrentFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  parentHeader->updateFrame(frame);
}

void SchMatrix::HorizontalHeaderControls::on_frameRate_valueChanged(int fps) {
  timeLine.setUpdateInterval(fps);
  SchMatrix::fps = fps;
  SchMatrix::frameLength = 1000 / SchMatrix::fps;

  emit fpsChanged(fps);
}

void SchMatrix::HorizontalHeaderControls::on_prevKeyframe_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_insertKeyframe_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_nextKeyframe_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_firstFrame_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_prevFrame_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_play_clicked() {
  if (timeLine.state() == QTimeLine::Running) {
    timeLine.setPaused(true);
    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-start.svg"));
  } else {
    timeLine.start();
    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-pause.svg"));
  }
}

void SchMatrix::HorizontalHeaderControls::on_nextFrame_clicked() {}

void SchMatrix::HorizontalHeaderControls::on_lastFrame_clicked() {}
