#include "utils.h"

std::string utils::get_working_path()
{
    char temp[PATH_MAX];

    if (getcwd(temp, PATH_MAX) != 0)
        return std::string(temp);

    int error = errno;

    switch (error)
    {
        // EINVAL can't happen - size argument > 0

        // PATH_MAX includes the terminating nul,
        // so ERANGE should not be returned

    case EACCES: throw std::runtime_error("Access denied");

    case ENOMEM:
        // I'm not sure whether this can happen or not
        throw std::runtime_error("Insufficient storage");

    default: {
        throw std::runtime_error("Some error occured");
    }
    }
}
