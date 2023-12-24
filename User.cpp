#include "User.h"

User::User(std::string name)
{
	login = name;
}

void User::init(std::string name)
{
	login = name;
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

void User::receiveMessage(Message msg)
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

User::User(User& other)
{
	login = other.login;
	mailbox = std::move(other.mailbox);
}

User& User::operator=(User& other)
{
	login = other.login;
	mailbox = std::move(other.mailbox);
}