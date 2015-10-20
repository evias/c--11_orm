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

#ifndef ROW_HPP
#define	ROW_HPP

#include <string>
#include <vector>
#include <tuple>
#include <map>

namespace evias {
namespace dbo {

    template <typename ...> class row;

    /**
     * Database row template class
     *
     * This class allows working with fields
     * of different types as one set.
     *
     * @example
     * evias::dbo::row<int,char> alphabet_a(make_tuple(1, 'A'));
     * evias::dbo::row<int,string,string> user_greg(make_tuple(1, "greg@evias.be", "Greg"));
     **/
    template <typename ... _fields_t>
    class row
    {
    private:
        std::tuple<_fields_t...>  values_;

    public:
        row() = default;
        virtual ~row() = default;

        row(std::tuple<_fields_t...> vals)
            : values_(vals)
        {};

        row(const row& rhs)
            : values_(rhs.values_)
        {};

        row(row&& rhs)
            : values_(std::move(rhs.values_))
        {};

        row& operator=(const row& rhs)
        {
            values_ = rhs.values_;
        }

        row& operator=(row&& rhs)
        {
            values_ = std::move(rhs.values_);
        }

        std::tuple<_fields_t...> get()
        {
            return values_;
        }

    };

}
}

#endif	/* ROW_HPP */

