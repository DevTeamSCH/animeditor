#ifndef COLORINDICATOR_H
#define COLORINDICATOR_H

#include <QWidget>

namespace Ui {
class ColorIndicator;
}

/*!
 * \brief The ColorIndicator class
 *
 * Clor indicar widget. It shows the actual drawing color
 *  and the last drawing color. If the last color clicked
 * it becomes the actual.
 */

class ColorIndicator : public QWidget
{
        Q_OBJECT
public:

        /*!
         * \brief ColorIndicator
         * \param parent
         *
         * Consructor
         */
        explicit ColorIndicator(QWidget *parent = 0);
        ~ColorIndicator();
         QSize sizeHint() const override;
private:
       // Ui::ColorIndicator *ui;
         /*!
         * \brief actual, before
         * color values
         */
        QColor actual, before;
        void mousePressEvent(QMouseEvent *) override;

        /*!
         * \brief paintEvent
         *
         * Paints two rectangle with the colors.
         */
        void paintEvent(QPaintEvent *) override;

public slots:
        /*!
         * \brief updateColor
         * \param color
         *
         * When in other widget the actual color changes
         * recieves its signal with the color.
         */
        void updateColor(QColor color);

signals:
        /*!
       * \brief colorChanged
       *
       * Fire a signal when the color changing.
       */
      void colorChanged(QColor);
};

#endif // COLORINDICATOR_H
