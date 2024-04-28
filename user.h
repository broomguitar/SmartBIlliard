#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User
{
public:
    User();
    enum ROLE
    {
        ADMIN,
        MANAGER,
        NORMAL
    };

    enum GENDER
    {
        NONE,
        MALE,
        FEMALE
    };
    int Id;
    string UserName;
    string Password;
    ROLE Role;
    string Memo;
    string ProfilePhoto;
    GENDER Gender;
    bool IsVip;
    bool IsValid;
};

#endif // USER_H
