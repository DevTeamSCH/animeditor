#ifndef TIMELINEMENU_H
#define TIMELINEMENU_H

#include <QMenu>

namespace SchMatrix {

enum MenuEntry {
  CreateClassicTween,
  InsertFrame,
  RemoveFrame,
  InsertKeyframe,
  InsertBlankKeyframe,
  ClearFrames,
  SelectAllFrames
};

class TimelineMenu : public QMenu {
  Q_OBJECT

 public:
  explicit TimelineMenu(QWidget *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // TIMELINEMENU_H
