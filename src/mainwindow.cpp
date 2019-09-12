#include <QDragEnterEvent>
#include <QMimeData>
#include <QPicture>
#include <QImage>
#include <QPixmap>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasImage() || event->mimeData()->hasHtml())
        event->acceptProposedAction();
//    if (event->mimeData()->hasFormat("text/plain"))
//        event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event){

}
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event){}
void MainWindow::dropEvent(QDropEvent *event){
//    textBrowser->setPlainText(event->mimeData()->text());
//        mimeTypeCombo->clear();
//        mimeTypeCombo->addItems(event->mimeData()->formats());

    if(event->mimeData()->hasImage())
    {
        auto image = event->mimeData()->imageData();
        ui->imageLabel->setPixmap(QPixmap::fromImage(image.value<QImage>()));
    }
    else if(event->mimeData()->hasHtml())
    {
        auto html = event->mimeData()->html();
        ui->imageLabel->setText(html);
    }

    event->acceptProposedAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

