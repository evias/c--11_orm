/*
 * File:   query.hpp
 * Author: greg
 *
 * Created on January 15, 2013, 4:24 PM
 */

#ifndef QUERY_HPP
#define	QUERY_HPP

#include <vector>
#include <map>
#include <string>
#include <algorithm>

namespace evias {
namespace dbo {

    /**
     * SQL SELECT statement struct
     *
     * This structure allows easily defining a fields
     * list to be selected in the query.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct select
    {
        select(std::initializer_list<std::string> l)
            : fields_(l)
        {};

        operator std::string()
        {
            std::string str;
            int i = 0;
            std::for_each(fields_.begin(), fields_.end(), [&i, &str, this](std::string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return "SELECT " + str;
        }

    private:
        std::vector<std::string> fields_;
    };

    /**
     * SQL FROM statement struct
     *
     * This structure allows easily defining a tables
     * list to select from in the query.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct from
    {
        from(std::initializer_list<std::string> l)
            : parts_(l)
        {}

        operator std::string()
        {
            std::string str;
            int i = 0;
            std::for_each(parts_.begin(), parts_.end(), [&i, &str, this](std::string item) {
                str += ((i > 0) ? " " : "") + item;
                ++i;
            });
            return "FROM " + str;
        }

    private:
        std::vector<std::string> parts_;
    };

    /**
     * SQL WHERE statement struct
     *
     * This structure allows easily defining a conditions
     * list to filter from in the query.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct where
    {
        where(std::initializer_list<std::string> l)
            : conditions_(l)
        {}

        operator std::string()
        {
            std::string str;
            int i = 0;
            std::for_each(conditions_.begin(), conditions_.end(), [&i, &str, this](std::string item) {
                str += ((i > 0) ? " AND " : "") + item;
                ++i;
            });
            return "WHERE " + str;
        }

    private:
        std::vector<std::string> conditions_;
    };

}
}


#endif	/* QUERY_HPP */

