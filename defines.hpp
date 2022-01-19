#pragma once

#include <QString>

const QString DatabaseName = "birthdays.db";

namespace Messages
{
	const QString DatabaseConnectionSuccess = "Database '" + DatabaseName + "' connected.";
	const QString DatabaseConnectionFailed = "Database '" + DatabaseName + "' not connected!";
}
