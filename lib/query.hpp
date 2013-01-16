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

    struct stmt_part;
    struct select;
    struct update;
    struct del;
    struct from;
    struct where;
    struct group_by;
    struct order_by;
    struct limit;

    /**
     * Statement part interface
     **/
    struct stmt_part
    {
        virtual operator std::string() = 0;
    };

    /**
     * SQL SELECT statement struct
     *
     * This structure allows easily defining a fields
     * list to be selected in the query.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct select
        : stmt_part
    {
        select(std::initializer_list<std::string> l)
            : fields_(l)
        {};

        operator std::string() override
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
     * SQL UPDATE statement struct
     *
     * This structure allows easily defining a fields/values
     * combinations list to update values in the query.
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct update
        : stmt_part
    {
        update(std::map<std::string, std::string> fields_values)
            : values_(fields_values)
        {};

        operator std::string() override
        {
            std::string str;
            int i = 0;
            std::for_each(values_.begin(), values_.end(), [&i, &str, this](std::pair<std::string,std::string> item) {
                /* Careful, there is no type cast done here to provide with a valid SQL key/value combination. */
                str += ((i > 0) ? ", " : "") + item.first + "=" + item.second;
                ++i;
            });
            return str.size() > 0 ? "UPDATE " + str : "";
        }

    private:
        std::map<std::string,std::string> values_;
    };

    /**
     * SQL DELETE statement struct
     *
     * The operator string() allows performing a
     * simple cast to string type.
     */
    struct del
        : stmt_part
    {
        del() = default;

        /**
         * SQL DELETE statement does not need any
         * specific data treatment, everything is
         * appended to the "DELETE" token directly
         * such that the FROM and WHERE part are set.
         */
        operator std::string() override
        {
            return "DELETE ";
        }
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
        : stmt_part
    {
        from(std::initializer_list<std::string> l)
            : parts_(l)
        {}

        operator std::string() override
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
        : stmt_part
    {
        where(std::initializer_list<std::string> l)
            : conditions_(l)
        {}

        operator std::string() override
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
        : stmt_part
    {
        group_by(std::initializer_list<std::string> l)
            : fields_(l)
        {}

        operator std::string() override
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
        : stmt_part
    {
        order_by(std::initializer_list<std::string> l)
            : parts_(l)
        {}

        operator std::string() override
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
        : stmt_part
    {
        limit(std::initializer_list<int> l)
        {
            std::vector<int> v = l;
            if (v.size() < 2) {
                limit_  = v.empty() ? 0 : v.at(0);
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

        operator std::string() override
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

