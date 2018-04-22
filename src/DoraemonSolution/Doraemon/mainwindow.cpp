#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdatabaseso.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QFileInfo>
#include <QProcess>

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#define FlashAXUUID "{d27cdb6e-ae6d-11cf-96b8-444553540000}"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    m_bFullScreen = false;
    m_bQueryClass = false;
    configFileHandle();
    widgetHideShow();    
    modelViewHandel();
    trayHandle();
    skinHandle();
    pushActiveInfo();

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

void MainWindow::OnSignSaveClassInfoFinished2UI(int code, int count)
{
    Q_UNUSED(code);
    if(count > 0) {
        ui->uiClassTreeView->reset();
    }
    QString info = QString("Classification synchronization completion %1").arg(QString::number(count));
    ui->statusBar->showMessage(info, 10000);
}

void MainWindow::OnSignSaveRecordInfoFinished2UI(int code, int count)
{
    Q_UNUSED(code);
    if(count > 0) {
        ui->uiRecordTreeView->reset();
    }
    QString info = QString("Record synchronization completion %1").arg(QString::number(count));
    ui->statusBar->showMessage(info, 10000);
}

void MainWindow::OnSignImportDBDataFinished2UI(int code, int count)
{
    Q_UNUSED(code);
    if(count > 0){
         ui->uiRecordTreeView->reset();
    }
    QString info = QString("Record initial completion %1").arg(QString::number(count));
    ui->statusBar->showMessage(info, 10000);
}


void MainWindow::OnSignDownDorFileFinished2UI(int code, int count)
{
    Q_UNUSED(code);
    Q_UNUSED(count);
    importDBData();
}

void MainWindow::OnSignGetDorDataVersionFinished2UI(int code, QString msg, const QVariant &mark)
{
    Q_UNUSED(code);
    Q_UNUSED(msg);
    QControlSo::instance().syncClassification();
    if(mark.canConvert<DorDataFileStruct>())
    {
        DorDataFileStruct ddfs = mark.value<DorDataFileStruct>();
        QSettings settings(m_commonData.iniFileName, QSettings::IniFormat);
        m_commonData.dbVersion = settings.value(DB_VERSION, "0").toInt();
        if(m_commonData.dbVersion < ddfs.versionNum){
            QString recordFileFullPath = QApplication::applicationDirPath() + "/data/comm_record.dor";
            QFileInfo fi(recordFileFullPath);
            if(fi.exists()){
                importDBData();
            } else {
                QControlSo::instance().downDorDataFile(ddfs.downAddress);
            }

        } else {
            QControlSo::instance().syncRecord();
            ui->statusBar->showMessage(tr("Network synchronization..."), 10000);
        }
    }
}


void MainWindow::OnSignCheckVersionFinished2UI(int code, QString msg, const QVariant &mark)
{
    Q_UNUSED(code);
    QString info;
    if(mark.canConvert<VersionInfoStruct>())
    {
        VersionInfoStruct vis = mark.value<VersionInfoStruct>();
        if( vis.verNum > QString(VERSION_NUM).toInt()){
            info = QString("new Version: %1 to Download?").arg(vis.version);
            QMessageBox message(QMessageBox::NoIcon, tr("Doraemon"), info, QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl(vis.downAddress));
            }
        } else {
            info = QString("It's the latest version: %1").arg(VERSION);
            QMessageBox::information(this, tr("Doraemon"), info);
        }
        return;
    }
    info = QString("检测失败: %1").arg(msg);
    QMessageBox::information(this, tr("Doraemon"), info);
}


void MainWindow::on_uiRecordTreeView_doubleClicked(const QModelIndex &index)
{
    int recordId = reinterpret_cast<int>(index.internalPointer());
    RecordStruct rs = QDatabaseSo::instance().getRecordRecord(recordId);
    QString filePath = QDatabaseSo::instance().getResourceServer() + rs.relativePath;
    QString localFilePath = QApplication::applicationDirPath() + rs.relativePath;
    QFileInfo fi(localFilePath);
    bool findFile= false;
    if(fi.exists()){
       filePath = localFilePath;
       findFile= true;
    }
    if(m_commonData.flashPlayWayFLag == FPWF_AXWIDGET) {
        ui->uiStackedWidgetPlay->setCurrentIndex(0);
        if(!m_commonData.hasFlashActiveX){
            QString info = QString("detects that there is no flash plug-in installed. Do you want to install it?");
            QMessageBox message(QMessageBox::NoIcon, tr("Doraemon"), info, QMessageBox::Yes | QMessageBox::No, NULL);
            if(message.exec() == QMessageBox::Yes)
            {

                 QString flashSetupPath = QApplication::applicationDirPath() + "/plugins/install_flash_player_ax.exe";
//                 qDebug() << flashSetupPath;
                m_process.start(flashSetupPath, QStringList(flashSetupPath));//"C:/pluginsTest/install_flash_player_ax.exe"
//                m_process.startDetached(flashSetupPath, QStringList(flashSetupPath));
//                m_process.startDetached("cmd.exe");
                return;
            }
        }
        ui->flashAxWidget->dynamicCall("LoadMovie(long,string)",0,filePath);
    } else {
        ui->uiStackedWidgetPlay->setCurrentIndex(1);
        if(findFile){
            ui->uiWebViewPlay->load(QUrl::fromLocalFile(filePath));
        } else {
            ui->uiWebViewPlay->load(QUrl(filePath));
        }


    }
//    qDebug() << filePath;
//    QString swfFile = qApp->applicationDirPath()+"/Resource/26个英文字母发音、笔画/a.swf"; // "http://www.firemail.wang/production_resource/temp/a.swf";


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
    QControlSo::instance().getDorDataVersion();
}

void MainWindow::on_uiPushButtonRecordQuery_clicked()
{
    m_rq.queryKey = ui->uiLineEditRecordKey->text();
    if(m_rq.queryKey.isEmpty()){
        QMessageBox::information(this, tr("Notice"), tr("Query key can not be empty"));
        return;
    }
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
//       qDebug() << screenWidth << " " << screenHeight;
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
    QString resultInfo;
    if(m_pRecordTreeModel->rowCount() < m_pRecordTreeModel->realCount()){
        resultInfo = QString("total:%1 shows the first %2 ").arg(QString::number(m_pRecordTreeModel->realCount())).arg(QString::number(m_pRecordTreeModel->rowCount()));
    } else {
        resultInfo = QString("total:%1 ").arg(QString::number(m_pRecordTreeModel->rowCount()));
    }
    ui->uiLabelQueryResult->setText(resultInfo);
}

void MainWindow::on_uiPushButtonQueryClass_clicked()
{
    if(!m_bQueryClass) {
         m_cq.queryKey = ui->uiLineEditClassKey->text();
         if(m_cq.queryKey.isEmpty()){
             QMessageBox::information(this, tr("Notice"), tr("Query key can not be empty"));
             return;
         }
         ui->uiPushButtonQueryClass->setIcon(QIcon(":/doraemon/res/reset.png"));
         ui->uiPushButtonQueryClass->setToolTip(tr("Reset"));
        ui->uiLeftStackedWidget->setCurrentIndex(1);

        m_pClassListModel->setQuery(m_cq);
        ui->uiClassListView->reset();

    } else {
        ui->uiPushButtonQueryClass->setIcon(QIcon(":/doraemon/res/search.png"));
        ui->uiPushButtonQueryClass->setToolTip(tr("Query classification"));
        ui->uiLineEditClassKey->setText(tr(""));
        m_cq.queryKey = "";
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
    m_systemTray->showMessage("Doraemon",
           "Welcome to use!",
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
    ui->uiRightTBSplitter->setStretchFactor(0,5);
    ui->uiRightTBSplitter->setStretchFactor(1,5);
//    ui->uiLeftStackedWidget->setMargin(1);
//    ui->uiLeftStackedWidget->setSpacing(1);
//    ui->uiLeftStackedWidget->setContentsMargins(0,0,0,0);
//    QString swfFile = "http://www.firemail.wang:8088/chunhui_resource/preschool/letters/a.swf";
    if(m_commonData.flashPlayWayFLag == FPWF_AXWIDGET) {
//        ui->uiStackedWidgetPlay->setCurrentIndex(FPWF_AXWIDGET);
        if(ui->flashAxWidget->setControl(QString::fromUtf8(FlashAXUUID))){
            m_commonData.hasFlashActiveX = true;
        } else {
            m_commonData.hasFlashActiveX = false;
        }
//        ui->flashAxWidget->dynamicCall("LoadMovie(long,string)",0,swfFile);
    }
    ui->uiStackedWidgetPlay->setCurrentIndex(1);
    QWebSettings *websetting = QWebSettings::globalSettings();
    websetting->setAttribute(QWebSettings::PluginsEnabled, true);
//        websetting->setAttribute(QWebSettings::JavaEnabled, true);
    websetting->setAttribute(QWebSettings::JavascriptEnabled, true);
    websetting->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);//
    websetting->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->uiWebViewPlay->load(QUrl("http://www.chunhuitech.cn:8088/doraemon/"));
    ui->uiWebViewPlay->show();

    ui->uiWebViewPlay->setContextMenuPolicy(Qt::NoContextMenu);
    ui->action_ImportRes->setVisible(false);

}

void MainWindow::modelViewHandel()
{
    m_pClassTreeModel = new ClassificationTreeModel();
    ui->uiClassTreeView->setModel(m_pClassTreeModel);
    ui->uiClassTreeView->setHeaderHidden(true);
    ui->uiLeftStackedWidget->setCurrentIndex(0);
    m_pClassListModel = new ClassificationListModel();
    ui->uiClassListView->setModel(m_pClassListModel);

    QObject::connect(&QControlSo::instance(), SIGNAL(signSaveClassInfoFinished2UI(int, int)),
            this, SLOT(OnSignSaveClassInfoFinished2UI(int, int)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signSaveRecordInfoFinished2UI(int, int)),
            this, SLOT(OnSignSaveRecordInfoFinished2UI(int, int)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signImportDBDataFinished2UI(int, int)),
            this, SLOT(OnSignImportDBDataFinished2UI(int, int)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signCheckVersionFinished2UI(int, QString, const QVariant&)),
            this, SLOT(OnSignCheckVersionFinished2UI(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signDownDorFileFinished2UI(int, int)),
            this, SLOT(OnSignDownDorFileFinished2UI(int, int)), Qt::QueuedConnection);
    QObject::connect(&QControlSo::instance(), SIGNAL(signGetDorDataVersionFinished2UI(int, QString, const QVariant&)),
            this, SLOT(OnSignGetDorDataVersionFinished2UI(int, QString, const QVariant&)), Qt::QueuedConnection);

    QObject::connect(&m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));


    m_pRecordTreeModel = new RecordTreeModel();
    m_pRecordTreeModel->setMaxCount(m_commonData.maxRecordShow);
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
    m_systemTray->setToolTip(tr("Doramon"));
    m_systemTray->show();
    connect(m_systemTray, &QSystemTrayIcon::activated, this, &MainWindow::on_activeTray);//点击托盘，执行相应的动作
    m_menu = new QMenu(this);
    m_actionMain = new QAction(m_menu);
    m_actionMain->setText("open window");
    m_menu->addAction(m_actionMain);
    connect(m_actionMain, &QAction::triggered, this, &MainWindow::showWindow);
    m_actionExit = new QAction(m_menu);
    m_actionExit->setText("exit");
    m_menu->addAction(m_actionExit);
    connect(m_actionExit, &QAction::triggered, this, &MainWindow::exitWindow);
    m_systemTray->setContextMenu(m_menu);
    connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &MainWindow::showWindow);//点击消息框，显示主窗
}

void MainWindow::configFileHandle()
{
    m_commonData.iniFileName = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(m_commonData.iniFileName, QSettings::IniFormat);
    m_commonData.dbVersion = settings.value(DB_VERSION, "0").toInt();
    if(!settings.contains(DB_VERSION)){
        settings.setValue(DB_VERSION, "0");
    }
    m_commonData.maxRecordShow = settings.value(UI_MAX_RECORD_SHOW, "100").toInt();
    if(!settings.contains(UI_MAX_RECORD_SHOW)){
        settings.setValue(UI_MAX_RECORD_SHOW, "100");
    }
    m_commonData.flashPlayWayFLag = settings.value(FlashPlayWayFLAG, "1").toInt();
    if(!settings.contains(FlashPlayWayFLAG)){
        settings.setValue(FlashPlayWayFLAG, "1");
    }

    m_commonData.OsPlatFlag = settings.value(OSPlatFlag, "0").toInt();
    if(!settings.contains(OSPlatFlag)){
        settings.setValue(OSPlatFlag, "0");
    }
}

void MainWindow::importDBData()
{
    ui->statusBar->showMessage(tr("Data synchronization..."), 10000);
    QControlSo::instance().importRecords();
//    QDatabaseSo::instance().importRecords();
//    QVector<QString> vecRecords;
//    vecRecords.append("INSERT INTO record(classId,sortNum,title,label,relativePath,fileSize,fileType,contentHtml,contentPlain,status,modifyTime,createTime)VALUES (5, 0, 'x','X','/chunhui_resource/preschool/letters/x.swf',24238,'SWF','','',0,1523287650,1523287650);");
//    vecRecords.append("INSERT INTO record(classId,sortNum,title,label,relativePath,fileSize,fileType,contentHtml,contentPlain,status,modifyTime,createTime)VALUES (5, 0, 'y','Y','/chunhui_resource/preschool/letters/y.swf',28117,'SWF','','',0,1523287650,1523287650);");
//    vecRecords.append("INSERT INTO record(classId,sortNum,title,label,relativePath,fileSize,fileType,contentHtml,contentPlain,status,modifyTime,createTime)VALUES (5, 0, 'z','Z','/chunhui_resource/preschool/letters/z.swf',24128,'SWF','','',0,1523287650,1523287650);");
    //    QDatabaseSo::instance().importRecords(vecRecords);
}

void MainWindow::pushActiveInfo()
{
    ProductActivityStruct pas;
    pas.userId = 0;
    pas.clientFlag = QNetSo::instance().gethostMac();
    pas.procName = APP_NAME;
    pas.procVersion = VERSION;
    pas.procId = QString(APP_ID).toInt();
    pas.os = QNetSo::instance().getOSInfo();
    pas.eventName = EVENT_START_UP;
    pas.ip = QNetSo::instance().gethostIp();
    IpInfoStruct iis = QNetSo::instance().GetNetIPInfo();
    pas.netIp = iis.netIp;
    pas.area = iis.areaInfo;
    QDateTime current_date_time = QDateTime::currentDateTime();
    pas.modifyTime = QString::number(current_date_time.toMSecsSinceEpoch());
    pas.createTime = QString::number(current_date_time.toMSecsSinceEpoch());
    pas.remarks = "";
    QControlSo::instance().pushActiveInfo(pas);
}

void MainWindow::skinHandle()
{
    ui->uiPushButtonFullScreen->setIcon(QIcon(":/doraemon/res/fullscreen.png"));
    ui->uiPushButtonFullScreen->setToolTip(tr("Switch to full screen"));
    ui->uiPushButtonQueryClass->setIcon(QIcon(":/doraemon/res/search.png"));
    ui->uiPushButtonQueryClass->setToolTip(tr("Query classification"));
    ui->uiPushButtonRecordQuery->setIcon(QIcon(":/doraemon/res/search.png"));
    ui->uiPushButtonRecordQuery->setToolTip(tr("Query"));
}

void MainWindow::on_verCheckAction_triggered()
{
    VersionInfoStruct vis;
    vis.appName = APP_NAME;
    if(m_commonData.OsPlatFlag == OPF_WIN_32){
        vis.platform = APP_PLAT_FORM_WIN_32;
    } else {
        vis.platform = APP_PLAT_FORM_WIN_64;
    }

    QControlSo::instance().checkVersion(vis);
}

void MainWindow::on_uiLineEditRecordKey_returnPressed()
{
    on_uiPushButtonRecordQuery_clicked();
}

void MainWindow::on_uiLineEditClassKey_returnPressed()
{
    on_uiPushButtonQueryClass_clicked();
}

void MainWindow::processError(QProcess::ProcessError error)
{
    QString info = ". Please install it manually  install_flash_player_ax.exe";
    switch(error)
       {
       case QProcess::FailedToStart:
           QMessageBox::information(0, "Tip", "FailedToStart" + info);
           break;
       case QProcess::Crashed:
           QMessageBox::information(0, "Tip", "Crashed" + info);
           break;
       case QProcess::Timedout:
           QMessageBox::information(0, "Tip", "Timedout" + info);
           break;
       case QProcess::WriteError:
           QMessageBox::information(0, "Tip", "WriteError" + info);
           break;
       case QProcess::ReadError:
           QMessageBox::information(0, "Tip", "ReadError" + info);
           break;
       case QProcess::UnknownError:
           QMessageBox::information(0, "Tip", "UnknownError" + info);
           break;
       default:
           QMessageBox::information(0, "Tip", "UnknownError" + info);
           break;
       }
    QString flashSetupPath = QApplication::applicationDirPath() + "/plugins/";
    QDesktopServices::openUrl(QUrl("file:" + flashSetupPath, QUrl::TolerantMode));
}

void MainWindow::on_action_ImportRes_triggered()
{
    QString program = QApplication::applicationDirPath() + "/7z.exe";
    qDebug() << program;
    QStringList arguments;
    arguments << "x" << "C:\github\Doraemon\src\DoraemonSolution\tools\7z\1.zip" << "-aoa" << "-o" + QApplication::applicationDirPath();
    qDebug() << arguments;
     m_process.start(program, arguments, QIODevice::ReadWrite);
}

void MainWindow::on_action_Home_triggered()
{
    ui->uiStackedWidgetPlay->setCurrentIndex(1);
    ui->uiWebViewPlay->load(QUrl("http://www.chunhuitech.cn:8088/doraemon/"));
    ui->uiWebViewPlay->show();
}

void MainWindow::on_action_OnlineHelp_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.firemail.wang:8088/forum.php?mod=viewthread&tid=9423"));
}
