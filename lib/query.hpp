/**
 * LICENSE
 *
 Copyright 2015 Grégory Saive (greg@evias.be)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 *
**/

#ifndef QUERY_HPP
#define QUERY_HPP

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

    using std::string;
    using std::map;
    using std::vector;
    using std::initializer_list;
    using std::stringstream;

    /**
     * Statement part interface
     **/
    struct stmt_part
    {
        virtual operator string() = 0;
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
        select(initializer_list<string> l)
            : fields_(l)
        {};

        select(vector<string> f)
            : fields_(f)
        {};

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(fields_.begin(), fields_.end(), [&i, &str, this](string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "SELECT " + str : "";
        }

    private:
        vector<string> fields_;
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
        update(map<string, string> fields_values)
            : values_(fields_values)
        {};

        update(initializer_list<string> l)
        {
            for (auto line : l) {
                if (line.find("=") == string::npos) {
                    table_ = line;
                    continue;
                }

                string p1 = line.substr(0, line.find("="));
                string p2 = line.substr(line.find("=") + 1);

                values_.insert(std::make_pair(p1, p2));
            }
        };

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(values_.begin(), values_.end(), [&i, &str, this](std::pair<string,string> item) {
                /* Careful, there is no type cast done here to provide with a valid SQL key/value combination. */
                str += ((i > 0) ? ", " : "") + item.first + "=" + item.second;
                ++i;
            });
            return str.size() > 0 ? "UPDATE " + table_ + " SET " + str : "";
        }

    private:
        map<string,string> values_;
        string             table_;
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
        operator string() override
        {
            return "DELETE";
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
        from(initializer_list<string> l)
            : parts_(l)
        {}

        from(vector<string> p)
            : parts_(p)
        {}

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(parts_.begin(), parts_.end(), [&i, &str, this](string item) {
                str += ((i > 0) ? " " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "FROM " + str : "";
        }

    private:
        vector<string> parts_;
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
        where(initializer_list<string> l)
            : conditions_(l)
        {}

        where(vector<string> c)
            : conditions_(c)
        {}

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(conditions_.begin(), conditions_.end(), [&i, &str, this](string item) {
                str += ((i > 0) ? " AND " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "WHERE " + str : "WHERE TRUE";
        }

    private:
        vector<string> conditions_;
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
        group_by(initializer_list<string> l)
            : fields_(l)
        {}

        group_by(vector<string> f)
            : fields_(f)
        {}

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(fields_.begin(), fields_.end(), [&i, &str, this](string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "GROUP BY " + str : "";
        }

    private:
        vector<string> fields_;
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
        order_by(initializer_list<string> l)
            : parts_(l)
        {}

        order_by(vector<string> p)
            : parts_(p)
        {}

        operator string() override
        {
            string str;
            int i = 0;
            std::for_each(parts_.begin(), parts_.end(), [&i, &str, this](string item) {
                str += ((i > 0) ? ", " : "") + item;
                ++i;
            });
            return str.size() > 0 ? "ORDER BY " + str : "";
        }

    private:
        vector<string> parts_;
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
        limit(initializer_list<int> l)
        {
            vector<int> v = l;
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

        operator string() override
        {
            if (limit_ == 0 && offset_ == 0)
                return "";

            stringstream ss;
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


#endif  /* QUERY_HPP */

