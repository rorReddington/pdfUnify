#ifndef PDFUNIFY_H
#define PDFUNIFY_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileInfo>

#include "PDFWriter.h"
#include "PDFPage.h"
#include "PageContentContext.h"

class PDFUnify : public QObject
{
    Q_OBJECT

signals:
   void saveCompleteSignal();

public:
    PDFUnify(const QString path = nullptr);
    ~PDFUnify();
    void changeOutput(const QString path);
    void addFiles(const QStringList newFiles);
    void removeFile(const QString file);
    void removeAllFiles();
    QStringList getFiles();
    void save();
private:
    PDFWriter *_pdfWriter;
    QString _output;
    QStringList _files;

    void insertImage(const QString file);
    void mergePDF(const QString file);
    bool fileExists(QString path);
};

#endif // PDFUNIFY_H
