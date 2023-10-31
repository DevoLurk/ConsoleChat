#include "User.h"

User::User(std::string name, std::string pass)
{
	login = name;
	password = pass;
}

void User::init(std::string name, std::string pass)
{
	login = name;
	password = pass;
}

User::User(User&& other) noexcept
{
	login = other.login;
	password = other.password;
	mailbox = std::move(other.mailbox); // other.mailbox resets on move. no need to reset it manually

	other.login = "";
	other.password = "";
}

User& User::operator=(User&& other) noexcept
{
	login = other.login;
	password = other.password;
	mailbox = std::move(other.mailbox); // other.mailbox resets on move. no need to reset it manually

	other.login = "";
	other.password = "";

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

void User::receiveMessage(Message msg)
{
	mailbox.addMessage(msg);
}

std::string User::getName()
{
	return login;
}

bool User::checkPass(std::string pass)
{
	if (pass == password)
		return true;

	return false;
}

int User::getMessageCnt()
{
	return mailbox.getCapity();
}