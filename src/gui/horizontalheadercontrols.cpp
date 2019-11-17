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
      m_timeLine(SchMatrix::frameLength, this),
      m_horizontalHeader(static_cast<SchMatrix::HorizontalHeader *>(parent)) {
  ui->setupUi(this);

  // Timeline init
  m_timeLine.setUpdateInterval(SchMatrix::fps);
  m_timeLine.setFrameRange(0, 1);
  m_timeLine.setCurveShape(QTimeLine::LinearCurve);

  connect(&m_timeLine, SIGNAL(finished()), this, SLOT(timelineFinished()));
  connect(&m_timeLine, SIGNAL(frameChanged(int)), this,
          SLOT(timelineFrameChanged(int)));
}

HorizontalHeaderControls::~HorizontalHeaderControls() { delete ui; }

void HorizontalHeaderControls::setModel(AnimationModel *model) {
  if (model == m_animationModel) return;

  if (m_animationModel) {
    disconnect(m_animationModel, SIGNAL(frameChanged(int, int)), this,
               SLOT(updateFrame(int, int)));
    disconnect(m_animationModel, SIGNAL(timelineChanged()), this,
               SLOT(updateTimeline()));
  }

  if (model) {
    m_animationModel = model;

    connect(m_animationModel, SIGNAL(frameChanged(int, int)), this,
            SLOT(updateFrame(int, int)));
    connect(m_animationModel, SIGNAL(timelineChanged()), this,
            SLOT(updateTimeline()));

    // Only connect this once
    connect(this, SIGNAL(frameLengthChanged(int, int, int)), m_animationModel,
            SLOT(updateFrameLength(int, int, int)), Qt::UniqueConnection);
  }
}

void HorizontalHeaderControls::updateFrame(int newFrame, int) {
  // Prevent recursion
  QSignalBlocker b(ui->currentFrame);
  QSignalBlocker b2(ui->ellapsedTime);
  QSignalBlocker b3(m_timeLine);

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(newFrame + 1);
  ui->ellapsedTime->setValue(m_animationModel->currentTimeDouble() / 1000.0);

  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  m_timeLine.setCurrentTime(m_animationModel->currentTime());
}

void HorizontalHeaderControls::updateTimeline() {
  auto lastFrame = m_animationModel->lastFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setMaximum(lastFrame + 1);
  ui->ellapsedTime->setMaximum(m_animationModel->durationDouble() / 1000.0);

  // Update timeline
  m_timeLine.setDuration(m_animationModel->duration());
  m_timeLine.setFrameRange(0, lastFrame);
}

void HorizontalHeaderControls::on_resetZoom_clicked() {
  ui->zoomSlider->setValue(m_defaultSectionSize);
}

void HorizontalHeaderControls::on_zoomIn_clicked() {
  ui->zoomSlider->setValue(ui->zoomSlider->value() + 5);
}

void HorizontalHeaderControls::on_zoomSlider_valueChanged(int value) {
  m_horizontalHeader->setDefaultSectionSize(value);
}

void HorizontalHeaderControls::on_zoomOut_clicked() {
  ui->zoomSlider->setValue(ui->zoomSlider->value() - 5);
}

void HorizontalHeaderControls::on_currentFrame_valueChanged(int value) {
  auto frame = value - 1;
  auto oldFrame = m_animationModel->currentFrame();

  // Prevent recursion
  QSignalBlocker b(m_animationModel);
  QSignalBlocker b2(ui->ellapsedTime);
  QSignalBlocker b3(m_timeLine);

  m_animationModel->setFrame(frame);
  m_timeLine.setCurrentTime(m_animationModel->currentTime());
  ui->ellapsedTime->setValue(m_animationModel->currentTimeDouble() / 1000);
  m_horizontalHeader->updateFrame(frame, oldFrame);
}

void HorizontalHeaderControls::on_ellapsedTime_valueChanged(double seconds) {
  // Prevent recursion
  QSignalBlocker b(m_animationModel);
  QSignalBlocker b2(ui->currentFrame);
  QSignalBlocker b3(m_timeLine);

  auto oldFrame = m_animationModel->currentFrame();

  m_animationModel->setTime(qRound(seconds * 1000));
  m_timeLine.setCurrentTime(m_animationModel->currentTime());
  auto frame = m_animationModel->currentFrame();

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  m_horizontalHeader->updateFrame(frame, oldFrame);
}

void HorizontalHeaderControls::on_frameRate_valueChanged(int fps) {
  /*
// Udate interval is in milliseconds
m_timeLine.setUpdateInterval(1000 / fps);

auto oldFrameLength = SchMatrix::frameLength;
auto currentFrame = m_animationModel->currentFrame();

SchMatrix::fps = fps;
SchMatrix::frameLength = 1000 / SchMatrix::fps;
SchMatrix::frameLengthDouble = 1000.0 / SchMatrix::fps;

emit frameLengthChanged(SchMatrix::frameLength, oldFrameLength, currentFrame);
*/
}

void HorizontalHeaderControls::on_prevKeyframe_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = m_animationModel->currentLayer();
  auto prevKeyframe = layer->prevKeyframe();

  if (!prevKeyframe) return;

  auto keyframePos = layer->animFramePosition(prevKeyframe);

  m_animationModel->setFrame(keyframePos);
}

void HorizontalHeaderControls::on_insertKeyframe_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = m_animationModel->currentLayer();
  auto layerIdx = m_animationModel->currentLayerIdx();
  auto index =
      m_animationModel->index(layerIdx, m_animationModel->currentFrame());

  // Set data and check if current Keyframe is empty
  m_animationModel->setData(index, (layer->currentKeyframe()->empty())
                                       ? SchMatrix::FrameTypes::BlankKey
                                       : SchMatrix::FrameTypes::Key);

  m_animationModel->setFrame(index.column() + 1);
}

void HorizontalHeaderControls::on_nextKeyframe_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto layer = m_animationModel->currentLayer();
  auto nextKeyframe = layer->nextKeyframe();

  if (!nextKeyframe) return;

  auto keyframePos = layer->animFramePosition(nextKeyframe);

  m_animationModel->setFrame(keyframePos);
}

void HorizontalHeaderControls::on_firstFrame_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();
  m_animationModel->setFrame(0);
}

void HorizontalHeaderControls::on_prevFrame_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto currentFrame = m_animationModel->currentFrame();
  auto prevFrame = (currentFrame == 0) ? 0 : currentFrame - 1;
  m_animationModel->setFrame(prevFrame);
}

void HorizontalHeaderControls::on_play_clicked() { toggleTimeline(); }

void HorizontalHeaderControls::on_nextFrame_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto currentFrame = m_animationModel->currentFrame();
  auto lastFrame = m_animationModel->lastFrame();
  auto nextFrame = (currentFrame > lastFrame) ? lastFrame : currentFrame + 1;

  m_animationModel->setFrame(nextFrame);
}

void HorizontalHeaderControls::on_lastFrame_clicked() {
  if (m_timeLine.state() == QTimeLine::Running) toggleTimeline();

  auto lastFrame = m_animationModel->lastFrame();
  m_animationModel->setFrame(lastFrame);
}

void HorizontalHeaderControls::toggleTimeline() {
  if (m_timeLine.state() == QTimeLine::Running) {
    m_timeLine.setPaused(true);
    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-start.svg"));
  } else {
    if (m_timeLine.state() == QTimeLine::NotRunning &&
        m_animationModel->currentFrame() == m_animationModel->lastFrame())
      m_timeLine.start();
    else
      m_timeLine.resume();

    ui->play->setIcon(QIcon(
        ":/resources/breeze-icons/icons/actions/16/media-playback-pause.svg"));
  }
}

void HorizontalHeaderControls::timelineFinished() {
  ui->play->setIcon(QIcon(
      ":/resources/breeze-icons/icons/actions/16/media-playback-start.svg"));
}

void HorizontalHeaderControls::timelineFrameChanged(int frame) {
  qDebug() << "timeline" << frame;

  auto oldFrame = m_animationModel->currentFrame();

  // Prevent recursion
  QSignalBlocker b(m_animationModel);
  QSignalBlocker b1(ui->currentFrame);
  QSignalBlocker b2(ui->ellapsedTime);

  m_animationModel->setFrame(frame);

  // + 1 because spinner starts at 1 not 0
  ui->currentFrame->setValue(frame + 1);
  ui->ellapsedTime->setValue(m_animationModel->currentTimeDouble() / 1000.0);
  m_horizontalHeader->updateFrame(frame, oldFrame);
}

}  // namespace SchMatrix
