#include "sort_proxy_model.hpp"
#include "column_ids.hpp"

#include <QDate>

SortProxyModel::SortProxyModel( QObject * _parent )
	: QSortFilterProxyModel( _parent )
{
	setFilterKeyColumn( ColumnId::Person );
	setFilterCaseSensitivity( Qt::CaseInsensitive );
}

bool
SortProxyModel::lessThan( QModelIndex const& _source_left, QModelIndex const& _source_right ) const
{
	switch ( _source_right.column() )
	{
		case ColumnId::Date:
		{
			auto leftDate = sourceModel()->data( _source_left, Qt::UserRole ).toDate();
			auto rightDate = sourceModel()->data( _source_right, Qt::UserRole ).toDate();

			if ( leftDate.month() == rightDate.month() )
				return leftDate.day() < rightDate.day();

			return leftDate.month() < rightDate.month();
		}
		break;

		case ColumnId::Age:
		{
			return
				  sourceModel()->data( _source_left, Qt::UserRole ).toInt()
				< sourceModel()->data( _source_right, Qt::UserRole ).toInt()
				;
		}
		break;
	}

	return QSortFilterProxyModel::lessThan( _source_left, _source_right );
}
