//Command to Compile: g++ demo.cpp -o demo.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>
// #include <float.h>

using namespace std;

MYSQL *conn;
// MYSQL *conn;
//  MYSQL_RES res; /* holds the result set */
//     MYSQL_ROW row;


int main()
{

    conn = mysql_init(NULL);

    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password,
    // Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "chakshu123", "chakshu12345","lab2_q4", 3306, NULL, 0)) {

        cout<<"Connected Successfully!"<<endl;
        // char query[256];
        // snprintf(query,256,"DROP TABLE Report");
        char tableName[256] = "lab2_og";
        char query[256],query1[100000],query2[100000],query3[100000];

        snprintf(query, 256, "CREATE TABLE `lab2_q4`.`lab2_og` (`Date` DATE NOT NULL , `Grocery_Name` VARCHAR(255) NOT NULL , `No_of_Items` INT NOT NULL DEFAULT '1' , `Necessity` VARCHAR(255) NOT NULL DEFAULT 'Need' , `Cost` INT NOT NULL , PRIMARY KEY (`Date`, `Grocery_Name`));",tableName);
        
        int createTableStatus = mysql_query(conn, query);


        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }
        snprintf(query1,100000,"INSERT INTO lab2_og(`Date`,`Grocery_Name`,`No_of_Items`,`Necessity`,`cost`) VALUES ('2022-07-02','Apple',10,'Need',30),('2022-07-02','Orange',0,'do not',20),('2022-07-02','Cauliflower',3,'may',30),('2022-07-12','Tomato',4,'Need',25),('2022-08-03','Apple',8,'Need',30),('2022-08-03','Tomato',4,'Need',25),('2022-08-03','Spinach',3,'may',30),('2022-08-03','Egplant',2,'do not',40),('2022-08-15','Banana',6,'Need',5),('2022-08-25','Tomato',6,'Need',25),('2022-09-04','Apple',8,'Need',30),('2022-09-04','Tomato',4,'Need',25),('2022-09-04','Spinach',3,'may',30),('2022-09-04','Orange',2,'do not',20),('2022-09-04','Cauliflower',3,'Need',30),('2022-09-11','Onion',5,'Need',50),('2022-09-16','Grapes',3,'may',40),('2022-09-17','Apple',4,'do not',30)");       
        int insertTableStatus = mysql_query(conn, query1);
        //insertTableStatus = mysql_query(conn, query2);
        //insertTableStatus = mysql_query(conn, query3);
        if (insertTableStatus != 0) {
            cout<<"Error while inserting in table: "<<mysql_error(conn)<<endl;

        }

    } 
    else {
        cout<<"Error while connecting!"<<endl;
    }

    
    return 0;
}