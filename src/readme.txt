

model/view

memdata->view

db->memdata


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
QControlLib (线程数据处理完成信号通知中转 事件通知控制中心)
QMemLib （内存结构定义）
QDbLib  （数据库操作）
QLog

程序启动时，QMem中没有数据，界面数据列表显示有问题：
等数据加载完成后，再通知界面刷新