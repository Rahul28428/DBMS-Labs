//Command to Compile: g++ demo.cpp -o demo.exe -lmysql
#include <iostream>
#include <windows.h>
#include <mysql.h>
using namespace std;
MYSQL *conn;

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) 
    {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }
// mysql_real_connect(Connection Instance, Username, Password,Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "vageesh","1234", "lab1", 3306, NULL, 0)) 
    {
        
        cout<<"Connected Successfully!"<<endl;
    } 
    else 
    {
        cout<<"Error while connecting!"<<endl;
    }
    char tableName2[256] = "Hospital";
    char query2[512];
    snprintf(query2, 512, "CREATE TABLE `%s` (`Hosp-id` int NOT NULL PRIMARY KEY, `Hos-Name` varchar(255), `HCity` varchar(255), `HAddress` varchar(255));",tableName2);
    snprintf(query2, 512, "INSERT INTO `%s` (Hosp-id, Hos-Name, HCity, HAddress) VALUES (1, 'Appolo', 'Delhi', 'Sarita Vihar');",tableName2);
    snprintf(query2, 512, "INSERT INTO `%s` (Hosp-id, Hos-Name, HCity, HAddress) VALUES (2, 'AIIMS', 'Jodhpur', 'Marudhart idustrial Area');",tableName2);
    snprintf(query2, 512, "INSERT INTO `%s` (Hosp-id, Hos-Name, HCity, HAddress) VALUES (3, 'Goel', 'Jodhpur', 'Sradarpura');",tableName2);
    int createTableStatus = mysql_query(conn, query2);
    if (createTableStatus != 0) 
    {
        cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
    }
    //int a = display();
    return 0;
}