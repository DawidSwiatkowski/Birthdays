#include "sql_query_model.hpp"

#include <QDebug>

SqlQueryModel::SqlQueryModel(QObject* _parent )
	: QSqlQueryModel( _parent )
{
	setQuery("SELECT name, born_date FROM People");

	setHeaderData(0, Qt::Horizontal, tr("Person"));
	setHeaderData(1, Qt::Horizontal, tr("Data"));	
}
