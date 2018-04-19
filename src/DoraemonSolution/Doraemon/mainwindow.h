#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "http/classificatonapi.h"
#include "qcontrolso.h"
#include "Model/classificationtreemodel.h"
#include "Model/classificationlistmodel.h"
#include "Model/recordtreemodel.h"
#include "qnetso.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QWebView>
#include <QWebSettings>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *);
protected:
    void setQueryResultInfo();
    void showMessage();
    void showWindow();
    void showMenu();
    void exitWindow();
    void widgetHideShow();
    void modelViewHandel();
    void trayHandle();
    void configFileHandle();

    void importDBData();

    void pushActiveInfo();

    void skinHandle();

private slots:

    void on_MainWindow_destroyed();

    void OnSignSaveClassInfoFinished2UI(int code, int count);
    void OnSignSaveRecordInfoFinished2UI(int code, int count);
    void OnSignImportDBDataFinished2UI(int code, int count);
    void OnSignCheckVersionFinished2UI(int code, QString msg, const QVariant& mark);
    void OnSignDownDorFileFinished2UI(int code, int count);
    void OnSignGetDorDataVersionFinished2UI(int code, QString msg, const QVariant& mark);

    void on_uiRecordTreeView_doubleClicked(const QModelIndex &index);

    void on_uiClassTreeView_clicked(const QModelIndex &index);

    void on_syncAction_triggered();

    void on_uiPushButtonRecordQuery_clicked();

    void on_uiPushButtonFullScreen_clicked();

    void on_uiPushButtonQueryClass_clicked();

    void on_uiClassListView_clicked(const QModelIndex &index);

    void on_activeTray(QSystemTrayIcon::ActivationReason reason);

    void on_verCheckAction_triggered();

    void on_uiLineEditRecordKey_returnPressed();

    void on_uiLineEditClassKey_returnPressed();

private:
    Ui::MainWindow *ui;
    RecordTreeModel * m_pRecordTreeModel;
    ClassificationTreeModel * m_pClassTreeModel;
    ClassificationListModel * m_pClassListModel;
    RecordQuery m_rq;
    RecordQuery m_cq;
    bool m_bFullScreen;
    bool m_bQueryClass;
    QSystemTrayIcon * m_systemTray;
    QMenu * m_menu;
    QAction * m_actionMain;
    QAction * m_actionExit;
    CommonData m_commonData;
};

#endif // MAINWINDOW_H
