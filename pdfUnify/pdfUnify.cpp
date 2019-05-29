#include "pdfUnify.h"

PDFUnify::PDFUnify(const QString path)
{
    _output = path;
}

PDFUnify::~PDFUnify()
{
}

void PDFUnify::changeOutput(const QString path)
{
    _output = path;
}

void PDFUnify::addFiles(const QStringList newFiles)
{
    _files += newFiles;
}

void PDFUnify::removeFile(const QString file)
{
    auto index = _files.indexOf(file);
    _files.removeAt(index);
}

void PDFUnify::removeAllFiles()
{
    _files.clear();
}

QStringList PDFUnify::getFiles()
{
    return _files;
}

bool PDFUnify::fileExists(const QString path)
{
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

void PDFUnify::mergePDF(const QString file)
{
    EStatusCodeAndObjectIDTypeList status;
    status = _pdfWriter->AppendPDFPagesFromPDF(file.toStdString(), PDFPageRange());
    if (status.first != eSuccess)
    {
        delete _pdfWriter;
        throw QString("Неудалось объеденить: %1").arg(file);
    }
}

void PDFUnify::insertImage(const QString file)
{
    PDFPage* page = new PDFPage();

    page->SetMediaBox(PDFRectangle(0, 0, 595, 842)); // set the media box to A4

    PageContentContext* context = _pdfWriter->StartPageContentContext(page);

    if (nullptr == context)
    {
        delete page;
        delete _pdfWriter;
        throw QString("Не удалось создать контекст для страницы\n%1").arg(file);
    }

    context->DrawImage(0, 0, file.toStdString());

    EStatusCode status = eSuccess;
    status = _pdfWriter->EndPageContentContext(context);
    if (status != eSuccess)
    {
        delete page;
        delete _pdfWriter;
        throw QString("Не удалось записать контекст на страницу\n%1").arg(file);
    }

    status = _pdfWriter->WritePage(page);
    if (status != eSuccess)
    {
        delete page;
        delete _pdfWriter;
        throw QString("Не удалось записать страницу в pdf файл\n%1").arg(file);
    }

    delete page;
}

void PDFUnify::save()
{
    if (_output == nullptr) { throw QString("Должен быть указан выходной файл"); }

    if (_files.isEmpty()) { throw QString("Список объединяемых файлов не должен быть пуст"); }

    EStatusCode status = eSuccess;
    _pdfWriter = new PDFWriter();
    status = _pdfWriter->StartPDF(_output.toStdString(), ePDFVersion13, LogConfiguration::DefaultLogConfiguration());
    if (status != eSuccess)
    {
        delete _pdfWriter;
        throw QString("Не удалось создать и запустить файл PDF");
    }

    /* some code */

    foreach (QString file, _files)
    {
        if (!fileExists(file))
        {
            delete _pdfWriter;
            throw QString("Не удалось открыть файл\n%1").arg(file);
        }

        if (file.toStdString().substr(file.toStdString().find_last_of(".") + 1) == "pdf")
        {
            mergePDF(file);
            continue;
        }

        insertImage(file);
    }

    status = _pdfWriter->EndPDF();
    if (status != eSuccess)
    {
        delete _pdfWriter;
        throw QString("Неудалось сохранить pdf файл");
    }
    delete _pdfWriter;

    emit saveCompleteSignal();
}
