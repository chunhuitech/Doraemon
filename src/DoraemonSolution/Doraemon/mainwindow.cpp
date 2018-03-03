#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Model/classificationtreemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ClassificationTreeModel *model = new ClassificationTreeModel();
    ui->uiClassTreeView->setModel(model);
    ui->uiClassTreeView->setHeaderHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
