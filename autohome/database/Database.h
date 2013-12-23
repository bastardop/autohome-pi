//
//  Database.h
//  
//
//  Code  from TyVeryMuch in dreamincode.net August 26th 2009
//
//

#ifndef __DATABASE_H__
#define __DATABASE_H__

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

#endif
