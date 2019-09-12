#include <QDragEnterEvent>
#include <QMimeData>
#include <QPicture>
#include <QImage>
#include <QPixmap>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QBuffer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    QString imageFile = "C:\\Users\\afTvber\\Desktop\\aaa";
    QImageReader reader(imageFile);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(imageFile), reader.errorString()));
        return;
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
//    if(event->mimeData()->hasImage() || event->mimeData()->hasHtml())
        event->accept();//ProposedAction();
    //    if (event->mimeData()->hasFormat("text/plain"))
    //        event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event){

}
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event){}

QImage GetImageFromDrop(const QMimeData* mime, const QString& format)
{
    if(!mime->hasFormat(format))
        return QImage();
    QByteArray data = mime->data(format);
    if(data.isNull() || data.isEmpty())
        return QImage();
    QBuffer buffer(&data);
    if(!buffer.open(QIODevice::ReadOnly))
        return QImage();
    QImageReader imageReader(&buffer);
    imageReader.setAutoTransform(true);
    QImage image = imageReader.read();
    if(image.isNull())
        return QImage();
    return image;
}
void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug() << event->mimeData()->formats();
    QImage image;
    if(event->mimeData()->hasImage())
    {
        auto image = event->mimeData()->imageData();
        ui->imageLabel->setPixmap(QPixmap::fromImage(image.value<QImage>()));
        event->acceptProposedAction();
        return;
    }

    static QStringList sss({
                               "application/x-qt-windows-mime;value=\"DragImageBits\"",
                               "application/x-qt-windows-mime;value=\"DragContext\"",
                               "application/x-qt-windows-mime;value=\"chromium/x-renderer-taint\"",
                               "application/x-qt-windows-mime;value=\"FileGroupDescriptorW\"",
                               "application/x-qt-windows-mime;value=\"FileContents\"",
                               "application/x-qt-windows-mime;value=\"UniformResourceLocatorW\"",
                           });
    for(auto&& format:sss)
    {
        if( !(image = GetImageFromDrop(event->mimeData(),
                                            format)).isNull() )
        {
            ui->imageLabel->setPixmap(QPixmap::fromImage(image));
            return;
        }
    }

    if(event->mimeData()->hasFormat("application/x-qt-windows-mime"))
    {
        event->mimeData()->data("application/x-qt-windows-mime");
        return;
    }

//    else if(event->mimeData()->hasHtml())
//    {
//        QString html = event->mimeData()->html();
//        QMessageBox::information(this,"",html);
//    }
//    else if (event->mimeData()->hasUrls())
//    {
//        QStringList pathList;
//        QList<QUrl> urlList = event->mimeData()->urls();

//        // extract the local paths of the files
//        for (int i = 0; i < urlList.size() && i < 32; +i)
//        {
//            pathList.append(urlList.at(i).toLocalFile());
//        }

//        // call a function to open the files

//    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

