#include "sql_query_model.hpp"

#include <QDebug>
#include <QDate>
#include <QLocale>

SqlQueryModel::SqlQueryModel(QObject* _parent )
	: QSqlQueryModel( _parent )
{
	setQuery("SELECT born_date, name FROM People");

	insertColumn( ColumnId::Year );
	insertColumn( ColumnId::DaysLeft );

	setHeaderData( ColumnId::Date, Qt::Horizontal, tr("Date"));
	setHeaderData( ColumnId::Person, Qt::Horizontal, tr("Person"));
	setHeaderData( ColumnId::Year, Qt::Horizontal, tr("Change to years"));
	setHeaderData( ColumnId::DaysLeft, Qt::Horizontal, tr("Days left..."));
}

QVariant
SqlQueryModel::data( QModelIndex const& _index, int _role) const
{
	if ( !_index.isValid() )
		  return QVariant();

	if ( _role != Qt::DisplayRole )
		return QSqlQueryModel::data( _index, _role );

	auto getBirthdayDate
			= [ this, &_index, &_role ]
			{
				QVariant sqlDate = QSqlQueryModel::data( index( _index.row(), ColumnId::Date ), _role );
				return QDate::fromString( sqlDate.toString(), "yyyy-MM-dd" );
			};

	switch ( _index.column() )
	{
		case ColumnId::Date:
			return QVariant( QLocale( QLocale::Polish, QLocale::Poland ).toString( getBirthdayDate(), "dd MMMM") );

		case ColumnId::Year:
			return QVariant( getBirthdayDate().year() );

		case ColumnId::DaysLeft:
		{
			QDate currentDate( QDate::currentDate() );

			QDate date = getBirthdayDate();
			date.setDate( currentDate.year(), date.month(), date.day() );

			auto daysToBirthday
					= date > currentDate
					? currentDate.daysTo( date )
					: date.daysTo( currentDate )
					;

			return QVariant( daysToBirthday );

		}
	}

	return QSqlQueryModel::data( _index, _role );
}
