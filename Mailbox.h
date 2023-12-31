#ifndef MAILBOX
#define MAILBOX

#include"Message.h"
#include<vector>

class Mailbox
{
private:
	std::vector<Message> msgArr;       

public:
	Mailbox() = default;
	Mailbox(const Mailbox& other) = delete;
	Mailbox& operator=(const Mailbox& other) = delete;
	~Mailbox() = default;

	size_t getCapity();
	int getUnreadCnt();
	Message* getMailsArray();
	void addMessage(Message& msg);
	bool getMessage(Message& msg, int position = 0);
};

#endif / MAILBOX
