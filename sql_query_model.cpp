#include "sql_query_model.hpp"
#include "column_ids.hpp"

#include <QDebug>
#include <QDate>
#include <QLocale>
#include <QSqlRecord>

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

	auto getBirthdayDate
			= [ this, &_index, &_role ]
			{
				return QDate::fromString(
							  record( _index.row() ).value( ColumnId::Date ).toString()
							, "yyyy-MM-dd"
							);
			};

	if ( _role == Qt::DisplayRole )
	{
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
	}
	else if ( _role == Qt::UserRole )
	{
		switch ( _index.column() )
		{
			case ColumnId::Date:
				return QVariant( getBirthdayDate() );
		}
	}

	return QSqlQueryModel::data( _index, _role );
}
