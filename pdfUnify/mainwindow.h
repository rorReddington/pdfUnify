#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>

#include "pdfUnify.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void selectFilesSlot();
    void removeFilesSlot();
    void removeFileSlot();
    void selectOuputFileSlot();
    void startSlot();
    void saveCompleteSlot();
    void upSlot();
    void downSlot();

private:
    Ui::MainWindow *ui;

    PDFUnify *pdf;

    void updateTreeWidget();
};

#endif // MAINWINDOW_H
