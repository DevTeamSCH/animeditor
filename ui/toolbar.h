#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class Toolbar;
}
/*!
 * \brief The ToolState enum
 *
 * Enumeration for the tools.
 */
enum ToolState{
        Arrow,
        Brush,
        Line,
        Rectangle,
        Ellipse,
        Pipette,
        Fill,
        Text
};

class Toolbar : public QWidget
{
        Q_OBJECT

public:
        /*!
         * \brief Toolbar
         * \param parent
         *
         * Default constructor
         */
        explicit Toolbar(QWidget *parent = 0);
        ~Toolbar();

        QSize sizeHint() const override;

private slots:

        void on_brushButton_clicked();

        void on_arrowButton_clicked();

        void on_lineButton_clicked();

        void on_rectButton_clicked();

        void on_ellipseButton_clicked();

        void on_pipetteButton_clicked();

        void on_fillButton_clicked();

        void on_textButton_clicked();

        void on_brushButton_toggled(bool checked);

signals:
        /**
         * Emitted when the user select a tool
         */
        void toolChanged(ToolState);
private:
        Ui::Toolbar *ui;
};

#endif // TOOLBAR_H
