#include "main_window.hpp"
#include "ui_main_window.h"

#include "defines.hpp"
#include "sql_query_model.hpp"
#include "sort_proxy_model.hpp"
#include "column_ids.hpp"

#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_database = QSqlDatabase::addDatabase("QSQLITE");

	m_database.setDatabaseName(
				  qApp->applicationDirPath()
				+ QDir::separator()
				+ DatabaseName );

	ui->statusbar->showMessage(
				  m_database.open()
				? Messages::DatabaseConnectionSuccess
				: Messages::DatabaseConnectionFailed
				);

	if ( !m_database.isOpen() )
		return;

	auto sortModel = new SortProxyModel( this );
	sortModel->setDynamicSortFilter( true );
	sortModel->setSourceModel( new SqlQueryModel( this ) );
	sortModel->setFilterKeyColumn( ColumnId::Person );

	ui->tableView->setModel( sortModel );
	ui->tableView->sortByColumn( ColumnId::DaysLeft, Qt::SortOrder::AscendingOrder );
	ui->tableView->setColumnWidth( ColumnId::Person, 500 );
	ui->tableView->selectRow( 0 );

	connect( ui->lineEdit, &QLineEdit::textChanged, sortModel, &SortProxyModel::setFilterFixedString );
}

MainWindow::~MainWindow()
{
	delete ui;
}

