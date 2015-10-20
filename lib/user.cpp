#include "user.hpp"

using namespace dbo;

std::vector<std::string> dbo::user::fields = {
    "id_user",
    "firstname",
    "lastname",
    "email",
    "date_created",
    "date_updated"
};
