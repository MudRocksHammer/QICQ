#ifndef GLOABAL_H
#define GLOABAL_H

#include <stdint.h>
#include <string>
#include <stdio.h>

#include <QDesktopWidget>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>
#include <QAbstractButton>
#include <QTime>
#include <QProcess>
#include <QDir>
#include <QApplication>
#include <QStyleFactory>
#include <QInputDialog>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QStyle>
#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <QPainter>
#include <QBitmap>
#include <QPixmap>
#include <QSound>

#include "myapp.h"
#include "unit.h"

class myHelper : public QObject{
public:
    //设置开机启动
    static void AutoRunWithSystem(bool isAutoRun, QString AppName){
        QString AppPath = QApplication::applicationFilePath();
        AppPath = AppPath.replace("/", "\\");

        QSettings* reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVerion\\Run",
                                       QSettings::NativeFormat);
        if(isAutoRun)
            reg->setValue(AppName, AppPath);
        else
            reg->setValue(AppName, "");
    }

    //设置编码为utf-8
    static void SetUTF8Code(){
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //窗体居中并且只有关闭按钮，不能调整大小
    static void FormOnlyCloseInCenter(QWidget* frm){
        //设置窗体居中
        QDesktopWidget desktop;
        int screenX = desktop.availableGeometry().width();
        int screenY = desktop.availableGeometry().height() - 40;
        int frmX = frm->width();
        int frmY = frm->height();
        QPoint movePoint(screenX / 2 - frmX / 2, screenY / 2 - frmY / 2);
        frm->move(movePoint);

        //设置窗体不能调整大小
        frm->setFixedSize(frmX, frmY);

        //设置窗体只有最小化按钮
        frm->setWindowFlag(Qt::WindowCloseButtonHint);
    }

    //窗体居中显示
    static void FormCenter(QWidget* frm){
        int screenX = qApp->desktop()->availableGeometry().width();
        int screenY = qApp->desktop()->availableGeometry().height() - 60;
        int wndX = frm->width();
        int wndY = frm->height();
        QPoint movePoint((screenX - wndX) / 2, (screenY - wndY) / 2);
        frm->move(movePoint);
    }

    //窗体取消最大化窗口
    static void FormNoMaxButton(QWidget* frm){
        frm->setWindowFlag(Qt::WindowMinimizeButtonHint);
    }

    //窗体只有关闭按钮
    static void FormOnlyCloseButton(QWidget* frm){
        frm->setWindowFlag(Qt::WindowCloseButtonHint);
    }

    //窗体大小不能改变
    static void FormNoResize(QWidget* frm){
        frm->setFixedSize(frm->width(), frm->height());
    }

    //设置样式
    static void setStyle(const QString& style){
        QFile file(":/resource/qss" + style + ".css");
        file.open(QIODevice::ReadOnly);
        qApp->setStyleSheet(file.readAll());
        file.close();
    }

    //延时
    static void Sleep(int sec){
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while(QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //判断是否是IP地址
    static bool IsIP(QString IP){
        QRegExp reg_exp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return reg_exp.exactMatch(IP);
    }

    //获取本机IP
    static QString GetIP(){
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        for(auto address : list){
            if(address.protocol() == QAbstractSocket::IPv4Protocol)
                return address.toString();
        }
        return "";
    }

    //获取文件大小
    static QString GetFileSize(const QString& name){
        QFileInfo file_info(MyApp::m_strRecvPath + name);
        //return CalcSize(file_info.size());
    }

    //获取选择的文件
    static QString GetFileName(QString filter){
        return QFileDialog::getOpenFileName(NULL, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }

    //获取选择的文件集合
    static QStringList GetFileNames(QString filter){
        return QFileDialog::getOpenFileNames(NULL, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }

    //获取选择的目录
    static QString GetFolderName(){
        return QFileDialog::getExistingDirectory();
    }

    //获取文件名，含拓展名
    static QString GetFileNameWithExtension(QString strFilePath){
        QFileInfo file_info(strFilePath);
        return file_info.fileName();
    }

    //获取选择文件夹中的文件
    static QStringList GetFolderFileNames(QStringList filter){
        QStringList file_list;
        QString str_folder = QFileDialog::getExistingDirectory();
        if(!str_folder.length() == 0){
            QDir my_folder(str_folder);
            if(my_folder.exists()){
                file_list = my_folder.entryList(filter);
            }
        }
        return file_list;
    }

    //文件夹是否存在
    static bool FolderIsExist(QString strFolder){
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    //文件是否存在
    static bool FileIsExist(QString strFile){
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    //删除目录下所有文件
    static void CleadDirPath(QString strPath){
        QDir dir(strPath);
        for(auto file : dir.entryInfoList()){
            if(file.isFile()){
                if(file.fileName().endsWith("wav")){
                    bool bOk = QFile::remove(file.filePath());
                    qDebug() << "Remove Old record files:" << bOk << file.filePath();
                }
            }
            else{
                if(file.fileName() == "." || file.fileName() == "..") continue;
                CleadDirPath(file.absoluteFilePath());
            }
        }
    }

    //复制文件
    static bool CopyFile(QString sourceFile, QString targetFile){
        if(FileIsExist(targetFile)){
            int ret = QMessageBox::information(NULL, "提示", "文件已经存在,是否替换?", QMessageBox::Yes | QMessageBox::No);
            if(ret != QMessageBox::Yes){
                return false;
            }
        }
        return QFile::copy(sourceFile, targetFile);
    }

    //播放声音
    static void PlaySound(const QString& name){
        QString strSound = MyApp::m_strSoundPath + name + ".wav";
        if(!QFile::exists(strSound)) return;
        QSound::play(strSound);
    }

    //转换html
    static void strToHtmlFilter(QString& str){
        //注意这几行代码的顺序不能乱,否则会导致多次替换
        str.replace("&", "&amp;");
        str.replace(">", "&gt;");
        str.replace("<", "&lt;");
        str.replace("\"", "&quot;");
        str.replace("\'", "&#39;");
        str.replace(" ", "&nbsp;");
        str.replace("\n", "<br>");
        str.replace("\r", "<br>");
    }

    //string  to html
    static void strToHtml(QString& str, QColor color){
        QByteArray array;
        array.append(color.red());
        array.append(color.green());
        array.append(color.blue());
        QString strC(array.toHex());
        str = QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
    }

    //html添加图片
    static void imgPathToHtml(QString& path){
        path = QString("<img src=\"%1\"/>").arg(path);
    }

    //html添加文本
    static void strToHtmlText(QString& str){
        str = QString("<span><p> %1</span></p>").arg(str);
    }

    //
    static QPixmap PixmapToRound(const QPixmap& src, int radius){
        if(src.isNull())
            return QPixmap();

        QSize size(2 * radius, 2 * radius);
        QBitmap mask(size);
        QPainter painter(&mask);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
        painter.setBrush(QColor(0, 0, 0));
        painter.drawRoundedRect(0, 0, size.width(), size.height(), 90, 90);

        QPixmap image = src.scaled(size);
        image.setMask(mask);
        return image;
    }

    //灰度
    static QPixmap ChangeGrayPixmap(const QImage& image){
        QImage newImage = image;
        if(newImage.isNull())
            return QPixmap();
        QColor oldColor;
        for(int x = 0; x < newImage.width(); x++){
            for(int y = 0; y < newImage.height(); y++){
                oldColor = QColor(newImage.pixel(x, y));
                int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
                newImage.setPixel(x, y, qRgb(average, average, average));
            }
        }
        return QPixmap::fromImage(newImage);
    }

    //文件大小转换
    static QString CalcSize(qint64 bytes){
        QString strUnit;
        double dSize = bytes * 1.0;
        if(dSize <= 0)
            dSize = 0.0;
        else if (dSize < 1024)
            strUnit = "Bytes";
        else if (dSize < 1024 * 1024){
            strUnit = "KB";
            dSize /= 1024;
        }
        else if (dSize < 1024 * 1024 * 1024){
            strUnit = "MB";
            dSize /= 1024 * 1024;
        }
        else {
            dSize /= 1024 * 1024 * 1024;
            strUnit = "GB";
        }

        return QString("%1 %2").arg(QString::number(dSize, 'f', 2)).arg(strUnit);

    }

    //计算下载速率
    static QString CalcSpeed(double speed){
        QString strUnit;
        if(speed <= 0){
            speed = 0;
            strUnit = "Bytes/s";
        }
        else if(speed < 1024){
            strUnit = "Bytes/s";
        }
        else if(speed < 1024 * 1024){
            speed /= 1024;
            strUnit = "KB/s";
        }
        else if(speed < 1024 * 1024 * 1024){
            speed /= 1024 * 1024;
            strUnit = "MB/s";
        }
        else{
            speed /= 1024 * 1024 * 1024;
            strUnit = "GB/s";
        }

        QString strSpeed = QString::number(speed, 'f', 2);
        return QString("%1 %2").arg(strSpeed).arg(strUnit);
    }

};

#endif // GLOABAL_H
