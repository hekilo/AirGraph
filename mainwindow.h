#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flightgraph.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toCity_currentIndexChanged(int index);

    void on_fromCity_currentIndexChanged(int index);

    void on_FindPathes_clicked();

    void on_ChooseFile_clicked();

    void on_AddInfo_clicked();

    void on_Edit_clicked();

private:
    int neededPathes = 10;

    FlightGraph graph;

    void fillData();

    int m_startAirportId = -1;
    int m_endAirportId = -1;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
