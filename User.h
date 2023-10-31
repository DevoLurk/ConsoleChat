#ifndef USER
#define USER

#include<iostream>
#include<string>
#include"Mailbox.h"

class User
{
private:
	std::string login;
	std::string password;
	Mailbox mailbox;

public:
	User() = default;
	User(std::string name, std::string pass);
	User(User& other) = delete;
	User(User&& other) noexcept;
	User& operator=(User& other) = delete;
	User& operator=(User&& other) noexcept;

	int getMessageCnt();
	std::string getName();
	Mailbox* getMailboxPtr();
	bool checkPass(std::string pass);
	void init(std::string name, std::string pass);
	void sendMessage(std::string message, User& target);
	void receiveMessage(Message msg);
};

#endif / USER