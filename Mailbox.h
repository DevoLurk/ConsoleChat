#ifndef MAILBOX
#define MAILBOX

#include"Message.h"

class Mailbox
{
private:
	Message* msg_arr_ptr;
	int max_cap = 100;        
	int capity;

public:
	Mailbox();
	Mailbox(Mailbox& other) = delete;
	Mailbox(Mailbox&& other) noexcept;
	Mailbox& operator=(Mailbox& other) = delete;
	Mailbox& operator=(Mailbox&& other) noexcept;
	~Mailbox();

	int getCapity();
	int getUnreadCnt();
	Message* getMailsArray();
	void addMessage(Message msg);
	bool getMessage(Message& msg, int position = 0);
};

#endif / MAILBOX
