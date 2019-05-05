#include "main.h"

using namespace std;
using namespace PDFHummus;

PDFWriter pdfWriter;

EStatusCode writeImageToPDF(const string filePath)
{
	EStatusCode status = eSuccess;

	if (filePath.length() < 4) return eFailure;

	PDFPage* page = new PDFPage(); // create the page object
	page->SetMediaBox(PDFRectangle(0, 0, 595, 842)); // set the media box to A4

	PageContentContext* pageContentContext = pdfWriter.StartPageContentContext(page); // create the page context
	if (NULL == pageContentContext)
	{
		cout << "failed to create content context for page\n";
		return eFailure;
	}

	AbstractContentContext::ImageOptions imageOptions;

	if (filePath.substr(filePath.find_last_of(".") + 1) == "png")
	{
		imageOptions.transformationMethod = AbstractContentContext::eMatrix;
		imageOptions.matrix[0] = imageOptions.matrix[3] = 0.24;
	}

	pageContentContext->DrawImage(0, 0, filePath, imageOptions);

	status = pdfWriter.EndPageContentContext(pageContentContext);
	if (status != eSuccess)
	{
		cout << "failed to end content context\n";
		return eFailure;
	}

	status = pdfWriter.WritePage(page);
	if (status != eSuccess)
	{
		cout << "failed to write page\n";
		return eFailure;
	}

	return status;
}

EStatusCodeAndObjectIDTypeList writePDFPagesToPDF(const string filePath)
{
	EStatusCodeAndObjectIDTypeList status;

	status = pdfWriter.AppendPDFPagesFromPDF(filePath, PDFPageRange());
	return status;
}

int main(int argc, char* argv[])
{
	EStatusCode status = eSuccess;

	status = pdfWriter.StartPDF("c:\\test\\myFile.pdf", ePDFVersion13, LogConfiguration(true, true, "c:\\test\\myFile.log"));
	if (status != eSuccess)
	{
		cout << "failed to start pdf file\n";
		return 1;
	}

	status = writeImageToPDF("c:\\test\\image.png");
	if (status != eSuccess)
	{
		cout << "failed image.png\n";
		return 2;
	}

	status = writeImageToPDF("c:\\test\\image.jpg");
	if (status != eSuccess)
	{
		cout << "failed image.jpg\n";
		return 2;
	}

	status = writeImageToPDF("c:\\test\\image.tif");
	if (status != eSuccess)
	{
		cout << "failed image.tif\n";
		return 2;
	}

	status = writeImageToPDF("c:\\test\\linux.png");
	if (status != eSuccess)
	{
		cout << "failed linux.png\n";
		return 2;
	}

	status = writeImageToPDF("c:\\test\\G32DS.TIF");
	if (status != eSuccess)
	{
		cout << "failed linux.png\n";
		return 2;
	}

	if (writePDFPagesToPDF("c:\\test\\test.pdf").first != eSuccess) 
	{
		cout << "failed merge test.pdf\n";
		return 3;
	}

	status = pdfWriter.EndPDF();
	if (status != eSuccess)
	{
		cout << "failed to end pdf\n";
		return 4;
	}

	return 0;
}