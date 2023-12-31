#include "Mailbox.h"


void Mailbox::addMessage(Message& msg)
{
	msgArr.push_back(msg);
}

bool Mailbox::getMessage(Message& msg, int position)
{
	if ((position >= 0) && (position < msgArr.size()))
	{
		msg = msgArr[position];
		return true;
	}

	return false;
}

int Mailbox::getUnreadCnt()
{
	int cnt = 0;

	for (auto i{ 0 }; i < msgArr.size(); ++i)
		if (!msgArr[i].getFlag())
			cnt++;

	return cnt;
}

Message* Mailbox::getMailsArray()
{ 
	return msgArr.data();
}

size_t Mailbox::getCapity()
{
	return msgArr.size();
}