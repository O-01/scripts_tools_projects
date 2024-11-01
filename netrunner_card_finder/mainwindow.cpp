#include "include/mainwindow.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <QLabel>
#include "include/simdjson.h"
#include "./ui_mainwindow.h"

using namespace simdjson;

static void to_lower(std::string *input)
{
    std::transform(
        (*input).begin(),
        (*input).end(),
        (*input).begin(),
        [](unsigned char c){ return std::tolower(c); }
    );
}

static void delim_to_underscore(std::string *input)
{
    std::replace((*input).begin(), (*input).end(), '-', '_');
    std::replace((*input).begin(), (*input).end(), ' ', '_');
}

static void clear_grid(QLayout *layout, bool delete_all = true)
{
    while (QLayoutItem *element = layout->takeAt(0))
    {
        if (delete_all)
        {
            if (QWidget *widget = element->widget())
                widget->deleteLater();
        }
        if (QLayout *child = element->layout())
            clear_grid(child, delete_all);
        delete element;
    }
}

static dom::element get_data(dom::parser& parser)
{
    dom::element data;
    auto error = parser.load("../cards.json").get(data);
    if (error)
    {
        std::cerr << "Failed to parse JSON: " << error << std::endl;
        std::exit(1);
    }
    return data["data"];
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // hide widgets until interaction properly detailed:
    ui->dropFormat->hide();
    ui->dropSet->hide();
    // hide search bar widget that reacts upon return pressed
    ui->lineEdit->hide();

    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        ui->cardList->addItem(tr(title.data()));
    }
}

MainWindow::~MainWindow()
{
    clear_grid(ui->gridLayout->layout(), 1);
    delete ui;
}

void MainWindow::on_cardList_itemClicked(QListWidgetItem *item)
{
    clear_grid(ui->gridLayout->layout(), 1);
    std::string item_name = item->text().toStdString();
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        if (std::strstr(title.data(), item_name.c_str()) == title.data() &&
            title.length() == item_name.length())
        {
            dom::array printing = element["attributes"]["printing_ids"];
            int row = 0, col = 0;
            for (size_t iter = 0; iter < printing.size(); ++iter)
            {
                std::stringstream image_path;
                image_path << "../images/" << printing.at(iter).get_string() << ".jpg";
                QPixmap image(image_path.str().c_str());
                QLabel *img_label = new QLabel();
                img_label->setPixmap(image.scaled(300, 420, Qt::KeepAspectRatio));
                ui->gridLayout->addWidget(img_label, row, col, Qt::AlignTop | Qt::AlignLeft);
                if (++col >= 2)
                    col = 0, ++row;
            }
        }
    }
}

void MainWindow::on_searchField_textChanged()
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    std::string search_text = ui->searchField->toPlainText().toStdString();
    to_lower(&search_text);
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        std::string title_lower = {title.begin(), title.end()};
        to_lower(&title_lower);
        if (std::strstr(title_lower.c_str(), search_text.c_str()))
            ui->cardList->addItem(tr(title.data()));
    }
}

void MainWindow::on_cardList_itemSelectionChanged()
{
    clear_grid(ui->gridLayout->layout(), 1);
    if (!ui->cardList->currentItem())
        return;
    std::string item_name = ui->cardList->currentItem()->text().toStdString();
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        if (std::strstr(title.data(), item_name.c_str()) == title.data() &&
            title.length() == item_name.length())
        {
            dom::array printing = element["attributes"]["printing_ids"];
            int row = 0, col = 0;
            for (size_t iter = 0; iter < printing.size(); ++iter)
            {
                std::stringstream image_path;
                image_path << "../images/" << printing.at(iter).get_string() << ".jpg";
                QPixmap image(image_path.str().c_str());
                QLabel *img_label = new QLabel();
                img_label->setPixmap(image.scaled(300, 420, Qt::KeepAspectRatio));
                ui->gridLayout->addWidget(img_label, row, col, Qt::AlignTop | Qt::AlignLeft);
                if (++col >= 2)
                    col = 0, ++row;
            }
        }
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    ui->searchField->clear();
    std::string search_text = ui->lineEdit->text().toStdString();
    to_lower(&search_text);
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        if (std::strstr(title.data(), search_text.c_str()))
            ui->cardList->addItem(tr(title.data()));
    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    ui->searchField->clear();

    // below conditions need to be fixed
    // these operations take longer than they ought to
    if (ui->dropSide->currentIndex())
        ui->dropSide->setCurrentIndex(0);
    if (ui->dropFaction->currentIndex())
        ui->dropFaction->setCurrentIndex(0);
    if (ui->dropType->currentIndex())
        ui->dropType->setCurrentIndex(0);

    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view title = element["attributes"]["title"];
        ui->cardList->addItem(tr(title.data()));
    }
}

void MainWindow::on_dropSide_currentTextChanged(const QString &arg1)
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    std::string side_select = arg1.toStdString().c_str();
    to_lower(&side_select);
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view side = element["attributes"]["side_id"];
        if (std::strstr(side.data(), side_select.c_str()) ||
            !ui->dropSide->currentIndex())
        {
            if (ui->dropFaction->currentIndex())
            {
                std::string faction_select = ui->dropFaction->currentText().toStdString();
                to_lower(&faction_select);
                delim_to_underscore(&faction_select);
                std::string_view faction = element["attributes"]["faction_id"];
                if (!std::strstr(faction.data(), faction_select.c_str()))
                    continue;
            }
            if (ui->dropType->currentIndex())
            {
                std::string type_select = ui->dropType->currentText().toStdString();
                to_lower(&type_select);
                std::string_view type = element["attributes"]["card_type_id"];
                if (!std::strstr(type.data(), type_select.c_str()))
                    continue;
            }
            std::string_view title = element["attributes"]["title"];
            ui->cardList->addItem(tr(title.data()));
        }
    }
}

void MainWindow::on_dropFaction_currentTextChanged(const QString &arg1)
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    std::string faction_select = arg1.toStdString().c_str();
    to_lower(&faction_select);
    delim_to_underscore(&faction_select);
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view faction = element["attributes"]["faction_id"];
        if (std::strstr(faction.data(), faction_select.c_str()) ||
            !ui->dropFaction->currentIndex())
        {
            if (ui->dropSide->currentIndex())
            {
                std::string side_select = ui->dropSide->currentText().toStdString();
                to_lower(&side_select);
                std::string_view side = element["attributes"]["side_id"];
                if (!std::strstr(side.data(), side_select.c_str()))
                    continue;
            }
            if (ui->dropType->currentIndex())
            {
                std::string type_select = ui->dropType->currentText().toStdString();
                to_lower(&type_select);
                std::string_view type = element["attributes"]["card_type_id"];
                if (!std::strstr(type.data(), type_select.c_str()))
                    continue;
            }
            std::string_view title = element["attributes"]["title"];
            ui->cardList->addItem(tr(title.data()));
        }
    }
}

void MainWindow::on_dropType_currentTextChanged(const QString &arg1)
{
    ui->cardList->setCurrentItem(nullptr);
    ui->cardList->clear();
    std::string type_select = arg1.toStdString().c_str();
    to_lower(&type_select);
    dom::parser parser;
    dom::element data = get_data(parser);
    for (dom::element element : data)
    {
        std::string_view card_type = element["attributes"]["card_type_id"];
        if (std::strstr(card_type.data(), type_select.c_str()) ||
            !ui->dropType->currentIndex())
        {
            if (ui->dropSide->currentIndex())
            {
                std::string side_select = ui->dropSide->currentText().toStdString();
                to_lower(&side_select);
                std::string_view side = element["attributes"]["side_id"];
                if (!std::strstr(side.data(), side_select.c_str()))
                    continue;
            }
            if (ui->dropFaction->currentIndex())
            {
                std::string faction_select = ui->dropFaction->currentText().toStdString();
                to_lower(&faction_select);
                delim_to_underscore(&faction_select);
                std::string_view faction = element["attributes"]["faction_id"];
                if (!std::strstr(faction.data(), faction_select.c_str()))
                    continue;
            }
            std::string_view title = element["attributes"]["title"];
            ui->cardList->addItem(tr(title.data()));
        }
    }
}
