#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

class Database
{
public:
	Database(char* filename);
	~Database();
	
	bool open(char* filename);
	vector<vector<string> > query(char* query);
	void close();
	
private:
	sqlite3 *database;
};

Database::Database(char* filename)
{
	database = NULL;
	open(filename);
}

Database::~Database()
{
}

bool Database::open(char* filename)
{
	if(sqlite3_open(filename, &database) == SQLITE_OK)
		return true;
    
	return false;
}

vector<vector<string> > Datab::query(char* query)
{
	sqlite3_stmt *statement;
	vector<vector<string> > results;
    
	if(sqlite3_prepare_v2(database, query, -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);
			
			if(result == SQLITE_ROW)
			{
				vector<string> values;
				for(int col = 0; col < cols; col++)
				{
                    std::string val;
                    char * ptr =(char*)sqlite3_column_text(statement, col);
                    
                    if(ptr){
                        val = ptr;
                    }
                    else val = "";
                    values.push_back(val);
				}
				results.push_back(values);
			}
			else
			{
				break;
			}
		}
        
		sqlite3_finalize(statement);
	}
	
	string error = sqlite3_errmsg(database);
	if(error != "not an error") cout << query << " " << error << endl;
	
	return results;
}

void Database::close()
{
	sqlite3_close(database);
}


Database db;

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

