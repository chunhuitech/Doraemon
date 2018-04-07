#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdatabaseso.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSystemTrayIcon>
#ifdef Q_OS_WIN32
#include <windows.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    m_bFullScreen = false;
    m_bQueryClass = false;
    widgetHideShow();
    modelViewHandel();
    trayHandle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    QControlSo::instance().exitHandler();
//    event->accept();
    this->hide();
    event->ignore();
}



void MainWindow::on_MainWindow_destroyed()
{

}

void MainWindow::OnSignSaveClassInfoFinished2UI(int code)
{
    qDebug() << "ui:" << code;
    ui->uiClassTreeView->reset();
    ui->statusBar->showMessage(tr("分类同步完成"), 2000);
}

void MainWindow::OnSignSaveRecordInfoFinished2UI(int code)
{
    Q_UNUSED(code);
    ui->uiRecordTreeView->reset();
    ui->statusBar->showMessage(tr("记录同步完成"), 2000);
}


void MainWindow::on_uiRecordTreeView_doubleClicked(const QModelIndex &index)
{
    int recordId = reinterpret_cast<int>(index.internalPointer());
    RecordStruct rs = QDatabaseSo::instance().getRecordRecord(recordId);
    QString filePath = QDatabaseSo::instance().getResourceServer() + rs.relativePath;
    qDebug() << filePath;
    QString swfFile = qApp->applicationDirPath()+"/Resource/26个英文字母发音、笔画/a.swf"; // "http://www.firemail.wang/production_resource/temp/a.swf";
    ui->flashAxWidget->dynamicCall("LoadMovie(long,string)",0,filePath);

}

void MainWindow::on_uiClassTreeView_clicked(const QModelIndex &index)
{
    int classId = reinterpret_cast<int>(index.internalPointer());
    m_rq.classId = classId;
    m_rq.queryKey = "";
    ui->uiLineEditRecordKey->setText(m_rq.queryKey);
    m_pRecordTreeModel->setQuery(m_rq);
    ui->uiRecordTreeView->reset();
    setQueryResultInfo();
}

void MainWindow::on_syncAction_triggered()
{
    QControlSo::instance().syncClassification();
    QControlSo::instance().syncRecord();
//    cc.syncClassification();
//     classAPI.syncData(0);
    ui->statusBar->showMessage(tr("同步中..."), 2000);
}

void MainWindow::on_uiPushButtonRecordQuery_clicked()
{
    m_rq.queryKey = ui->uiLineEditRecordKey->text();
    m_pRecordTreeModel->setQuery(m_rq);
    ui->uiRecordTreeView->reset();
    setQueryResultInfo();
}

void MainWindow::on_uiPushButtonFullScreen_clicked()
{
    QDesktopWidget *deskWgt = QApplication::desktop();
    int screenWidth = 1366;
    int screenHeight = 768;
    int left = screenWidth * 0.3;
    int right = screenWidth - left;
    int top = screenHeight * 0.7;
    int bottom = screenHeight - top;
   if (deskWgt) {
       QRect screenRect = deskWgt->screenGeometry();
       screenWidth = screenRect.width();
       left = screenWidth * 0.3;
       right = screenWidth - left;
       screenHeight = screenRect.height();
       top = screenHeight * 0.7;
       bottom = screenHeight - top;
       qDebug() << screenWidth << " " << screenHeight;
   }
   QList <int> sizeListWidth;
//   sizeListWidth.clear();
   QList <int> sizeListHeight;
    if(!m_bFullScreen){
//        setWindowFlags(Qt::Window);
        ui->statusBar->hide();
        ui->menuBar->hide();
       sizeListWidth.append(0);
       sizeListWidth.append(screenWidth);
       ui->uiLeftRightSplitter->setSizes(sizeListWidth);

       sizeListHeight.append(screenHeight);
       sizeListHeight.append(0);
       ui->uiRightTBSplitter->setSizes(sizeListHeight);

       ui->uiWidgetFullScreen->hide();
       showFullScreen();
    } else {
//        setWindowFlags(Qt::SubWindow);
        ui->statusBar->show();
        ui->menuBar->show();

        sizeListWidth.append(left);
        sizeListWidth.append(right);
        ui->uiLeftRightSplitter->setSizes(sizeListWidth);

        sizeListHeight.append(top);
        sizeListHeight.append(bottom);
        ui->uiRightTBSplitter->setSizes(sizeListHeight);
        ui->uiWidgetFullScreen->show();
        showNormal();
    }

    m_bFullScreen = !m_bFullScreen;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 响应Esc键以退出程序
    if (event->key() == Qt::Key_Escape)
    {
       on_uiPushButtonFullScreen_clicked();
    }
}

void MainWindow::changeEvent(QEvent * event)
{
    if ((event->type() == QEvent::WindowStateChange) && isMinimized())
    {
        //最小化还是原来的方式，不进行隐藏处理了。
//       this->hide();
//       event->ignore();
    }
}

void MainWindow::setQueryResultInfo()
{
    ui->uiLabelQueryResult->setText(QString::number(m_pRecordTreeModel->rowCount()));
}

void MainWindow::on_uiPushButtonQueryClass_clicked()
{
    if(!m_bQueryClass) {
         m_cq.queryKey = ui->uiLineEditClassKey->text();
         if(m_cq.queryKey.isEmpty()){
             QMessageBox::information(this, tr("警告"), tr("查询关键字不能为空"));
             return;
         }
        ui->uiPushButtonQueryClass->setText(tr("重置"));
        ui->uiLeftStackedWidget->setCurrentIndex(1);

        m_pClassListModel->setQuery(m_cq);
        ui->uiClassListView->reset();

    } else {
        ui->uiPushButtonQueryClass->setText(tr("查询分类"));
        ui->uiLineEditClassKey->setText(tr(""));
        ui->uiLeftStackedWidget->setCurrentIndex(0);
    }
    m_bQueryClass = !m_bQueryClass;
}

void MainWindow::on_uiClassListView_clicked(const QModelIndex &index)
{
    int classId = reinterpret_cast<int>(index.internalPointer());
    m_rq.classId = classId;
    m_rq.queryKey = "";
    ui->uiLineEditRecordKey->setText(m_rq.queryKey);
    m_pRecordTreeModel->setQuery(m_rq);
    ui->uiRecordTreeView->reset();
    setQueryResultInfo();
}

void MainWindow::on_activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
   {
   case QSystemTrayIcon::Context:
       showMenu();
       break;
   case QSystemTrayIcon::DoubleClick:
       showWindow();
       break;
   case QSystemTrayIcon::Trigger:
       showMessage();
       break;
    default:
        showWindow();
        break;
    }
}

void MainWindow::showMessage()
{
    m_systemTray->showMessage("多啦A梦",
           "欢迎使用!",
            QSystemTrayIcon::Information,//消息窗口图标
                              5000);//消息窗口显示时长
}

void MainWindow::showWindow()
{

    if (this->isMinimized())
    {
//        this->showNormal();
        this->showMaximized();
    }
#ifdef Q_OS_WIN32
//    SetWindowPos((HWND)winId(),HWND_TOPMOST,pos().x(),pos().y(),width(),height(),SWP_SHOWWINDOW);
    //设置窗口置顶
    SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

#else
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
#endif

    this->show();
    this->activateWindow();
}

void MainWindow::showMenu()
{
    m_menu->show();
}

void MainWindow::exitWindow()
{
    QControlSo::instance().exitHandler();
    QApplication::exit();
}

void MainWindow::widgetHideShow()
{
    ui->mainToolBar->hide();
    ui->uiLeftRightSplitter->setStretchFactor(0,3);
    ui->uiLeftRightSplitter->setStretchFactor(1,7);
    ui->uiLeftTBSplitter->setStretchFactor(0,1);
    ui->uiLeftTBSplitter->setStretchFactor(1,9);
    ui->uiRightTBSplitter->setStretchFactor(0,7);
    ui->uiRightTBSplitter->setStretchFactor(1,3);
//    ui->uiLeftStackedWidget->setMargin(1);
//    ui->uiLeftStackedWidget->setSpacing(1);
//    ui->uiLeftStackedWidget->setContentsMargins(0,0,0,0);
    ui->flashAxWidget->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
    QString swfFile = "http://www.firemail.wang:8088/chunhui_resource/preschool/letters/a.swf";
    ui->flashAxWidget->dynamicCall("LoadMovie(long,string)",0,swfFile);
}

void MainWindow::modelViewHandel()
{
    m_pClassTreeModel = new ClassificationTreeModel();
    ui->uiClassTreeView->setModel(m_pClassTreeModel);
    ui->uiClassTreeView->setHeaderHidden(true);
    ui->uiLeftStackedWidget->setCurrentIndex(0);
    m_pClassListModel = new ClassificationListModel();
    ui->uiClassListView->setModel(m_pClassListModel);

    QObject::connect(&QControlSo::instance(), SIGNAL(signSaveClassInfoFinished2UI(int)),
            this, SLOT(OnSignSaveClassInfoFinished2UI(int)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signSaveRecordInfoFinished2UI(int)),
            this, SLOT(OnSignSaveRecordInfoFinished2UI(int)), Qt::QueuedConnection);


    m_pRecordTreeModel = new RecordTreeModel();
    m_rq.classId = 5;
    m_pRecordTreeModel->setQuery(m_rq);
    ui->uiRecordTreeView->setModel(m_pRecordTreeModel);
    ui->uiRecordTreeView->setColumnWidth(0,400);
    //隐藏根节点项前的图标（展开折叠图标）
    ui->uiRecordTreeView->setRootIsDecorated(false);

    setQueryResultInfo();
}

void MainWindow::trayHandle()
{
    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/doraemon/res/Doraemon.png"));
    m_systemTray->setToolTip(tr("哆啦A梦"));
    m_systemTray->show();
    connect(m_systemTray, &QSystemTrayIcon::activated, this, &MainWindow::on_activeTray);//点击托盘，执行相应的动作
    m_menu = new QMenu(this);
    m_actionMain = new QAction(m_menu);
    m_actionMain->setText(tr("打开主窗口"));
    m_menu->addAction(m_actionMain);
    connect(m_actionMain, &QAction::triggered, this, &MainWindow::showWindow);
    m_actionExit = new QAction(m_menu);
    m_actionExit->setText(tr("退出"));
    m_menu->addAction(m_actionExit);
    connect(m_actionExit, &QAction::triggered, this, &MainWindow::exitWindow);
    m_systemTray->setContextMenu(m_menu);
    connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &MainWindow::showWindow);//点击消息框，显示主窗
}
