#include <iostream>
#include <windows.h>
#include <mysql.h>
 
using namespace std;
 
MYSQL *conn;
 
int main(){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }
 
    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "dbms_demo_vageesh_2", "DBMSDemo_vageesh_2", "dbms_demo_vageesh_2", 3306, NULL, 0)){
        cout<<"Connected Successfully!"<<endl;
        char tableName[256] = "sales";
        char query[256],query1[256];
        snprintf(query, 256, "CREATE TABLE `%s` (`salesman_id` int NOT NULL PRIMARY KEY,`name` varchar(255),`adrress_city` varchar(255), `coverage_city` varchar(255),`commission` int,`date of employ` Date,`date of release` Date);", tableName);
 
        int createTableStatus = mysql_query(conn, query);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }
 
        snprintf(query1,256,"INSERT INTO `sales_table` (`salesman_id`, `name`, `address_city`, `coverage_city`, `commission`,`date of employ`,`date of release`) VALUES ('1', 'Chakshu', 'Mumbai', 'Jodhpur', '1000','2021-05-12','2022-02-22'), ('2', 'Vageesh', 'Haryana', 'Delhi', '2000','2022-06-19',NULL), ('3', 'Rahul', 'Amravati', 'Nagpur', '1500','2020-07-15',NULL), ('4', 'Rushil', 'Thane', 'Jodhpur', '1000','2020-08-18',NULL), ('5', 'Kaustubh', 'Goa', 'Delhi', '1000','2019-02-15','2022-05-15'), ('6', 'Aman', 'Lucknow', 'Mumbai', '500','2018-01-23','2021-06-16');");
        int insertTableStatus = mysql_query(conn, query1);
        if (insertTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }
 
    } else {
        cout<<"Error while connecting!"<<endl;
    }
 
    return 0;
