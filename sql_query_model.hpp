#pragma once

#include <QSqlQueryModel>

class SqlQueryModel
		: public QSqlQueryModel
{

public:
	SqlQueryModel( QObject* _parent = nullptr );

public:
	QVariant data( QModelIndex const& _index, int role ) const;
};

