#include "sqdb.h"
#include <iostream>

using namespace std;
string name;
string channel_id;
string sender_id;
char quer;
int main()
{

name = "zimmer4";
channel_id = "44";
sender_id = "1001";
sqdb::Db db("/var/www/liteadmin/weather");
try {
sqdb::Statement i = db.Query("insert into location (name, sender_id, channel_id) values (?, ?, ?)");
i.Bind(1, "zimmer4");
i.Bind(2, "1001");
i.Bind(3, "77");
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
