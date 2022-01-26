#include "sql_query_model.hpp"
#include "column_ids.hpp"

#include <QDebug>
#include <QDate>
#include <QLocale>
#include <QSqlRecord>
#include <QString>

SqlQueryModel::SqlQueryModel(QObject* _parent )
	: QSqlQueryModel( _parent )
{
	setQuery("SELECT born_date, name FROM People");

	insertColumn( ColumnId::Age );
	insertColumn( ColumnId::DaysLeft );

	setHeaderData( ColumnId::Date, Qt::Horizontal, tr("Date"));
	setHeaderData( ColumnId::Person, Qt::Horizontal, tr("Person"));
	setHeaderData( ColumnId::Age, Qt::Horizontal, tr("Age"));
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

	auto getAge
			= [ &getBirthdayDate ]() -> int
			{
				QDate birthdayDate = getBirthdayDate();
				QDate currentDate = QDate::currentDate();

				int offset
					=     ( currentDate.month() < birthdayDate.month() )
					   || ( currentDate.month() == birthdayDate.month() && currentDate.day() < birthdayDate.day() )
					? -1
					: 0
					;

				return currentDate.year() - birthdayDate.year() + offset;
			};

	if ( _role == Qt::DisplayRole )
	{
		switch ( _index.column() )
		{
			case ColumnId::Date:
				return QVariant( QLocale( QLocale::Polish, QLocale::Poland ).toString( getBirthdayDate(), "dd MMMM") );

			case ColumnId::Age:
			{
				QString field = QString( "%1 (%2)" )
						.arg( getAge() )
						.arg( getBirthdayDate().year() )
						;

				return QVariant( field );
			}

			case ColumnId::DaysLeft:
			{
				QDate currentDate( QDate::currentDate() );

				QDate date = getBirthdayDate();
				date.setDate( currentDate.year(), date.month(), date.day() );
				if ( date < currentDate )
					date = date.addYears( 1 );

				return QVariant( currentDate.daysTo( date ) );
			}
		}
	}
	else if ( _role == Qt::UserRole )
	{
		switch ( _index.column() )
		{
			case ColumnId::Date:
				return QVariant( getBirthdayDate() );

			case ColumnId::Age:
				return QVariant( getAge() );
		}
	}
	else if ( _role == Qt::TextAlignmentRole )
	{
		return Qt::AlignCenter;
	}

	return QSqlQueryModel::data( _index, _role );
}
