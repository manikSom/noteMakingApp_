#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->mainWindowTextEdit);
    this->setWindowTitle("Note Taking app (made with Qt)");
    this->setWindowIcon(QIcon(":/icons_/take-note.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// functionality when a new file option is clicked
void MainWindow::on_actionNew_File_triggered()
{
    currentFile.clear();
    ui->mainWindowTextEdit->setText(QString());
}

// functionality when the user wants to open a file
void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the File");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice:: ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot Open file:"+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file); //Interface for reading text
    QString text = in.readAll();
    ui->mainWindowTextEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as.");
    QFile file(fileName);
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot Save file:"+file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file); //Interface for writing text
    QString text = ui->mainWindowTextEdit->toPlainText();
    out << text; // the text from Dialog is written into the file stream
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer; // allows us to interact with any printer in our network.
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec()== QDialog::Rejected){
        QMessageBox::warning(this,"warning","Cannot access Printer");
        return;
    }
    ui->mainWindowTextEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->mainWindowTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->mainWindowTextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->mainWindowTextEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->mainWindowTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->mainWindowTextEdit->redo();
}

