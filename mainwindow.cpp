#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graph_structures.h"
#include <QMessageBox>
#include "pathfinder.h"
#include <QFileDialog>
#include <QFileInfo>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Система поиска");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toCity_currentIndexChanged(int index)
{
    m_endAirportId = ui->toCity->currentData().toInt();
}

void MainWindow::on_fromCity_currentIndexChanged(int index)
{
    m_startAirportId = ui->fromCity->currentData().toInt();
}

void MainWindow::fillData() {
    ui->fromCity->blockSignals(true);
    ui->toCity->blockSignals(true);

    ui->fromCity->clear();
    ui->toCity->clear();

    auto airportIds = graph.GetAllAirportsIds();

    for (int id : airportIds) {
        Airport a = graph.GetAirport(id);
        ui->fromCity->addItem(a.City, id);
        ui->toCity->addItem(a.City, id);
    }

    ui->fromCity->blockSignals(false);
    ui->toCity->blockSignals(false);

    if (ui->fromCity->count() > 0) {
        m_startAirportId = ui->fromCity->currentData().toInt();
        m_endAirportId = ui->toCity->currentData().toInt();
    } else {
        m_startAirportId = -1;
        m_endAirportId = -1;
    }
}

void MainWindow::on_FindPathes_clicked()
{
    if (m_startAirportId == -1 || m_endAirportId == -1) {
        QMessageBox::warning(this, "Внимание", "Выберите аэропорты.");
        return;
    }

    if (m_startAirportId == m_endAirportId) {
        QMessageBox::warning(this, "Внимание", "Выберите разные аэропорты.");
        return;
    }

    Criteria searchCriteria = Criteria::Price;
    if (ui->Time->isChecked()) searchCriteria = Criteria::Time;
    else if (ui->Combo->isChecked()) searchCriteria = Criteria::Combo;

    std::vector<std::vector<Flight>> paths;
    if(ui->OnlyDirect->isChecked())
        paths = PathFinder(graph).GetDirectFlights(m_startAirportId, m_endAirportId, searchCriteria, neededPathes);
    else
        paths = PathFinder(graph).FindKShortestPaths(m_startAirportId, m_endAirportId, searchCriteria, neededPathes);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"№", "Маршрут", "Детали"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    for (int i = 0; i < paths.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));

        double totalPrice = 0;
        QStringList routeCities;

        if (!paths[i].empty()) {
            routeCities << graph.GetAirport(paths[i].front().SourceId).City;

            qint64 totalSecs = paths[i].front().Departure.secsTo(paths[i].back().Arrival);
            int hours = totalSecs / 3600;
            int minutes = (totalSecs % 3600) / 60;

            for (const auto& flight : paths[i]) {
                totalPrice += flight.Price;
                routeCities << graph.GetAirport(flight.DestId).City + " №" + flight.FlightNumber + " ";
            }

            QString info = QString("Цена: %1$ | Время: %2ч %3м")
                               .arg(totalPrice)
                               .arg(hours)
                               .arg(minutes);

            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(routeCities.join(" -> ")));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(info));
        }
    }
}

void MainWindow::on_ChooseFile_clicked()
{
    neededPathes = 10;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выберите файл JSON",
                                                    "",
                                                    "JSON Files (*.json)");

    if (!fileName.isEmpty()) {
        graph.LoadFromJson(fileName);
        fillData();

        if (ui->fromCity->count() > 0) {
            m_startAirportId = ui->fromCity->currentData().toInt();
            m_endAirportId = ui->toCity->currentData().toInt();
        }

        ui->tableWidget->setRowCount(0);
        setWindowTitle("Система поиска — " + QFileInfo(fileName).fileName());
    }
}

void MainWindow::on_AddInfo_clicked()
{
    neededPathes += 10;
    on_FindPathes_clicked();
}



void MainWindow::on_Edit_clicked()
{
    Dialog editDialog(&graph, this);

    editDialog.exec();
    fillData();
    ui->tableWidget->setRowCount(0);
}
