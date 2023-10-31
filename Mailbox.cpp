#include "Mailbox.h"

Mailbox::Mailbox()
{
	capity = 0;
	msg_arr_ptr = new Message[max_cap];
}

Mailbox::~Mailbox()
{
	delete[] msg_arr_ptr;
}

Mailbox::Mailbox(Mailbox&& other) noexcept
{
	capity = other.capity;
	msg_arr_ptr = other.msg_arr_ptr;

	other.capity = 0;
	other.msg_arr_ptr = nullptr;
}

Mailbox& Mailbox::operator=(Mailbox&& other) noexcept
{
	capity = other.capity;
	msg_arr_ptr = other.msg_arr_ptr;

	other.capity = 0;
	other.msg_arr_ptr = nullptr;

	return *this;
}

void Mailbox::addMessage(Message msg)
{
	if (capity)
	{
		for (auto i{ capity }; i > 0; --i)
			msg_arr_ptr[i] = msg_arr_ptr[i - 1];

		msg_arr_ptr[0] = msg;
		capity++;
	}
	else
	{
		msg_arr_ptr[0] = msg;
		capity++;
	}
}

bool Mailbox::getMessage(Message& msg, int position)
{
	if ((position >= 0) && (position < capity))
	{
		msg = msg_arr_ptr[position];
		return true;
	}

	return false;
}

int Mailbox::getUnreadCnt()
{
	int cnt = 0;

	for (auto i{ 0 }; i < capity; ++i)
		if (!msg_arr_ptr[i].getFlag())
			cnt++;

	return cnt;
}

Message* Mailbox::getMailsArray() { return msg_arr_ptr; }

int Mailbox::getCapity() { return capity; }