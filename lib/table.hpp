/*
 * File:   table.hpp
 * Author: greg
 *
 * Created on January 15, 2013, 10:22 AM
 */

#ifndef TABLE_HPP
#define	TABLE_HPP

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <pqxx/pqxx>
#include "row.hpp"
#include "query.hpp"

namespace evias {
namespace dbo {

    using evias::dbo::select;
    using evias::dbo::from;
    using evias::dbo::where;

    /**
     * Database table class
     **/
    class table
    {
    protected :
        std::string table_ = "";
        std::vector<std::string>  pkeys_ = {};
        std::vector<std::string>  fields_ = {};

        static std::string conn_policy_;

    public:
        table() = default;
        table(std::string,std::vector<std::string>);
        table(std::string,
              std::vector<std::string>,
              std::vector<std::string>);

        /* Copy & move semantic */
        table(const table&);
        table(table&&);

        virtual ~table();

        static void set_connection_data(std::string,std::string,std::string,std::string);

        std::string query_select(select, from, where);

    private:
        pqxx::result _query(std::string);

        /** XXX **/
        /** XXX **/
        /** XXX **/
        /** XXX **/
//        template <typename ... _fields_t>
//        std::vector<row<_fields_t...>> query(std::string sql_query)
//        {
//            time_t              timestamp;
//            std::string         trxKey;
//            std::stringstream   trxSeed;
//            unsigned long       timeSeed;
//
//            time (&timestamp);
//            timeSeed= (unsigned long) timestamp;
//            trxSeed << "__evias_dbo_table_transaction_"
//                    << timeSeed
//                    << "__";
//            trxKey  = trxSeed.str();
//
//            pqxx::connection    db(conn_policy_);
//            pqxx::result        res;
//            pqxx::transaction<> tr(db, trxKey);
//
//            try {
//                res = tr.exec(sql_query);
//
//                tr.commit();
//            }
//            catch (const std::exception& e) {
//                std::cerr << "-- caught an error.. aborting : " << e.what() << std::endl;
//            }
//
//            std::vector<row<_fields_t...>> rows;
//            return rows;
//        }
    };

}
}

#endif	/* TABLE_HPP */

