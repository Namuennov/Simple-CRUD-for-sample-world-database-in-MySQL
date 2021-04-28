//Jakub Foryœ   Informatyka Techniczna   grupa 1
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <mysql.h>

#include "jdbc/mysql_connection.h"

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

#define WAIT 2000

using namespace std;

string getCountryCode(sql::Driver* driver, sql::Connection* con)
{
    string s = " ";
    sql::Statement* stmt;
    sql::ResultSet* res;
    cout << "\nYou have to add uniqe 3-characters country code\nType country code to check whether code can be used or not";

    while (1)
    {
        cout << "\nEnter your code: ";
        cin >> s;
        if (s.length() > 3) s = s.erase(0, 3);
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM country WHERE Code LIKE \"" + s + "\"");
        if (res->rowsCount() == 0)
        {
            delete stmt;
            delete res;
            return s;
        }
        cout << "\nThis code is used. Choose another one";
    }
}

string getCountryCode2(sql::Driver* driver, sql::Connection* con)
{
    string s = " ";
    sql::Statement* stmt;
    sql::ResultSet* res;
    cout << "\nYou have to add uniqe 2-characters second country code\nType country code to check whether code can be used or not";

    while (1)
    {
        cout << "\nEnter your code: ";
        cin >> s;
        if (s.length() > 2) s = s.erase(0, 2);
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM country WHERE Code2 LIKE \"" + s + "\"");
        if (res->rowsCount() == 0)
        {
            delete stmt;
            delete res;
            return s;
        }
        cout << "\nThis code is used. Choose another one";
    }
}

bool Cco(sql::Driver* driver, sql::Connection* con)
{
        string add = " ";
        int n = 0;
        float f = 0.;

        sql::PreparedStatement* prep;
        prep = con->prepareStatement("INSERT INTO country VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        system("cls");
        cout << "=CREATING NEW COUNTRY=\nName: ";
        cin >> add;
        prep->setString(2, add);

        cout << "Continent (enter appropriate number): 1 - Asia, 2 - Europe, 3 - North America, 4 - Africa, 5 - Oceania, 6 - Antarctica, 7 - South America\n";
        cin >> n;
        switch (n)
        {
        case 2:
            add = "Europe";
            break;
        case 3:
            add = "North America";
            break;
        case 4:
            add = "Africa";
            break;
        case 5:
            add = "Oceania";
            break;
        case 6:
            add = "Antarctica";
            break;
        case 7:
            add = "South America";
            break;
        default:
            add = "Asia";
        }
        prep->setString(3, add);

        cout << "Region: ";
        cin >> add;
        prep->setString(4, add);

        cout << "Surface area (float 10,2): ";
        cin >> f;
        prep->setDouble(5, f);

        cout << "Independence year: ";
        cin >> n;
        prep->setInt(6, n);

        cout << "Population: ";
        cin >> n;
        prep->setInt(7, n);

        cout << "Life expectancy (float 3,1): ";
        cin >> f;
        prep->setDouble(8, f);

        cout << "GNP (float 10,2): ";
        cin >> f;
        prep->setDouble(9, f);

        cout << "GNPOld (float 10,2): ";
        cin >> f;
        prep->setDouble(10, f);

        cout << "Local name: ";
        cin >> add;
        prep->setString(11, add);

        cout << "Government form: ";
        cin >> add;
        prep->setString(12, add);

        cout << "Head of state: ";
        cin >> add;
        prep->setString(13, add);

        cout << "Capital (int): ";
        cin >> n;
        prep->setInt(14, n);

        add = getCountryCode(driver, con);
        prep->setString(1, add);

        add = getCountryCode2(driver, con);
        prep->setString(15, add);

        cout << "\nConfirm adding country: 1 - Yes, 2 - No\nYour choice: ";
        cin >> n;
        switch (n)
        {
        case 2:
            break;
        default:
            prep->execute();
        }
        delete prep;
        return true;
}

string getCountry_NameCode(sql::Driver* driver, sql::Connection* con)
{
    string s = " ";
    int a = 0;
    sql::Statement* stmt;
    sql::ResultSet* res;
    cout << "\nChoose country\nType country name to check whether that country is in database or not";

    while (1)
    {
        cout << "\nEnter country name: ";
        cin >> s;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT Code, Name FROM country WHERE Name LIKE \"%" + s + "%\"");
        
        a = res->rowsCount();
        switch (a)
        {
        case 0:
            cout << "\nThere is no such country in database";
            break;
        case 1:
            res->next();
            s = res->getString("Code");
            delete stmt;
            delete res;
            return s;
        default:
            cout << "\nThere are many countries in database with entered characters: ";
            while (res->next()) cout << res->getString("Name") << ", ";
            cout << "\n\nenter more or different characters to choose right country";
        }
    }
}

string getCity_NameID(sql::Driver* driver, sql::Connection* con)
{
    string s = " ";
    int a = 0;
    sql::Statement* stmt;
    sql::ResultSet* res;
    cout << "\nChoose city\nType country name to check whether that city is in database or not";

    while (1)
    {
        cout << "\nEnter city name: ";
        cin >> s;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT ID, Name FROM city WHERE Name LIKE \"%" + s + "%\"");

        a = res->rowsCount();
        switch (a)
        {
        case 0:
            cout << "\nThere is no such city in database";
            break;
        case 1:
            res->next();
            s = res->getString("ID");
            delete stmt;
            delete res;
            return s;
        default:
            cout << "\nThere are many cities in database with entered characters: ";
            while (res->next()) cout << res->getString("Name") << ", ";
            cout << "\n\nenter more or different characters to choose right city";
        }
    }
    return 0;
}

bool Cci(sql::Driver* driver, sql::Connection* con)
{
    string add = " ";
    int n = 0;

    sql::PreparedStatement* prep;
    prep = con->prepareStatement("INSERT INTO city VALUES(NULL, ?, ?, ?, ?)");
    system("cls");
    cout << "=CREATING NEW CITY=\nName: ";
    cin >> add;
    prep->setString(1, add);

    add = getCountry_NameCode(driver, con);
    prep->setString(2, add);

    cout << "District: ";
    cin >> add;
    prep->setString(3, add);

    cout << "Population: ";
    cin >> n;
    prep->setInt(4, n);

    cout << "\nConfirm adding city: 1 - Yes, 2 - No\nYour choice: ";
    cin >> n;
    switch (n)
    {
    case 2:
        break;
    default:
        prep->execute();
    }
    delete prep;
    return true;
}

bool Ccl(sql::Driver* driver, sql::Connection* con)
{
    string add = " ";
    int n = 0;
    float f = 0.;

    sql::PreparedStatement* prep;
    prep = con->prepareStatement("INSERT INTO countrylanguage VALUES(?, ?, ?, ?)");
    system("cls");
    cout << "=CREATING NEW COUNTRY LANGUAGE=\nLanguage: ";
    cin >> add;
    prep->setString(2, add);

    add = getCountry_NameCode(driver, con);
    prep->setString(1, add);

    cout << "Is this language official? 1 - YES, 2 - NO\nYour choice: ";
    cin >> n;
    switch (n)
    {
    case 1:
        prep->setString(3, "T");
        break;
    default:
        prep->setString(3, "F");
    }

    cout << "Percentage (float 4,1): ";
    cin >> f;
    prep->setDouble(4, f);

    cout << "\nConfirm adding country language: 1 - Yes, 2 - No\nYour choice: ";
    cin >> n;
    switch (n)
    {
    case 2:
        break;
    default:
        prep->execute();
    }
    delete prep;
    return true;
}

void Create(sql::Driver* driver, sql::Connection* con)
{
    int c;
    bool b = true;
    while (b == true)
    {
        system("cls");
        cout << "=CREATING RECORDS: SELECT TABLE=\n1 - country\n2 - city\n3 - countrylanguage\n4 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            b = Cco(driver, con);
            break;
        case 2:
            b = Cci(driver, con);
            break;
        case 3:
            b = Ccl(driver, con);
            break;
        case 4:
            return;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    };
}

bool Rco(sql::Driver* driver, sql::Connection* con)
{
    int c;
    string s;

    while (1)
    {
        system("cls");
        cout << "=SELECT OPERATION=\n1 - search by name\n2 - see all records in alphabetical order\n3 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            system("cls");
            cout << "Enter name of the country you are looking for: ";
            cin >> s;
            sql::Statement* stmt1;
            sql::ResultSet* res1;
            stmt1 = con->createStatement();
            res1 = stmt1->executeQuery("SELECT * FROM country WHERE Name LIKE \"%" + s + "%\"");
            system("cls");
            while (res1->next()) {
                cout << "Name: " << res1->getString("Name") << "\n";
                cout << "Continent: " << res1->getString("Continent") << "\n";
                cout << "Region: " << res1->getString("Region") << "\n";
                cout << "Surface Area: " << res1->getString("SurfaceArea") << "\n";
                cout << "Independence Year: " << res1->getString("IndepYear") << "\n";
                cout << "Population: " << res1->getString("Population") << "\n";
                cout << "Life Expectancy: " << res1->getString("LifeExpectancy") << "\n";
                cout << "GNP: " << res1->getString("GNP") << "\n";
                cout << "GNPOld: " << res1->getString("GNPOld") << "\n";
                cout << "Local Name: " << res1->getString("LocalName") << "\n";
                cout << "Government Form: " << res1->getString("GovernmentForm") << "\n";
                cout << "Head Of State: " << res1->getString("HeadOfState") << "\n";
                cout << "Capital: " << res1->getString("Capital") << "\n\n";
            }
            delete res1;
            delete stmt1;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;

        case 2:
            sql::Statement * stmt2;
            sql::ResultSet* res2;
            stmt2 = con->createStatement();
            res2 = stmt2->executeQuery("SELECT * FROM country ORDER BY Name ASC");
            system("cls");
            while (res2->next()) {
                cout << "Name: " << res2->getString("Name") << "\n";
                cout << "Continent: " << res2->getString("Continent") << "\n";
                cout << "Region: " << res2->getString("Region") << "\n";
                cout << "Surface Area: " << res2->getString("SurfaceArea") << "\n";
                cout << "Independence Year: " << res2->getString("IndepYear") << "\n";
                cout << "Population: " << res2->getString("Population") << "\n";
                cout << "Life Expectancy: " << res2->getString("LifeExpectancy") << "\n";
                cout << "GNP: " << res2->getString("GNP") << "\n";
                cout << "GNPOld: " << res2->getString("GNPOld") << "\n";
                cout << "Local Name: " << res2->getString("LocalName") << "\n";
                cout << "Government Form: " << res2->getString("GovernmentForm") << "\n";
                cout << "Head Of State: " << res2->getString("HeadOfState") << "\n";
                cout << "Capital: " << res2->getString("Capital") << "\n\n";
            }

            delete res2;
            delete stmt2;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;
        case 3:
            return true;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

bool Rci(sql::Driver* driver, sql::Connection* con)
{
    int c;
    string s;

    while (1)
    {
        system("cls");
        cout << "=SELECT OPERATION=\n1 - search by name\n2 - see all records in alphabetical order\n3 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            system("cls");
            cout << "Enter name of the city you are looking for: ";
            cin >> s;
            sql::Statement* stmt1;
            sql::ResultSet* res1;
            stmt1 = con->createStatement();
            res1 = stmt1->executeQuery("SELECT city.Name, country.Name, city.District, city.Population FROM city INNER JOIN country ON city.CountryCode = country.Code WHERE city.Name LIKE \"%" + s + "%\" ORDER BY city.Name");

            system("cls");
            while (res1->next()) {
                cout << "Name: " << res1->getString(1) << "\n";
                cout << "Country: " << res1->getString(2) << "\n";
                cout << "District: " << res1->getString(3) << "\n";
                cout << "Population: " << res1->getString(4) << "\n\n";
            }
            delete res1;
            delete stmt1;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;

        case 2:
            sql::Statement * stmt2;
            sql::ResultSet* res2;
            stmt2 = con->createStatement();
            res2 = stmt2->executeQuery("SELECT city.Name, country.Name, city.District, city.Population FROM city INNER JOIN country ON city.CountryCode = country.Code ORDER BY city.Name");

            system("cls");
            while (res2->next()) {
                cout << "Name: " << res2->getString(1) << "\n";
                cout << "Country: " << res2->getString(2) << "\n";
                cout << "District: " << res2->getString(3) << "\n";
                cout << "Population: " << res2->getString(4) << "\n\n";
            }
            delete res2;
            delete stmt2;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;
        case 3:
            return true;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

bool Rcl(sql::Driver* driver, sql::Connection* con)
{
    int c;
    string s;

    while (1)
    {
        system("cls");
        cout << "=SELECT OPERATION=\n1 - search by name\n2 - see all records in alphabetical order\n3 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            system("cls");
            cout << "Enter name of the country to display its languages: ";
            cin >> s;
            sql::Statement* stmt1;
            sql::ResultSet* res1;
            stmt1 = con->createStatement();
            res1 = stmt1->executeQuery("SELECT countrylanguage.Language, country.Name, countrylanguage.IsOfficial, countrylanguage.Percentage FROM countrylanguage INNER JOIN country ON countrylanguage.CountryCode = country.Code WHERE country.Name LIKE \"%" + s + "%\" ORDER BY country.Name");

            system("cls");
            while (res1->next()) {
                cout << "Country: " << res1->getString(2) << "\n";
                cout << "Language: " << res1->getString(1) << "\n";
                cout << "Is official? " << res1->getString(3) << "\n";
                cout << "Percentage: " << res1->getString(4) << "\n\n";
            }
            delete res1;
            delete stmt1;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;

        case 2:
            sql::Statement * stmt2;
            sql::ResultSet* res2;
            stmt2 = con->createStatement();
            res2 = stmt2->executeQuery("SELECT countrylanguage.Language, country.Name, countrylanguage.IsOfficial, countrylanguage.Percentage FROM countrylanguage INNER JOIN country ON countrylanguage.CountryCode = country.Code ORDER BY country.Name");

            system("cls");
            while (res2->next()) {
                cout << "Country: " << res2->getString(2) << "\n";
                cout << "Language: " << res2->getString(1) << "\n";
                cout << "Is official? " << res2->getString(3) << "\n";
                cout << "Percentage: " << res2->getString(4) << "\n\n";
            }
            delete res2;
            delete stmt2;

            cout << "\n\n\nEnter anything to return to main menu: ";
            cin >> s;

            return false;
        case 3:
            return true;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

void Read(sql::Driver* driver, sql::Connection* con)
{
    int c;
    bool b = true;
    while (b == true)
    {
        system("cls");
        cout << "=READING RECORDS: SELECT TABLE=\n1 - country\n2 - city\n3 - countrylanguage\n4 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            b = Rco(driver, con);
            break;
        case 2:
            b = Rci(driver, con);
            break;
        case 3:
            b = Rcl(driver, con);
            break;
        case 4:
            return;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

bool Uco(sql::Driver* driver, sql::Connection* con)
{
    string country = " ";
    string s = " ";
    int n, m = 0;
    float f = 0.;

    system("cls");
    cout << "=UPDATING EXISTING COUNTRY=\n";
    country = getCountry_NameCode(driver, con);

    sql::PreparedStatement* prep = con->prepareStatement("SELECT \"nothing\"");
    sql::Statement* stmt1;
    sql::ResultSet* res1;
    stmt1 = con->createStatement();

    while (1)
    {
        res1 = stmt1->executeQuery("SELECT * FROM country WHERE Code = \"" + country + "\"");
        res1->next();

        system("cls");
        cout << "=UPDATING EXISTING COUNTRY=\n\nCurrent record parametres:\n";

        cout << "Name: " << res1->getString("Name") << "\n";
        cout << "Continent: " << res1->getString("Continent") << "\n";
        cout << "Region: " << res1->getString("Region") << "\n";
        cout << "Surface Area: " << res1->getString("SurfaceArea") << "\n";
        cout << "Independence Year: " << res1->getString("IndepYear") << "\n";
        cout << "Population: " << res1->getString("Population") << "\n";
        cout << "Life Expectancy: " << res1->getString("LifeExpectancy") << "\n";
        cout << "GNP: " << res1->getString("GNP") << "\n";
        cout << "GNPOld: " << res1->getString("GNPOld") << "\n";
        cout << "Local Name: " << res1->getString("LocalName") << "\n";
        cout << "Government Form: " << res1->getString("GovernmentForm") << "\n";
        cout << "Head Of State: " << res1->getString("HeadOfState") << "\n";
        cout << "Capital: " << res1->getString("Capital") << "\n\n";

        cout << "\nWhat do you want to change?\n1 - Name\n2 - Continent\n3 - Region\n4 - Surface area\n5 - Independence year\n6 - Population\n7 - Life expectancy\n8 - GNP\n9 - GNPOld\n10 - Local name\n11 - Government form\n12 - Head of state\n13 - Capital\n14 - return to main menu\n\nYour choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "\nEnter new name: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE country SET Name = \"" + s + "\"WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 2:
            cout << "Select continent (enter appropriate number): 1 - Asia, 2 - Europe, 3 - North America, 4 - Africa, 5 - Oceania, 6 - Antarctica, 7 - South America\n";
            cin >> m;
            switch (m)
            {
            case 2:
                s = "Europe";
                break;
            case 3:
                s = "North America";
                break;
            case 4:
                s = "Africa";
                break;
            case 5:
                s = "Oceania";
                break;
            case 6:
                s = "Antarctica";
                break;
            case 7:
                s = "South America";
                break;
            default:
                s = "Asia";
            }
            prep = con->prepareStatement("UPDATE country SET Continent = \"" + s + "\" WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 3:
            cout << "\nEnter new region: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE country SET Region = \"" + s + "\" WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 4:
            cout << "\nEnter new surface area (float 10,2): ";
            cin >> f;
            prep = con->prepareStatement("UPDATE country SET SurfaceArea = ? WHERE Code = \"" + country + "\"");
            prep->setDouble(1, f);
            prep->execute();
            break;
        case 5:
            cout << "\nEnter new independence year: ";
            cin >> m;
            prep = con->prepareStatement("UPDATE country SET IndepYear = ? WHERE Code = \"" + country + "\"");
            prep->setInt(1, m);
            prep->execute();
            break;
        case 6:
            cout << "\nEnter new population: ";
            cin >> m;
            prep = con->prepareStatement("UPDATE country SET Population = ? WHERE Code = \"" + country + "\"");
            prep->setInt(1, m);
            prep->execute();
            break;
        case 7:
            cout << "\nEnter new life expectancy (float 3,1): ";
            cin >> f;
            prep = con->prepareStatement("UPDATE country SET LifeExpectancy = ? WHERE Code = \"" + country + "\"");
            prep->setDouble(1, f);
            prep->execute();
            break;
        case 8:
            cout << "\nEnter new GNP (float 10,2): ";
            cin >> f;
            prep = con->prepareStatement("UPDATE country SET GNP = ? WHERE Code = \"" + country + "\"");
            prep->setDouble(1, f);
            prep->execute();
            break;
        case 9:
            cout << "\nEnter new GNPOld (float 10,2): ";
            cin >> f;
            prep = con->prepareStatement("UPDATE country SET GNPOld = ? WHERE Code = \"" + country + "\"");
            prep->setDouble(1, f);
            prep->execute();
            break;
        case 10:
            cout << "\nEnter new local name: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE country SET LocalName = \"" + s + "\" WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 11:
            cout << "\nEnter new government form: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE country SET GovernmentForm = \"" + s + "\" WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 12:
            cout << "\nEnter new head of state: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE country SET HeadOfState = \"" + s + "\" WHERE Code = \"" + country + "\"");
            prep->execute();
            break;
        case 13:
            cout << "\nEnter new capital (int): ";
            cin >> m;
            prep = con->prepareStatement("UPDATE country SET Capital = ? WHERE Code = \"" + country + "\"");
            prep->setInt(1, m);
            prep->execute();
            break;
        case 14:
            delete stmt1;
            delete res1;
            delete prep;
            return false;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

bool Uci(sql::Driver* driver, sql::Connection* con)
{
    string city = " ";
    string s = " ";
    int n, m = 0;

    system("cls");
    cout << "=UPDATING EXISTING CITY=\n";
    city = getCity_NameID(driver, con);

    sql::PreparedStatement* prep = con->prepareStatement("SELECT \"nothing\"");
    sql::PreparedStatement* prep1 = con->prepareStatement("SELECT city.Name, country.Name, city.District, city.Population FROM city INNER JOIN country ON city.CountryCode = country.Code WHERE city.ID = " + city);
    sql::ResultSet* res1;

    while (1)
    {
        res1 = prep1->executeQuery();
        res1->next();

        system("cls");
        cout << "=UPDATING EXISTING CITY=\n\nCurrent record parametres:\n";

        cout << "Name: " << res1->getString(1) << "\n";
        cout << "Country: " << res1->getString(2) << "\n";
        cout << "District: " << res1->getString(3) << "\n";
        cout << "Population: " << res1->getString(4) << "\n\n";

        cout << "\nWhat do you want to change?\n1 - Name\n2 - Country\n3 - District\n4 - Population\n5 - return to main menu\n\nYour choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "\nEnter new name: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE city SET Name = \"" + s + "\"WHERE ID = " + city);
            prep->execute();
            break;
        case 2:
            s = getCountry_NameCode(driver, con);
            prep = con->prepareStatement("UPDATE city SET CountryCode = \"" + s + "\"WHERE ID = " + city);
            prep->execute();
            break;
        case 3:
            cout << "\nEnter new district: ";
            cin >> s;
            prep = con->prepareStatement("UPDATE city SET District = \"" + s + "\"WHERE ID = " + city);
            prep->execute();
            break;
        case 4:
            cout << "\nEnter new population: ";
            cin >> m;
            prep = con->prepareStatement("UPDATE city SET Population = ? WHERE ID = " + city);
            prep->setInt(1, m);
            prep->execute();
            break;
        case 5:
            delete res1;
            delete prep1;
            delete prep;
            return false;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    }
}

void Update(sql::Driver* driver, sql::Connection* con)
{
    int c;
    bool b = true;
    while (b == true)
    {
        system("cls");
        cout << "=UPDATING RECORDS: SELECT TABLE=\n1 - country\n2 - city\n3 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            b = Uco(driver, con);
            break;
        case 2:
            b = Uci(driver, con);
            break;
        case 3:
            return;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    };
}

bool Dco(sql::Driver* driver, sql::Connection* con)
{
    system("cls");
    cout << "=DELETING COUNTRY=\n";
    string country;
    country = getCountry_NameCode(driver, con);

    int n = 0;
    cout << "\nAre you sure? 1 - Yes, 2 - No\n";
    cin >> n;
    switch (n)
    {
    case 1:
        sql::PreparedStatement* prep;
        prep = con->prepareStatement("DELETE FROM countrylanguage WHERE CountryCode = \"" + country + "\"");
        prep->execute();
        prep = con->prepareStatement("DELETE FROM city WHERE CountryCode = \"" + country + "\"");
        prep->execute();
        prep = con->prepareStatement("DELETE FROM country WHERE Code = \"" + country + "\"");
        prep->execute();
        delete prep;
        return false;
    default:
        return false;
    }
}

bool Dci(sql::Driver* driver, sql::Connection* con)
{
    system("cls");
    cout << "=DELETING CITY=\n";
    string city = " ";
    city = getCity_NameID(driver, con);

    int n = 0;
    cout << "\nAre you sure? 1 - Yes, 2 - No\n";
    cin >> n;
    switch (n)
    {
    case 1:
        sql::PreparedStatement * prep;
        prep = con->prepareStatement("DELETE FROM city WHERE ID = " + city);
        prep->execute();
        delete prep;
        return false;
    default:
        return false;
    }
}

void Delete(sql::Driver* driver, sql::Connection* con)
{
    int c;
    bool b = true;
    while (b == true)
    {
        system("cls");
        cout << "=UPDATING RECORDS: SELECT TABLE=\n1 - country\n2 - city\n3 - return to main menu\n\nYour choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            b = Dco(driver, con);
            break;
        case 2:
            b = Dci(driver, con);
            break;
        case 3:
            return;
        default:
            cout << "-BAD OPERATION-";
            Sleep(WAIT);
        }
    };
}


int main(void)
{
    try {
        string pswd = " ";
        cout << "Enter password: ";
        cin >> pswd;

        sql::Driver* driver;
        sql::Connection* con;

        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", pswd);
        con->setSchema("world");

        cout << "=WELCOME IN WORLD DATABASE=\n";
        bool run = true;
        char c;
        while (run == true)
        {
            system("cls");
            cout << "=SELECT OPERATION=\nC - Create new record\nR - Read records\nU - Update existing record\nD - delete existing record\nE - Exit\n\nYour choice: ";
            cin >> c;

            switch (c)
            {
            case 'C':
                Create(driver, con);
                break;
            case 'R':
                Read(driver, con);
                break;
            case 'U':
                Update(driver, con);
                break;
            case 'D':
                Delete(driver, con);
                break;
            case 'E':
                run = false;
                break;
            default:
                cout << "-BAD OPERATION-";
                Sleep(WAIT);
            }
        }

        delete con;

    }
    catch (sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}