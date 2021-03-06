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

#ifndef __USER_MODEL_HPP__
#define __USER_MODEL_HPP__

#include "table.hpp"

namespace evias {
namespace dbo {

    class user
        : public table
    {
    public:
        user()
        {
            table_  = "user_obj";
            pkeys_  = {"id_user"};
            fields_ = {
                "id_user",
                "firstname",
                "lastname",
                "email",
                "date_created",
                "date_updated"
            };
        }
    };
}
}

#endif /* __USER_MODEL_HPP__ */