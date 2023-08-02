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
    char tableName1[256] = "Patient";
    char query1[512];
    snprintf(query1, 512, "CREATE TABLE `%s` (`Pat-id` int NOT NULL PRIMARY KEY, `Pname` varchar(255), `Pdiagnosis` varchar(255), `Paddress` varchar(255));",tableName1);
    snprintf(query1, 512, "INSERT INTO `%s` (Pat-id, Pname, Pdiagnosis, Paddress) VALUES (1, 'Chakshu', 'Rickets', 'Mumbai');",tableName1);
    snprintf(query1, 512, "INSERT INTO `%s` (Pat-id, Pname, Pdiagnosis, Paddress) VALUES (2, 'Rahul', 'Rabies', 'Amravati');",tableName1);
    snprintf(query1, 512, "INSERT INTO `%s` (Pat-id, Pname, Pdiagnosis, Paddress) VALUES (3, 'Vageesh', 'Polio', 'Rewari');",tableName1);
    int createTableStatus = mysql_query(conn, query1);
    if (createTableStatus != 0) 
    {
        cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
    }
    //int a = display();
    return 0;
}