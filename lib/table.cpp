#include "table.hpp"
#include "query.hpp"
#include "statement.hpp"

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <pqxx/pqxx>

using namespace evias;
using namespace dbo;

std::string table::conn_policy_ = "";

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
    _check_connection();
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
    _check_connection();

    std::vector<std::string> intersection;
    std::for_each(pkeys.begin(), pkeys.end(), [&intersection,this] (std::string item) {
        for (auto it : this->fields_)
            if (it == item) {
                intersection.push_back(it);
                break;
            }
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
    _check_connection();
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
    _check_connection();
}

void table::_check_connection()
{
    if (conn_policy_.empty())
        throw std::logic_error("Please initialize the connection policy.");

    if (conn_policy_.find("host") == std::string::npos
        || conn_policy_.find("dbname") == std::string::npos
        || conn_policy_.find("user") == std::string::npos
        || conn_policy_.find("password") == std::string::npos)
        throw std::logic_error(
              "Wrong connection policy format: host, dbname, user, password are mandatory");
}

void table::set_connection_config(std::string p)
{
    conn_policy_ = p;
}

pqxx::result table::select(where _where, group_by _group, order_by _order, limit _limit)
{
    _check_connection();

    /* following line needed because of method name 'select' */
    using select = evias::dbo::select;

    select _select(fields_);
    evias::dbo::from   _from{table_};

    using tuple_t = std::tuple<select,from,where,group_by,order_by,limit>;
    using stmt_t  = statement<select,from,where,group_by,order_by,limit>;

    stmt_t::policy_ = conn_policy_;

    stmt_t my_stmt(tuple_t{
        _select, _from, _where,
        _group, _order, _limit});

    return my_stmt();
}
