#ifndef USER
#define USER

#include<iostream>
#include"Mailbox.h"

class User
{
private:
	std::string login;
	Mailbox mailbox;

public:
	User() = default;
	User(std::string login_) : login(std::move(login_)) {};
	User(const User& other);
	User& operator=(const User& other);
	~User() = default;

	int getMessageCnt();
	std::string getName();
	Mailbox* getMailboxPtr();
	void sendMessage(std::string message, User& target);
	void receiveMessage(Message& msg);
};

#endif // USER