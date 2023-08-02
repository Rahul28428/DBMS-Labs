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
    char tableName4[256] = "Medical record";
    char query4[512];
    snprintf(query4, 512, "CREATE TABLE `%s` (`Record-id` int NOT NULL PRIMARY KEY, `Date_of_examination` int NOT NULL PRIMARY KEY, `Problem` varchar(255));",tableName4);
    snprintf(query4, 512, "INSERT INTO `%s` (Record-id, Date_of_examination, Problem) VALUES (1, '2022-08-20', 'Pain in legs');",tableName4);
    snprintf(query4, 512, "INSERT INTO `%s` (Record-id, Date_of_examination, Problem) VALUES (2, '2022-08-19', 'Rashes');",tableName4);
    snprintf(query4, 512, "INSERT INTO `%s` (Record-id, Date_of_examination, Problem) VALUES (3, '2022-08-18', 'Weak legs');",tableName4);
    int createTableStatus = mysql_query(conn, query4);
    if (createTableStatus != 0) 
    {
        cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
    }
    //int a = display();
    return 0;
}