#pragma once

#include <QString>

namespace Birthdays
{
	const QString DatabaseName = "birthdays.db";

namespace Message
{
	const QString DatabaseConnectionSuccess = "Database '" + DatabaseName + "' connected.";
	const QString DatabaseConnectionFailed = "Database '" + DatabaseName + "' not connected!";
}


}
