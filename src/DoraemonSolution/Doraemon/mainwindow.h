#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "http/classificatonapi.h"
#include "qcontrolso.h"
#include "Model/classificationtreemodel.h"
#include "Model/classificationlistmodel.h"
#include "Model/recordtreemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
//    ClassificatonAPI classAPI;
//    QControlSo cc;

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void setQueryResultInfo();
private slots:

    void on_MainWindow_destroyed();

    void OnSignSaveClassInfoFinished2UI(int code);
    void OnSignSaveRecordInfoFinished2UI(int code);

    void on_uiRecordTreeView_doubleClicked(const QModelIndex &index);

    void on_uiClassTreeView_clicked(const QModelIndex &index);

    void on_syncAction_triggered();

    void on_uiPushButtonRecordQuery_clicked();

    void on_uiPushButtonFullScreen_clicked();

    void on_uiPushButtonQueryClass_clicked();

    void on_uiClassListView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    RecordTreeModel * m_pRecordTreeModel;
    ClassificationTreeModel * m_pClassTreeModel;
    ClassificationListModel * m_pClassListModel;
    RecordQuery m_rq;
    RecordQuery m_cq;
    bool m_bFullScreen;
    bool m_bQueryClass;
};

#endif // MAINWINDOW_H
