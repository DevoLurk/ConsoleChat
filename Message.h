#ifndef MESSAGE
#define MESSAGE

#include<string>

class Message
{
private:
	std::string message;
	std::string author;
	bool is_readed;

public:
	Message() = default;
	Message(std::string msg, std::string name);

	Message(const Message& other);
	Message(Message&& other) noexcept;
	Message& operator=(const Message& other);
	Message& operator=(Message && other) noexcept; 

	std::string getMsg();
	std::string getAuthor();
	bool getFlag();
	void setReaded();
};

#endif // MESSAGE