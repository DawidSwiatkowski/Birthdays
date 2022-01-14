#pragma once

#include <QSqlQueryModel>

class SqlQueryModel
		: public QSqlQueryModel
{

public:
	SqlQueryModel( QObject* _parent = nullptr );
};

