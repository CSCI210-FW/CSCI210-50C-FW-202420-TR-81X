#include <iostream>
#include <string>
#include <sqlite3.h>
#include <limits>
#include <iomanip>

void viewAssignmentsByProject(sqlite3 *);
void resetStream();
int genericRowCallback(void *, int, char **, char **);

int main()
{
    sqlite3 *db;
    int rc = sqlite3_open_v2("ConstructCo.db", &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }
    else
    {
        std::cout << "Database opened successfully." << std::endl;
    }
    std::string query = "select * from employee";
    rc = sqlite3_exec(db, query.c_str(), genericRowCallback, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - select callback: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
    }

    query = "delete from employee where emp_lname = 'Brown' and emp_fname = 'Charlie'";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {

        std::cout << "There was an error with deleting charlie brown: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
    }

    std::string lname, fname, mi;
    int job, years;
    char formatDate[80];
    time_t currentDate = time(NULL);
    strftime(formatDate, 80, "%F", localtime(&currentDate));
    std::string hiredate(formatDate);
    lname = "Brown";
    fname = "Charlie";
    job = 504;
    years = 0;
    query = "insert into employee(emp_lname, emp_fname, emp_hiredate, job_code, emp_years)\n";
    query += "values ('";
    query += lname + "', '";
    query += fname + "', '";
    query += hiredate + "', ";
    query += std::to_string(job) + ", ";
    query += std::to_string(years) + ");";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {

        std::cout << "There was an error with adding charlie brown: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
    }
    else
    {
        int emp_num = sqlite3_last_insert_rowid(db);
        std::cout << fname << " " << lname << " inserted into the database as employee number " << emp_num << std::endl;
    }
    viewAssignmentsByProject(db);
    sqlite3_close(db);
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void viewAssignmentsByProject(sqlite3 *db)
{
    std::string query;
    sqlite3_stmt *result;
    query = "select proj_num, proj_name from project"; // proj_num is 0 proj_name is 1
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &result, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(result);
        std::cout << "There was an error with the project query: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return;
    }
    int i = 1;
    int choice;
    std::cout << std::left;
    std::cout << "Please choose the project: " << std::endl;
    rc = sqlite3_step(result);
    while (rc == SQLITE_ROW)
    {
        std::cout << i << ". " << sqlite3_column_text(result, 0);
        std::cout << " - " << sqlite3_column_text(result, 1);
        std::cout << std::endl;
        i++;
        rc = sqlite3_step(result);
    }
    std::cin >> choice;
    while (!std::cin || choice < 1 || choice >= i)
    {
        if (!std::cin)
            resetStream();
        std::cout << "That is not a valid choice! Try again!" << std::endl;
        std::cin >> choice;
    }
    sqlite3_reset(result);
    for (int j = 0; j < choice; j++)
    {
        sqlite3_step(result);
    }
    int proj_num = sqlite3_column_int(result, 0);
    sqlite3_finalize(result);
    query = "select *\n";
    query += "from assignment join employee on assignment.emp_num = employee.emp_num\n";
    query += "where proj_num = " + std::to_string(proj_num);
    // query += " group by proj_num";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &result, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(result);
        std::cout << "There was an error with the assignment query: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return;
    }
    int columnCount = sqlite3_column_count(result);
    for (int i = 0; i < columnCount; i++)
    {
        std::cout << std::setw(15) << sqlite3_column_name(result, i);
    }
    std::cout << std::endl;
    for (rc = sqlite3_step(result); rc == SQLITE_ROW; rc = sqlite3_step(result))
    {

        for (int i = 0; i < columnCount; i++)
        {
            if (sqlite3_column_type(result, i) != SQLITE_NULL)
            {
                std::cout << std::setw(15) << sqlite3_column_text(result, i);
            }
            else
                std::cout << std::setw(15) << " ";
        }
        std::cout << std::endl;
    }
    sqlite3_finalize(result);
}

int genericRowCallback(void *extData, int numCols, char **values, char **colName)
{
    static int rowCount = 0;
    if (rowCount == 0)
    {
        for (int i = 0; i < numCols; i++)
        {
            std::cout << std::setw(15) << colName[i];
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < numCols; i++)
    {
        std::cout << std::setw(15);
        // std::cout << colName[i] << ": ";
        if (values[i] != NULL)
            std::cout << values[i];
        else
            std::cout << " ";
        // std::cout << std::endl;
    }
    std::cout << std::endl;
    rowCount++;
    return SQLITE_OK;
}