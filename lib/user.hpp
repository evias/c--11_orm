#ifndef __USER_MODEL_HPP__
#define __USER_MODEL_HPP__

#include <pqxx/pqxx>

namespace dbo {

    class user
        : public pqxx::result::tuple
    {
    public:
        static std::vector<std::string> fields = {
            "id_user", "firstname", "lastname",
            "email", "date_created", "date_updated"};
    };
}

#endif /* __USER_MODEL_HPP__ */