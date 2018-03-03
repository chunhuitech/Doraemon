后缀为.so（shared object）的文件为Linux上的动态库文件，Linux上的静态库文件为.a(akynesis)




model/view

memdata->view

相互之间的联动---
网络同步的数据->memdata变化->model变化->view变化
网络同步数据：
QControlCenterLib::getAccountFolders
m_mailNetWrapper->getAccountFolders(accountId);
QMailNetThreadWrapper::getAccountFolders(uint32_t accountId)
{
    emit signalGetAccountFolders(accountId);
}
 QObject::connect(this, SIGNAL(signalGetAccountFolders(uint32_t)),
        m_threadEntity, SLOT(getAccountFolders(uint32_t)), Qt::QueuedConnection);

QMailNetThreadEntity::getAccountFolders(uint32_t accountId)
{
pAccount->fetchAllFoldersOperation(); //线程里面连接网络下载数据
}
account::QAccount::fetchAllFoldersOperation(bool urgent /*= false*/)
{
	m_pIncommingServer->fetchAllFoldersOperation(urgent); //线程里面连接网络下载数据
}
m_pIncommingServer = new QImapServer();

QImapServer::fetchAllFoldersOperation(bool urgent)
{
	m_pImapFetchAllFoldersOperationCallback = new ImapFetchAllFoldersOperationCallback();
	connect(m_pImapFetchAllFoldersOperationCallback, SIGNAL(fetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&, unsigned int)),
		this, SLOT(onFetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&, unsigned int)));
}
基类统一对返回处理
QIncommingServer::onFetchAllFoldersOperationFinished(mailcore::ErrorCode code, const QVariant& folders, const QString& strErrorMessage, unsigned int taskIndex)
{
    emit fetchAllFoldersOperationFinished(code, folders, strErrorMessage);
}

QMailNetThreadEntity::connectWithAccountSignals(account::QAccount *pAccount)
{
    //获取所有邮件夹 信号连接
    connect(pAccount, SIGNAL(fetchAllFoldersOperationFinished(const QVariant&, mailcore::ErrorCode, const QVariant&, const QString&)),
        this, SLOT(onFetchAllFoldersOperationFinished(const QVariant&, mailcore::ErrorCode, const QVariant&, const QString&)));
}
QAccount::initConnect()
{
connect(m_pIncommingServer, SIGNAL(fetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&)),
        this, SLOT(onFetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&)));
}

QMailNetThreadEntity::onFetchAllFoldersOperationFinished(const QVariant& mark, mailcore::ErrorCode code, const QVariant& folders, const QString& strErrorMessage)
{
    fetchFoldersOperationFinished(mark, code, folders, strErrorMessage, __FUNCTION__);
}

QMailNetThreadEntity::fetchFoldersOperationFinished(const QVariant& mark, mailcore::ErrorCode code, const QVariant& folders, const QString& strErrorMessage, QString functionName)
{
//内存中添加数据
m_ctrlCenterRef->recursionAddFolder(folderListPath, FORWARD_SLASH_ONE, inServerId, stInServerInfo.protocolType);
if (bReflashFolders)
        emit signalAccountsMailFoldersChanged(stInServerInfo.accountId);  //通知界面刷新
}

QControlCenterLib::QControlCenterLib{
connect(m_mailNetWrapper, SIGNAL(signalAccountsMailFoldersChanged(uint32_t)),
        this, SLOT(onAccountsMailFoldersChanged(uint32_t)));
}

QControlCenterLib::onAccountsMailFoldersChanged(uint32_t accountId)
{
    emit refreshAccountsMailFolders(accountId, true);
}
MainWindow::signalSlotConnection(){
connect(m_pControlCenterLib, SIGNAL(refreshAccountsMailFolders(uint32_t, bool)), this, SLOT(onRefreshAccountFolders(uint32_t, bool))/*, Qt::QueuedConnection*/);
}

MainWindow::onRefreshAccountFolders(uint32_t accountId, bool bSel)
{
ui.mailFolderTreeView->refreshMailFolderTreeView();
}
QMailFolderTreeView::refreshMailFolderTreeView()
{
    resetModel();
}
QxTreeView::resetModel()
{
    saveState(currentState());
    disconnect(selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &QxTreeView::signalSelectionChanged);

    QAbstractItemModel *m = model();
    QTreeView::setModel(0);
    QTreeView::setModel(m);

    connect(selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &QxTreeView::signalSelectionChanged);

    recoveryState(currentState());
    emit signalSelectionChanged();
}
网络线程同步完成数据后,把数据传回主线程，然后加入到内存
QMailNetThreadEntity* m_threadEntity;  //同步数据线程 QThread m_netThread;在这个线程中执行
QMailNetThreadWrapper * m_mailNetWrapper; //通过它的信号槽 把数据转入主线程

加入到内存后：
通过信号槽更新界面 ui.mailFolderTreeView->refreshMailFolderTreeView();

view变化-> memdata变化->model变化


db->memdata

开始启动，由于数据量太大，所以要在线程中加载完成数据库中的数据后，再通知界面刷新
MainWindow::signalSlotConnection(){
connect(m_pControlCenterLib, SIGNAL(signalLoadMemoryDataFinished()), this, SLOT(onLoadMemoryDataFinished()), Qt::QueuedConnection);
}
MainWindow::onLoadMemoryDataFinished()
{
    onMailFolderSelectChanged(NULL);
}
MainWindow::onMailFolderSelectChanged(void * signalData)
{
   
    ui.mailListTreeViewEx->queryData(stQueryConditions);
}
QMailTreeView::queryData(QueryConditions stQueryConditions)
{
    QMailTreeModel::instance()->queryData(stQueryConditions);
}

////////
QControlCenterLib::QControlCenterLib{
 QObject::connect(&m_mDbCenterLib, SIGNAL(signalLoadMemoryDataFinished()),
        this, SLOT(onLoadMemoryDataFinished()), Qt::QueuedConnection);
}
QControlCenterLib::onLoadMemoryDataFinished()
{
    emit signalLoadMemoryDataFinished();
}

QMDbCenterLib::QMDbCenterLib{
QObject::connect(&m_dbThreadObj, SIGNAL(signalLoadMemoryDataFinished()),
        this, SLOT(onLoadMemoryDataFinished()), Qt::QueuedConnection);
}
 QDBThreadObj m_dbThreadObj;
 
QDBThreadObj::QDBThreadObj{
	m_dbEntry.moveToThread(&m_dbThread);
	QObject::connect(&m_dbEntry, SIGNAL(signalLoadMemoryDataFinished()), this, SLOT(onLoadMemoryDataFinished()), Qt::QueuedConnection);
}

QDBThreadEntrance::loadMemoryData(CMemoryDBManager* pMemoryDBManager){
   m_mailDBLib.loadAllMails(pMemoryDBManager->getMailMemoryData());
    emit signalLoadMemoryDataFinished();
}

//几种情况，
a.数据库结构与model源内存结构一致，直接从数据库中查询出来[通过sql语句获取相关值] （数据量大小无关，关键看sql语句查询速度 直接在主线程中操作等待完成显示）

b.数据库结构与model源内存结构memdata不一致(树视图), 从数据库一次加载后，转换为memdata结构 （数据量小，直接等待返回， 数据量大 异步等待返回） ---数据库构造数据 完成memdata结构的类似操作

model 数据源接口  ---数据库实现 内存实现

数据库实现与内存实现的关键点

获取数据时 只能根据一个数值来获取一记录的所有字段的值
数据库：只能存这个ID，通过ID到数据库查相关字段，然后返回为一个包含相关字段的结构体
内存：存一个包含相关字段的结构体的指针地址

 TreeItem *item = static_cast<TreeItem*>(index.internalPointer()); //获取内存地址  或 数据库  int itemId = (int)(index.internalPointer());
 parents.last()->appendChild(new TreeItem(columnData, parents.last())); //生成指针值
 
   TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);  //设置index的指针数据
		
QAbstractItemModel::createIndex(int arow, int acolumn, void *adata) const;
QModelIndex QAbstractItemModel::createIndex(int arow, int acolumn, quintptr aid)

ITreeModelData
(数据库或内存实现)(接口)(表名)Impl
(Db|Mem)(TreeModelData)(Classificaton)Impl
DBTreeModelDataClassificatonImpl

发起网络请求
界面点击同步数据
            m_pControlCenterLib->getAccountFolders(accountId, protocolType);
内部转入线程发送网络请求

网络数据返回
信号槽
netdata -> memdata  ->db

提炼统一接口 添加网络数据
内存对象和数据库对象分别实现  ---统一有数据管理对象分别调用

数据对象的添加 要放线程中
线程安全处理




QCommLib (接口，数据结构定义)


QNetLib (网络调用 线程实现)
QControlSo (线程数据处理完成信号通知中转 事件通知控制中心  线程(网络\数据库)转换)
QMemLib （内存结构定义）
QDbSo  （数据库操作）
QLog

程序启动时，QMem中没有数据，界面数据列表显示有问题：
等数据加载完成后，再通知界面刷新