#include <iostream>
#include <string>
#include "../include/UserFactory.h"

UserFactory::UserFactory(int i)
{
    std::cout << "Hello new user! \n";
    UserFactory::setUserName();
    UserFactory::setPassword();
    UserFactory::setMessage();
    UserFactory::setID(i);
}

void UserFactory::setUserName()
{
    std::cout << "What would you like your user name to be?\n";
    std::cin >> userName;
    system("cls");
}

void UserFactory::setPassword()
{
    std::cout << "What would you like your password to be?\n";
    std::cin >> password;
    system("cls");
}

void UserFactory::setMessage()
{
    std::cout << "What would you like your message to be?\n";
    std::cin >> message;
    system("cls");
}
void UserFactory::setID(int i)
{
    ID = i;
}

void UserFactory::setLock()
{
    lock = true;
}
void UserFactory::setUnlock()
{
    lock = false;
}

bool UserFactory::getLock()
{
    return lock;
}

std::string UserFactory::getUserName()
{
    return userName;
}
std::string UserFactory::getPassword()
{
    return password;
}
std::string UserFactory::getMessage()
{
    return message;
}
int UserFactory::getID()
{
    return ID;
}