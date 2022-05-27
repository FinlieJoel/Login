#include "../include/User.h"

class UserFactory : public User
{
public:
    UserFactory(int);
    void setPassword();
    void setUserName();
    void setMessage();
    void setID(int);
    int getID();
    void setLock();
    void setUnlock();
    std::string getUserName();
    std::string getPassword();
    std::string getMessage();
    bool getLock();
};