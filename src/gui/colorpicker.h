#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QFrame>

namespace SchMatrix {

class ColorPicker : public QFrame {
  Q_OBJECT

 public:
  explicit ColorPicker(const QColor &initial, QWidget *parent = nullptr);

  // QWidget interface
  QSize minimumSizeHint() const override;

  QColor currentColor() const;
  void setCurrentColor(const QColor &currentColor);

 signals:
  void currentColorChanged(const QColor &color);

 private:
  QColor m_currentColor = Qt::white;

  // QWidget interface
 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
};

}  // namespace SchMatrix

#endif  // COLORPICKER_H
