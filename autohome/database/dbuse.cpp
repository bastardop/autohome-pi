#include <iostream>
#include "Database/Database.h"

using namespace std;

Database *db;

db = new Database("/var/www/liteadmin/weather");
//db->query("CREATE TABLE a (a INTEGER, b INTEGER);");
//db->query("INSERT INTO a VALUES(1, 2);");
//db->query("INSERT INTO a VALUES(5, 4);");
vector<vector<string> > result = db->query("SELECT * FROM location;");
for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
{
	vector<string> row = *it;
	cout << "Values: (key=" << row.at(0) << ", name=" << row.at(1) << ")" << endl;
}
db->close();

