#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <QWidget>

/**
 * \brief Display an analog widget that allows the selection of a HSV color
 *
 * It has an outer wheel to select the Hue and an intenal square to select
 * Saturation and Lightness.
 */
class ColorWheel : public QWidget
{
        Q_OBJECT

        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged DESIGNABLE true STORED false )
        Q_PROPERTY(qreal hue READ hue WRITE setHue DESIGNABLE false )
        Q_PROPERTY(qreal saturation READ saturation WRITE setSaturation DESIGNABLE false )
        Q_PROPERTY(qreal value READ value WRITE setValue DESIGNABLE false )
        Q_PROPERTY(unsigned wheelWidth READ wheelWidth WRITE setWheelWidth DESIGNABLE true )

public:


        explicit ColorWheel(QWidget *parent = 0);
        ~ColorWheel();

        /// Get current color
        QColor color() const;

        virtual QSize sizeHint() const override;

        /// Get current hue in the range [0-1]
        qreal hue() const;

        /// Get current saturation in the range [0-1]
        qreal saturation() const;

        /// Get current value in the range [0-1]
        qreal value() const;

        /// Get the width in pixels of the outer wheel
        unsigned int wheelWidth() const;

        /// Set the width in pixels of the outer wheel
        void setWheelWidth(unsigned int w);

public slots:

        /// Set current color
        void setColor(QColor c);

        /**
     * @param h Hue [0-1]
     */
        void setHue(qreal h);

        /**
     * @param s Saturation [0-1]
     */
        void setSaturation(qreal s);

        /**
     * @param v Value [0-1]
     */
        void setValue(qreal v);

        /**
     * @brief Set the display flags
     * @param flags which will replace the current ones
     */
        // void setDisplayFlags(ColorWheel::DisplayFlags flags);

signals:
        /**
     * Emitted when the user selects a color or setColor is called
     */
        void colorChanged(QColor);

        /**
     * Emitted when the user selects a color
     */
        void colorSelected(QColor);

protected:
        void paintEvent(QPaintEvent *) override;
        void mouseMoveEvent(QMouseEvent *) override;
        void mousePressEvent(QMouseEvent *) override;
        void mouseReleaseEvent(QMouseEvent *) override;
        void resizeEvent(QResizeEvent *) override;
private:
        class Private;
        Private * const p;
};


#endif // COLORWHEEL_H
