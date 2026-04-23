#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QFileDialog>
#include <stdexcept>

Dialog::Dialog(FlightGraph* graph, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_graph(graph)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");

    ui->info->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->info->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->info->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateComboBoxes();
    updateTable();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateComboBoxes()
{
    ui->from->blockSignals(true);
    ui->to->blockSignals(true);

    ui->from->clear();
    ui->to->clear();

    ui->from->addItem("Все", -1);
    ui->to->addItem("Все", -1);

    auto airportIds = m_graph->GetAllAirportsIds();
    for (int id : airportIds) {
        Airport a = m_graph->GetAirport(id);
        ui->from->addItem(a.City + " (" + a.Code + ")", id);
        ui->to->addItem(a.City + " (" + a.Code + ")", id);
    }

    ui->from->blockSignals(false);
    ui->to->blockSignals(false);
}

void Dialog::updateTable()
{
    ui->info->clear();
    ui->info->setRowCount(0);

    if (ui->isAirport->isChecked()) {

        ui->info->setColumnCount(3);
        ui->info->setHorizontalHeaderLabels({"ID", "Город", "Код"});

        ui->from->setEnabled(false);
        ui->to->setEnabled(false);

        auto airportIds = m_graph->GetAllAirportsIds();

        for (int i = 0; i < airportIds.size(); ++i) {
            Airport a = m_graph->GetAirport(airportIds[i]);
            ui->info->insertRow(i);
            ui->info->setItem(i, 0, new QTableWidgetItem(QString::number(a.Id)));
            ui->info->setItem(i, 1, new QTableWidgetItem(a.City));
            ui->info->setItem(i, 2, new QTableWidgetItem(a.Code));
        }
    }
    else {

        ui->info->setColumnCount(7);
        ui->info->setHorizontalHeaderLabels({"№ Рейса", "Откуда (ID)", "Куда (ID)", "Цена", "Вылет", "Прилет", "Откуда ID (Скрыто)"});
        ui->info->hideColumn(6);

        ui->from->setEnabled(true);
        ui->to->setEnabled(true);

        int filterFromId = ui->from->currentData().toInt();
        int filterToId = ui->to->currentData().toInt();

        auto airportIds = m_graph->GetAllAirportsIds();
        int row = 0;

        for (int id : airportIds) {
            if (filterFromId != -1 && id != filterFromId) continue;

            auto flights = m_graph->GetFlightsFrom(id);
            for (const auto& flight : flights) {
                if (filterToId != -1 && flight.DestId != filterToId) continue;

                Airport fromAir = m_graph->GetAirport(flight.SourceId);
                Airport toAir = m_graph->GetAirport(flight.DestId);

                ui->info->insertRow(row);
                ui->info->setItem(row, 0, new QTableWidgetItem(flight.FlightNumber));
                ui->info->setItem(row, 1, new QTableWidgetItem(fromAir.City));
                ui->info->setItem(row, 2, new QTableWidgetItem(toAir.City));
                ui->info->setItem(row, 3, new QTableWidgetItem(QString::number(flight.Price, 'f', 2)));
                ui->info->setItem(row, 4, new QTableWidgetItem(flight.Departure.toString("dd.MM.yyyy HH:mm")));
                ui->info->setItem(row, 5, new QTableWidgetItem(flight.Arrival.toString("dd.MM.yyyy HH:mm")));
                ui->info->setItem(row, 6, new QTableWidgetItem(QString::number(flight.SourceId)));
                row++;
            }
        }
    }
    ui->info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Dialog::on_Add_clicked()
{
    try {
        if (ui->isAirport->isChecked()) {

            QDialog addAirportDlg(this);
            addAirportDlg.setWindowTitle("Добавить аэропорт");
            QFormLayout form(&addAirportDlg);

            QDoubleSpinBox idSpn;
            idSpn.setDecimals(0);
            idSpn.setMaximum(1000000);
            QLineEdit cityEdit, codeEdit;

            form.addRow("ID:", &idSpn);
            form.addRow("Город:", &cityEdit);
            form.addRow("Код (3 буквы):", &codeEdit);

            QDialogButtonBox btnBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &addAirportDlg);
            form.addRow(&btnBox);

            connect(&btnBox, &QDialogButtonBox::accepted, &addAirportDlg, &QDialog::accept);
            connect(&btnBox, &QDialogButtonBox::rejected, &addAirportDlg, &QDialog::reject);

            if (addAirportDlg.exec() == QDialog::Accepted) {
                if (cityEdit.text().isEmpty() || codeEdit.text().isEmpty()) {
                    throw std::invalid_argument("Все поля должны быть заполнены!");
                }

                Airport newAirport = { static_cast<int>(idSpn.value()), codeEdit.text(), cityEdit.text(), };

                if (!m_graph->AddAirport(newAirport)) {
                    throw std::invalid_argument("Аэропорт с таким ID уже существует!");
                }

                updateComboBoxes();
                updateTable();
            }
        }
        else {

            auto airportIdsCheck = m_graph->GetAllAirportsIds();
            if (airportIdsCheck.empty()) {
                throw std::invalid_argument("Сначала добавьте хотя бы два аэропорта!");
            }

            QDialog addFlightDlg(this);
            addFlightDlg.setWindowTitle("Добавить полет");
            QFormLayout form(&addFlightDlg);

            QLineEdit flightNumEdit;
            QComboBox fromCb, toCb;

            auto airportIds = m_graph->GetAllAirportsIds();
            for (int id : airportIds) {
                Airport a = m_graph->GetAirport(id);
                fromCb.addItem(a.City, id);
                toCb.addItem(a.City, id);
            }

            QDoubleSpinBox priceSpn;
            priceSpn.setMaximum(1000000);

            QDateTimeEdit depEdit(QDateTime::currentDateTime());
            QDateTimeEdit arrEdit(QDateTime::currentDateTime().addSecs(3600));

            form.addRow("Номер рейса:", &flightNumEdit);
            form.addRow("Откуда:", &fromCb);
            form.addRow("Куда:", &toCb);
            form.addRow("Цена:", &priceSpn);
            form.addRow("Вылет:", &depEdit);
            form.addRow("Прилет:", &arrEdit);

            QDialogButtonBox btnBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &addFlightDlg);
            form.addRow(&btnBox);

            connect(&btnBox, &QDialogButtonBox::accepted, &addFlightDlg, &QDialog::accept);
            connect(&btnBox, &QDialogButtonBox::rejected, &addFlightDlg, &QDialog::reject);

            if (addFlightDlg.exec() == QDialog::Accepted) {

                if (flightNumEdit.text().isEmpty()) {
                    throw std::invalid_argument("Номер рейса не может быть пустым!");
                }

                int sourceId = fromCb.currentData().toInt();
                int destId = toCb.currentData().toInt();

                if (sourceId == destId) {
                    throw std::invalid_argument("Пункт отправления и назначения не могут совпадать!");
                }
                if (depEdit.dateTime() >= arrEdit.dateTime()) {
                    throw std::invalid_argument("Время прилета должно быть позже времени вылета!");
                }

                Flight newFlight = {
                    flightNumEdit.text(),
                    sourceId,
                    destId,
                    priceSpn.value(),
                    depEdit.dateTime(),
                    arrEdit.dateTime()
                };

                if (!m_graph->AddFlight(newFlight)) {
                    throw std::invalid_argument("Ошибка добавления! Возможно, такой рейс уже существует.");
                }
                updateTable();
            }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка валидации", e.what());
    }
}

void Dialog::on_DeleteSelected_clicked()
{
    int currentRow = ui->info->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Внимание", "Выберите элемент для удаления в таблице.");
        return;
    }

    try {
        if (ui->isAirport->isChecked()) {
            int airportId = ui->info->item(currentRow, 0)->text().toInt();

            if (!m_graph->DeleteAirport(airportId)) {
                throw std::invalid_argument("Не удалось удалить аэропорт!");
            }
            updateComboBoxes();

        } else {
            QString flightNum = ui->info->item(currentRow, 0)->text();
            int sourceId = ui->info->item(currentRow, 6)->text().toInt();

            if (!m_graph->DeleteFlight(flightNum, sourceId)) {
                throw std::invalid_argument("Не удалось удалить рейс!");
            }
        }
        updateTable();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка удаления", e.what());
    }
}

void Dialog::on_isAirport_toggled(bool checked)
{
    if (checked) updateTable();
}

void Dialog::on_radioButton_toggled(bool checked)
{
    if (checked) updateTable();
}

void Dialog::on_from_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if (ui->radioButton->isChecked()) updateTable();
}

void Dialog::on_to_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if (ui->radioButton->isChecked()) updateTable();
}

void Dialog::on_Save_clicked()
{
    accept();
}

void Dialog::on_SaveToFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл JSON", "", "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        if (m_graph->SaveToJson(fileName)) {
            QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл:\n" + fileName);
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить файл.");
        }
    }
}
