#include "timelinemenu.h"

namespace SchMatrix {

TimelineMenu::TimelineMenu(QWidget *parent) : QMenu(parent) {
  addAction(tr("Create Classic Tween"))->setData(MenuEntry::CreateClassicTween);
  addSeparator();
  addAction(tr("Insert Frame"))->setData(MenuEntry::InsertFrame);
  addAction(tr("Remove Frame"))->setData(MenuEntry::RemoveFrame);
  addSeparator();
  addAction(tr("Insert Keyframe"))->setData(MenuEntry::InsertKeyframe);
  addAction(tr("Insert Blank Keyframe"))
      ->setData(MenuEntry::InsertBlankKeyframe);
  addSeparator();
  addAction(tr("Clear Frames"))->setData(MenuEntry::ClearFrames);
  addAction(tr("Select All Frames"))->setData(MenuEntry::SelectAllFrames);
}

}  // namespace SchMatrix
