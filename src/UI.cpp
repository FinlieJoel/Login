#include "../include/UI.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;
bool gNotified = false;

void UI::threadPassword(std::shared_ptr<UserFactory> f)
{
    f->setLock();
    std::cout << "thread .. This account has been blocked for 1 minute\n";
    std::this_thread::sleep_for(std::chrono::seconds(60));
    f->setUnlock();
}

void UI::printer()
{
    char decision;
    std::cout << "You have entered the UI . .\n";
    bool x = true;
    do
    {
        std::cout << "Create account: Y\n"
                  << "View account: V\n"
                  << "Exit: X\n";
        std::cin >> decision;
        system("cls");
        switch (decision)
        {
        case 'y':
            UI::makeUser();
            break;
        case 'Y':
            UI::makeUser();
            break;
        case 'v':
            UI::showUser();
            break;
        case 'V':
            UI::showUser();
            break;
        case 'x':
            x = false;
            break;
        case 'X':
            x = false;
            break;

        default:
            std::cout << "Invalid entry ..\n";
            break;
        }
    } while (x == true);
}

void UI::makeUser()
{
    std::shared_ptr<UserFactory> newUser = std::make_shared<UserFactory>(i);
    MyUsers.push_back(newUser);
    i++;
}

void UI::adminMode()
{
    char userInput;
    bool x = true;
    for (std::vector<std::shared_ptr<UserFactory>>::iterator f = MyUsers.begin(); f != MyUsers.end(); ++f)
    {
        std::cout << "User ID: " << (*f)->getID() << " User name: " << (*f)->getUserName() << std::endl;
    }
    do
    {
        std::cout << "Would you like to:  delete users (d), Unlock users (u), exit(x) " << std::endl;
        std::cin >> userInput;
        switch (userInput)
        {
        case 'd':
            UI::deleteUser();
            x = false;
            break;
        case 'D':
            UI::deleteUser();
            x = false;
            break;
        case 'u':
            UI::unlockUser();
            x = false;
            break;
        case 'U':
            UI::unlockUser();
            x = false;
            break;
        case 'x':
            x = false;
            break;
        case 'X':
            x = false;
            break;

        default:
            std::cout << "Invalid entry ..\n";
            break;
        }
    } while (x == true);
}

void UI::showUser()
{
    std::unique_lock<std::mutex> lock(gLock);
    std::cout << "User name: ";
    std::cin >> userInput;
    if (userInput == "ADMIN")
    {
        UI::adminMode();
    }
    else
    {
        for (std::vector<std::shared_ptr<UserFactory>>::iterator f = MyUsers.begin(); f != MyUsers.end(); ++f)
        {
            if ((*f)->getUserName() == userInput)
            {
                if ((*f)->getLock() == true)
                {
                    std::cout << "This account is locked\n";
                }
                else
                {
                    system("cls");
                    if (UI::enterPassword(*f) == false)
                    {

                        std::thread producerThread(&UI::threadPassword, this, *f); // range based for loop
                        producerThread.detach();
                        std::cout << "This account has been blocked for 1 minute\n";
                    }
                }
                std::cin >> userInput;
                system("cls");
                //    std::thread producerThread(&UI::threadPassword, this); // range based for loop
            }
        }
    }
}

bool UI::enterPassword(const std::shared_ptr<UserFactory> &f)
{

    int j = 0;
    do
    {
        std::string userInput;
        std::cout << "Password: ";
        std::cin >> userInput;
        system("cls");
        if ((f)->getPassword() == userInput)
        {
            std::cout << "Message: " << (f)->getMessage() << std::endl;
            std::cout << "Press any key and enter to exit ...\n";
            std::cin >> userInput;
            // system("cls");
            return true;
        }
        else
        {
            j++;
            if (j == 3)
            {
                std::cout << "You have no attempts left .. \n";
                return false;
            }
            else
            {
                std::cout << "Password incorrect, " << 3 - j << " attempts left\n";
            }
        }
    } while (j < 5);
    return false;
}

void UI::deleteUser()
{
    int found = 0;
    int userInput;
    std::cout << "Enter user ID you like to delete \n";
    std::cin >> userInput;
    for (std::vector<std::shared_ptr<UserFactory>>::iterator f = MyUsers.begin(); f != MyUsers.end(); ++f)
    {
        if ((*f)->getID() == userInput)
        {
            std::cout << userInput << " has been deleted \n";
            MyUsers.erase(f--);
            found++;
        }
    }
    if (found == 0)
    {
        std::cout << "User could not be found .. \n";
    }
}
void UI::unlockUser()
{
    int found = 0;
    int userInput;
    std::cout << "Enter user ID you like to unlock \n";
    std::cin >> userInput;
    for (std::vector<std::shared_ptr<UserFactory>>::iterator f = MyUsers.begin(); f != MyUsers.end(); ++f)
    {
        if ((*f)->getID() == userInput)
        {
            std::cout << userInput << " has been unlocked \n";
            (*f)->setUnlock();
            found++;
        }
    }
    if (found == 0)
    {
        std::cout << "User could not be found .. \n";
    }
}