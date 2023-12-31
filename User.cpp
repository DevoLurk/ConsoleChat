#include "User.h"

User::User(const User& other)
{
	login = other.login;
}

User& User::operator=(const User& other)
{
	login = other.login;

	return *this;
}

Mailbox* User::getMailboxPtr()
{
	return &mailbox;
}

void User::sendMessage(std::string message, User& target)
{
	Message msg(message, login);

	target.receiveMessage(msg);
}

void User::receiveMessage(Message& msg)
{
	mailbox.addMessage(msg);
}

std::string User::getName()
{
	return login;
}

int User::getMessageCnt()
{
	return mailbox.getCapity();
}