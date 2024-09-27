#include <sqlite3.h>
#include <iostream>
#include <limits>
#include <string>

void resetStream();
void makeSale(sqlite3 *);
int startTransaction(sqlite3 *);
int commit(sqlite3 *);
int rollback(sqlite3 *);
int pickCustomer(sqlite3 *);
int addCustomer(sqlite3 *);

int main()
{
    sqlite3 *saleCo;
    int returnCode;
    returnCode = sqlite3_open_v2("SaleCo.db", &saleCo, SQLITE_OPEN_READWRITE, NULL);
    if (returnCode != SQLITE_OK)
    {
        std::cout << "Error opening database: " << sqlite3_errmsg(saleCo) << std::endl;
        sqlite3_close(saleCo);
        return 0;
    }
    makeSale(saleCo);
    sqlite3_close(saleCo);
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
•   You must write a new customer invoice.
    //•   pick customer or
    //    add new
    •   create an invoice using the cus_code
    •   add products by adding lines using the inv_number
•   You must reduce the quantity on hand in the product’s inventory for each product.
•   You must update the customer balance.
•   You must update the payments if necessary.
*/
void makeSale(sqlite3 *db)
{
    int rc = startTransaction(db);
    if (rc != SQLITE_OK)
    {
        std::cout << "Unable to start transaction: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    int cusCode = pickCustomer(db);

    rollback(db);
}

int startTransaction(sqlite3 *db)
{
    std::string query = "begin transaction";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error in start transaction: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    return SQLITE_OK;
}

int commit(sqlite3 *db)
{
    std::string query = "commit";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - committing transaction: " << sqlite3_errmsg(db) << std::endl;
        rollback(db);
        return rc;
    }
    return SQLITE_OK;
}

int rollback(sqlite3 *db)
{
    std::string query = "rollback";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "There was an error - rolling back the transaction: " << sqlite3_errmsg(db) << std::endl;
        // rollback(db);
        return rc;
    }
    return SQLITE_OK;
}

// choose an existing customer or kick of the add process for a new one
// returns the cus_code
int pickCustomer(sqlite3 *db)
{
    std::string query = "select cus_code, cus_lname || ', ' || cus_fname as name\n";
    query += "from customer\n";
    sqlite3_stmt *result;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &result, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(result);
        std::cout << "There was an error with the customer query: " << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return -1;
    }
    int i, choice;
    std::cout << "Please choose a customer:" << std::endl;
    i = 1;
    rc = sqlite3_step(result);
    while (rc == SQLITE_ROW)
    {
        std::cout << i << ". " << sqlite3_column_text(result, 0);
        std::cout << " - " << sqlite3_column_text(result, 1);
        std::cout << std::endl;
        i++;
        rc = sqlite3_step(result);
    }
    std::cout << i << ". " << "Add New Customer" << std::endl;
    std::cin >> choice;
    while (!std::cin || choice < 1 || choice > i)
    {
        if (!std::cin)
            resetStream();
        std::cout << "That is not a valid choice! Try again!" << std::endl;
        std::cin >> choice;
    }
    if (choice == i)
    {
        sqlite3_finalize(result);
        return addCustomer(db);
    }
    sqlite3_reset(result);
    for (int j = 0; j < choice; j++)
    {
        sqlite3_step(result);
    }
    int cusCode = sqlite3_column_int(result, 0);
    sqlite3_finalize(result);
    return cusCode;
}
// adds a new customer and returns their customer code.
int addCustomer(sqlite3 *db)
{
    std::string query = "insert into customer(cus_lname, cus_fname, cus_phone)\n";
    query += "values (@lname, @fname, @phone)";
    std::string fname, lname, phone;
    std::cout << "Enter the customer last name: ";
    std::getline(std::cin >> std::ws, lname);
    std::cout << "Enter the customer first name: ";
    std::getline(std::cin >> std::ws, fname);
    std::cout << "Enter the customer phone number: ";
    std::getline(std::cin >> std::ws, phone);
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &res, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(res);
        std::cout << "unable to insert customer." << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return -1;
    }
    rc = sqlite3_bind_text(res, sqlite3_bind_parameter_index(res, "@lname"), lname.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(res);
        std::cout << "unable to insert customer." << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return -1;
    }
    rc = sqlite3_bind_text(res, sqlite3_bind_parameter_index(res, "@fname"), fname.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(res);
        std::cout << "unable to insert customer." << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return -1;
    }
    rc = sqlite3_bind_text(res, sqlite3_bind_parameter_index(res, "@phone"), phone.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(res);
        std::cout << "unable to insert customer." << sqlite3_errmsg(db) << std::endl;
        std::cout << query << std::endl;
        return -1;
    }
    sqlite3_step(res);
    int cusCode = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(res);

    return cusCode;
}