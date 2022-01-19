#pragma once

#include <QSortFilterProxyModel>

class SortProxyModel
		: public QSortFilterProxyModel
{

public:
	explicit SortProxyModel( QObject *_parent = nullptr );

};

