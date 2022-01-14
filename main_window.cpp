#include "main_window.hpp"
#include "ui_main_window.h"

#include "defines.hpp"
#include "sql_query_model.hpp"

#include <QDebug>
#include <QDir>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(
				  qApp->applicationDirPath()
				+ QDir::separator()
				+ Birthdays::DatabaseName );

	ui->statusbar->showMessage(
				  m_database.open()
				? Birthdays::Message::DatabaseConnectionSuccess
				: Birthdays::Message::DatabaseConnectionFailed
				);

	if ( m_database.isOpen() )
		ui->treeView->setModel( new SqlQueryModel( ui->treeView ) );
}

MainWindow::~MainWindow()
{
	delete ui;
}

