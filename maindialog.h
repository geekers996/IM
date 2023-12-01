#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QHostInfo>
#include <QMessageBox>
#include <QLabel>
#include <QDateTime>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>



QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();


private:
    QTcpSocket *m_TcpMsgClient;     // 处理聊天消息socket
    QTcpSocket *m_TcpFileClient;    // 处理文件传输消息socket

    QFile *m_LocalFiles; // 要传输的文件
    qint64 m_TotalBytes; // 数据总大小
    qint64 m_BytesWrites; // 已经发送数据大小
    qint64 m_BytesToWrites; // 剩下数据大小
    qint64 m_LoadSizes; // 每次发送数据的大小
    QString m_FileNames; // 保存文件信息

    QByteArray m_OutDataBlock; //数据缓冲区（即存放每次要发送的数据）


    void paintEvent(QPaintEvent *event);  // 实现更改窗口背景
    QString GetLocalIPAddress(); // 获取本机的IP地址信息
    void closeEvent(QCloseEvent *event); // 关闭事件



    // 系统托盘
    QSystemTrayIcon *MySystemTrays; // 托盘指针
    QMenu *pContextMenu; // 托盘菜单

    QAction *qMiniAction;       // 客户端最小化
    QAction *qRestoreAction;    // 恢复客户端
    QAction *qExitAction;       // 退出系统






    // 自定义槽函数
private slots:
    void OnConnectedFunc(); // 客户端连接服务器
    void OnDisconnectedFunc(); // 客户端与服务器断开
    void OnSocketReadyReadFunc(); // 读取服务器socket传输的数据信息

    void UpdateClientProgressFunc(qint64); // 文件传输及显示进度条更新
    void DisplayErrorFunc(QAbstractSocket::SocketError); // 异常处理信息

    void MySystemTrayFunc(); // 系统托盘函数




    void on_pushButton_ConnectServer_clicked();

    void on_pushButton_DisconnectServer_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_ClearMsg_clicked();

    void on_pushButton_SendMsg_clicked();

    void on_pushButton_SelectFile_clicked();

    void on_pushButton_SendFile_clicked();

private:
    Ui::MainDialog *ui;
};
#endif // MAINDIALOG_H
