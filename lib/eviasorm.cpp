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

#include "for_each.hpp"
#include "query.hpp"
#include "row.hpp"
#include "statement.hpp"
#include "table.hpp"
#include "user.hpp"

using namespace evias;
using namespace dbo;

/**
 * evias::dbo::func_store_to_string static
 * field str_.
 **/
std::string func_store_to_string::str_ = "";

/**
 * evias::dbo::table static field conn_policy_.
 **/
std::string table::conn_policy_ = "";
