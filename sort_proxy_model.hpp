#pragma once

#include <QSortFilterProxyModel>

class SortProxyModel
		: public QSortFilterProxyModel
{

public:
	explicit SortProxyModel( QObject *_parent = nullptr );

protected:
	bool lessThan( QModelIndex const& _source_left, QModelIndex const& _source_right ) const override;
};

