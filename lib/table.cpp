#include "table.hpp"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <pqxx/pqxx>

using namespace evias;
using namespace dbo;

std::string table::conn_policy_ = "dbname= host= user= pass=";

/**
 * Destructor
 */
table::~table()
{
}

/**
 * Table constructor
 *
 * @param std::string name  The database relation name
 * @param std::vector<std::string> fields   The fields names list
 */
table::table(std::string name, std::vector<std::string> fields)
    : table_(name), fields_(fields)
{
}

/**
 * Table constructor
 * @param string name  The database relation name
 * @param vector<string> fields The fields names list
 * @param vector<string> pkeys  The primary keys names
 */
table::table(std::string name,
                           std::vector<std::string> fields,
                           std::vector<std::string> pkeys)
    : table_(name),
      fields_(fields),
      pkeys_(pkeys)
{
    std::vector<std::string> intersection;
    std::for_each(pkeys.begin(), pkeys.end(), [&intersection,this] (std::string item) {
        for (auto it : this->fields_)
            if (it == item)
                intersection.push_back(it);
    });

    if (intersection.size() != pkeys.size())
        throw std::exception();
}

/**
 * Copy constructor
 * @param const table& rhs  The object to be copied
 */
table::table(const table& rhs)
    : table_(rhs.table_),
      fields_(rhs.fields_),
      pkeys_(rhs.pkeys_)
{
}

/**
 * Move semantic constructor
 * @param table&& rval  Moved object (r-value)
 */
table::table(table&& rval)
    : table_(std::move(rval.table_)),
      fields_(std::move(rval.fields_)),
      pkeys_(std::move(rval.pkeys_))
{
}

void table::set_connection_data(std::string host, std::string db, std::string user, std::string pass)
{
    conn_policy_ = "host=" + host
                 + " dbname=" + db
                 + " user=" + user
                 + " pass=" + pass;
}

pqxx::result table::_query(std::string sql_query)
{
//    time_t              timestamp;
//    std::string         trxKey;
//    std::stringstream   trxSeed;
//    unsigned long       timeSeed;
//
//    time (&timestamp);
//    timeSeed= (unsigned long) timestamp;
//    trxSeed << "__evias_dbo_table_transaction_"
//            << timeSeed
//            << "__";
//    trxKey  = trxSeed.str();
//
//    pqxx::connection    db(conn_policy_);
    pqxx::result        res;
//    pqxx::transaction<> tr(db, trxKey);
//
//    try {
//        res = tr.exec(sql_query);
//
//        tr.commit();
//    }
//    catch (const std::exception& e) {
//        std::cerr << "-- caught an error.. aborting : " << e.what() << std::endl;
//    }

    return res;
}