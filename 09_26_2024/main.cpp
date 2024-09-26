#include <sqlite3.h>
#include <iostream>
#include <limits>
#include <string>

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
    sqlite3_close(saleCo);
    return 0;
}