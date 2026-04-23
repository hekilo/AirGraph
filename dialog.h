#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "flightgraph.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(FlightGraph* graph, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_Save_clicked();
    void on_SaveToFile_clicked();
    void on_Add_clicked();
    void on_DeleteSelected_clicked();

    void on_isAirport_toggled(bool checked);
    void on_radioButton_toggled(bool checked);

    void on_from_currentIndexChanged(int index);
    void on_to_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    FlightGraph* m_graph;

    void updateTable();
    void updateComboBoxes();
};

#endif // DIALOG_H
