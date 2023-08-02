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
    char tableName3[256] = "Doctor";
    char query3[512];
    snprintf(query3, 512, "CREATE TABLE `%s` (`Doc-id` int NOT NULL PRIMARY KEY, `DName` varchar(255), `Qualification` varchar(255), `Salary` int NOT NULL PRIMARY KEY);",tableName3);
    snprintf(query3, 512, "INSERT INTO `%s` (Doc-id, DName, Qualification, Salary) VALUES (1, 'Devi', 'MMBS', 1000002);",tableName3);
    snprintf(query3, 512, "INSERT INTO `%s` (Doc-id, DName, Qualification, Salary) VALUES (2, 'Ribhav', 'MD', 100000);",tableName3);
    snprintf(query2, 512, "INSERT INTO `%s` (Doc-id, DName, Qualification, Salary) VALUES (3, 'Rushil', 'BMS', 100000);",tableName3);
    int createTableStatus = mysql_query(conn, query3);
    if (createTableStatus != 0) 
    {
        cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
    }
    //int a = display();
    return 0;
}