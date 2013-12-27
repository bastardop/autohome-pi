#include "sqdb.h"
#include <iostream>

using namespace std;
string name;
string channel_id;
string sender_id;
char quer;
int main()
{

name = "zimmer9";
channel_id = "99";
sender_id = "9999";
sqdb::Db db("/var/www/liteadmin/weather");
try {
sqdb::Statement i = db.Query("insert into location (name, sender_id, channel_id) values (?, ?, ?)");
i.Bind(1, name);
i.Bind(2, sender_id);
i.Bind(3, channel_id);
i.Next();
}
catch ( const sqdb::Exception& e ){
sqdb::Exception excep(sqdb::Exception&);
cout << "Fehler ist aufgetreten " << excep << endl;
}

sqdb::Statement s = db.Query("select * from location;");
  while ( s.Next() )
  {
    int i = s.GetField(0);    // Get the first column.
    string d = s.GetField(1); // Get second column.
	cout << "key " << i << " name " << d << endl;
  }
}
