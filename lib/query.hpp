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
#include <sstream>
#include <algorithm>

namespace evias {
namespace dbo {

    struct select;
    struct from;
    struct where;
    struct group_by;
    struct order_by;
    struct limit;

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
            return str.size() > 0 ? "SELECT " + str : "";
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
            return str.size() > 0 ? "FROM " + str : "";
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
            return str.size() > 0 ? "WHERE " + str : "";
        }

    private:
        std::vector<std::string> conditions_;
    };

    /**
     * SQL GROUP BY statement struct
     *
     * This structure allows easily defining a fields
     * list to group the result by.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct group_by
    {
        group_by(std::initializer_list<std::string> l)
            : fields_(l)
        {}

        operator std::string()
        {
            std::string str;
            int i = 0;
            std::for_each(fields_.begin(), fields_.end(), [&i, &str, this](std::string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "GROUP BY " + str : "";
        }

    private:
        std::vector<std::string> fields_;
    };

    /**
     * SQL ORDER BY statement struct
     *
     * This structure allows easily defining a order
     * statement list to sort the result with.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct order_by
    {
        order_by(std::initializer_list<std::string> l)
            : parts_(l)
        {}

        operator std::string()
        {
            std::string str;
            int i = 0;
            std::for_each(parts_.begin(), parts_.end(), [&i, &str, this](std::string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "ORDER BY " + str : "";
        }

    private:
        std::vector<std::string> parts_;
    };

    /**
     * SQL OFFSET/LIMIT statement struct
     *
     * This structure allows easily defining an offset
     * and a limit of count for the result list.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct limit
    {
        limit(std::initializer_list<int> l)
        {
            std::vector<int> v = l;
            if (v.size() < 2) {
                limit_  = 0;
                offset_ = 0;
            }
            else {
                limit_  = v.at(0);
                offset_ = v.at(1);
            }
        };

        limit(int lim, int offset = 0)
            : limit_(lim), offset_(offset)
        {}

        operator std::string()
        {
            if (limit_ == 0 && offset_ == 0)
                return "";

            std::stringstream ss;
            ss << "LIMIT " << limit_;
            if (offset_ != 0)
                ss << " OFFSET " << offset_;
            ss << std::ends;
            return ss.str();
        }

    private:
        int limit_;
        int offset_;
    };
}
}


#endif	/* QUERY_HPP */

