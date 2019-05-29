#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->label->setHidden(true);

    QStringList headers;
    headers.append("Имя");
    headers.append("Расположение");
    headers.append("Размер");
    headers.append("Изменен");
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(headers);

    pdf = new PDFUnify();

    connect(pdf, &PDFUnify::saveCompleteSignal, this, &MainWindow::saveCompleteSlot);

    connect(ui->pushButtonAddFiles, &QPushButton::released, this, &MainWindow::selectFilesSlot);
    connect(ui->pushButtonRemoveAll, &QPushButton::released, this, &MainWindow::removeFilesSlot);
    connect(ui->pushButtonRemoveFile, &QPushButton::released, this, &MainWindow::removeFileSlot);
    connect(ui->toolButtonSelect, &QToolButton::released, this, &MainWindow::selectOuputFileSlot);
    connect(ui->pushButtonStart, &QToolButton::released, this, &MainWindow::startSlot);
}

MainWindow::~MainWindow()
{
    delete pdf;
    delete ui;
}

void MainWindow::updateTreeWidget()
{
    ui->treeWidget->clear();

    auto files = pdf->getFiles();

    foreach (QString file, files)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();

        QFileInfo fi(file);

        itm->setText(0, fi.fileName());
        itm->setText(1, file);
        itm->setText(2, QString::number(fi.size()));
        itm->setText(3, fi.lastModified().toString("HH:mm:ss   dd-MM-yyyy"));

        ui->treeWidget->addTopLevelItem(itm);
    }

    if (files.count() > 0)
    {
        ui->label->setText(QString("Всего %1 файлов в работе").arg(files.count()));
        ui->label->setHidden(false);
    } else ui->label->setHidden(true);
}

void MainWindow::selectFilesSlot()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Выберите файлы"), "", tr("Images and pdf (*.pdf *.png *.jpg *.jpeg *.tif *.tiff)"));

    if (files.isEmpty()) return;

    pdf->addFiles(files);
    updateTreeWidget();
}

void MainWindow::removeFilesSlot()
{
    pdf->removeAllFiles();
    updateTreeWidget();
}

void MainWindow::removeFileSlot()
{
    auto item = ui->treeWidget->currentItem();

    if (item == nullptr) { return; }

    pdf->removeFile(item->text(1));
    updateTreeWidget();
}

void MainWindow::selectOuputFileSlot()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Сохранить..."), nullptr, tr("Portable Document Format (*.pdf)"));
    pdf->changeOutput(file);
    ui->lineEdit->setText(file);
}

void MainWindow::startSlot()
{
    ui->pushButtonStart->setEnabled(false);

    try {
     pdf->save();
    } catch (const QString exc) {
        QMessageBox messageBox;
        messageBox.critical(this, "Ошибка", exc);
        messageBox.setFixedSize(800,400);
        ui->pushButtonStart->setEnabled(true);
    }
}

void MainWindow::saveCompleteSlot()
{
    ui->pushButtonStart->setEnabled(true);
    QMessageBox messageBox;
    messageBox.information(this, "Завершено", "Cохранение завершено");
    messageBox.setFixedSize(800,400);
}
