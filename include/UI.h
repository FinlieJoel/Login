#include <iostream>
#include "../include/UserFactory.h"
#include <vector>
#include <memory>

class UI
{
    int i;
    std::string userInput;
    void makeUser();
    std::vector<std::shared_ptr<UserFactory>> MyUsers;
    void printer();
    void showUser();
    void adminMode();
    void deleteUser();
    void unlockUser();
    bool enterPassword(const std::shared_ptr<UserFactory> &f);
    void threadPassword(std::shared_ptr<UserFactory> f);
    // void message(const std::shared_ptr<UserFactory> &f);

public:
    UI()
    {
        UI::printer();
        i = 0;
    };
};