#include "timelinemenu.h"

namespace SchMatrix {

TimelineMenu::TimelineMenu(QWidget *parent) : QMenu(parent) {
  addAction(tr("Create Classic Tween"));
  addSeparator();
  addAction(tr("Insert Frame"));
  addAction(tr("Remove Frame"));
  addSeparator();
  addAction(tr("Insert Keyframe"));
  addAction(tr("Insert Blank Keyframe"));
  addSeparator();
  addAction(tr("Clear Frames"));
  addAction(tr("Select All Frames"));
}

}  // namespace SchMatrix
