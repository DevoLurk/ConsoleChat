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
	User(std::string name);
	User(User& other);
	User& operator=(User& other);

	int getMessageCnt();
	std::string getName();
	Mailbox* getMailboxPtr();
	void init(std::string name);
	void sendMessage(std::string message, User& target);
	void receiveMessage(Message msg);
};

#endif // USER