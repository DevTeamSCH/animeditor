#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QTableView>

namespace SchMatrix {

class TimelineView : public QTableView {
  Q_OBJECT

 public:
  explicit TimelineView(QWidget *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // TIMELINEVIEW_H
