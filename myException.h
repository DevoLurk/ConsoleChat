#ifndef MYEXCEPTION
#define MYEXCEPTION

#include <exception>

class  bad_users: public std::exception                       
{
public:
	virtual const char* what() const noexcept override
	{
		return "ERROR: Not possible to add a user. Maximum number of chat users";
	}
};

class  users_uniq : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "ERROR: The names of all users in the chat must be unique";
	}
};

class  users_empty : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "ERROR: Íou are trying to add an uninitialized user";
	}
};


#endif // MYEXCEPTION