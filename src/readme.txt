��׺Ϊ.so��shared object�����ļ�ΪLinux�ϵĶ�̬���ļ���Linux�ϵľ�̬���ļ�Ϊ.a(akynesis)




model/view

memdata->view

�໥֮�������---
����ͬ��������->memdata�仯->model�仯->view�仯
����ͬ�����ݣ�
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
pAccount->fetchAllFoldersOperation(); //�߳���������������������
}
account::QAccount::fetchAllFoldersOperation(bool urgent /*= false*/)
{
	m_pIncommingServer->fetchAllFoldersOperation(urgent); //�߳���������������������
}
m_pIncommingServer = new QImapServer();

QImapServer::fetchAllFoldersOperation(bool urgent)
{
	m_pImapFetchAllFoldersOperationCallback = new ImapFetchAllFoldersOperationCallback();
	connect(m_pImapFetchAllFoldersOperationCallback, SIGNAL(fetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&, unsigned int)),
		this, SLOT(onFetchAllFoldersOperationFinished(mailcore::ErrorCode, const QVariant&, const QString&, unsigned int)));
}
����ͳһ�Է��ش���
QIncommingServer::onFetchAllFoldersOperationFinished(mailcore::ErrorCode code, const QVariant& folders, const QString& strErrorMessage, unsigned int taskIndex)
{
    emit fetchAllFoldersOperationFinished(code, folders, strErrorMessage);
}

QMailNetThreadEntity::connectWithAccountSignals(account::QAccount *pAccount)
{
    //��ȡ�����ʼ��� �ź�����
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
//�ڴ����������
m_ctrlCenterRef->recursionAddFolder(folderListPath, FORWARD_SLASH_ONE, inServerId, stInServerInfo.protocolType);
if (bReflashFolders)
        emit signalAccountsMailFoldersChanged(stInServerInfo.accountId);  //֪ͨ����ˢ��
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
�����߳�ͬ��������ݺ�,�����ݴ������̣߳�Ȼ����뵽�ڴ�
QMailNetThreadEntity* m_threadEntity;  //ͬ�������߳� QThread m_netThread;������߳���ִ��
QMailNetThreadWrapper * m_mailNetWrapper; //ͨ�������źŲ� ������ת�����߳�

���뵽�ڴ��
ͨ���źŲ۸��½��� ui.mailFolderTreeView->refreshMailFolderTreeView();

view�仯-> memdata�仯->model�仯


db->memdata

��ʼ����������������̫������Ҫ���߳��м���������ݿ��е����ݺ���֪ͨ����ˢ��
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

//���������
a.���ݿ�ṹ��modelԴ�ڴ�ṹһ�£�ֱ�Ӵ����ݿ��в�ѯ����[ͨ��sql����ȡ���ֵ] ����������С�޹أ��ؼ���sql����ѯ�ٶ� ֱ�������߳��в����ȴ������ʾ��

b.���ݿ�ṹ��modelԴ�ڴ�ṹmemdata��һ��(����ͼ), �����ݿ�һ�μ��غ�ת��Ϊmemdata�ṹ ��������С��ֱ�ӵȴ����أ� �������� �첽�ȴ����أ� ---���ݿ⹹������ ���memdata�ṹ�����Ʋ���

model ����Դ�ӿ�  ---���ݿ�ʵ�� �ڴ�ʵ��

���ݿ�ʵ�����ڴ�ʵ�ֵĹؼ���

��ȡ����ʱ ֻ�ܸ���һ����ֵ����ȡһ��¼�������ֶε�ֵ
���ݿ⣺ֻ�ܴ����ID��ͨ��ID�����ݿ������ֶΣ�Ȼ�󷵻�Ϊһ����������ֶεĽṹ��
�ڴ棺��һ����������ֶεĽṹ���ָ���ַ

 TreeItem *item = static_cast<TreeItem*>(index.internalPointer()); //��ȡ�ڴ��ַ  �� ���ݿ�  int itemId = (int)(index.internalPointer());
 parents.last()->appendChild(new TreeItem(columnData, parents.last())); //����ָ��ֵ
 
   TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);  //����index��ָ������
		
QAbstractItemModel::createIndex(int arow, int acolumn, void *adata) const;
QModelIndex QAbstractItemModel::createIndex(int arow, int acolumn, quintptr aid)

ITreeModelData
(���ݿ���ڴ�ʵ��)(�ӿ�)(����)Impl
(Db|Mem)(TreeModelData)(Classificaton)Impl
DBTreeModelDataClassificatonImpl

������������
������ͬ������
            m_pControlCenterLib->getAccountFolders(accountId, protocolType);
�ڲ�ת���̷߳�����������

�������ݷ���
�źŲ�
netdata -> memdata  ->db

����ͳһ�ӿ� �����������
�ڴ��������ݿ����ֱ�ʵ��  ---ͳһ�����ݹ������ֱ����

���ݶ������� Ҫ���߳���
�̰߳�ȫ����




QCommLib (�ӿڣ����ݽṹ����)


QNetLib (������� �߳�ʵ��)
QControlSo (�߳����ݴ�������ź�֪ͨ��ת �¼�֪ͨ��������  �߳�(����\���ݿ�)ת��)
QMemLib ���ڴ�ṹ���壩
QDbSo  �����ݿ������
QLog

��������ʱ��QMem��û�����ݣ����������б���ʾ�����⣺
�����ݼ�����ɺ���֪ͨ����ˢ��