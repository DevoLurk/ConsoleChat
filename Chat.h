#ifndef CHAT
#define CHAT

#include<fstream>
#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include"User.h"
#include"myCrypt.h"
#include<unordered_map>
#include<vector>
#include<deque>

class Chat
{
	enum Screens
	{
		NOSCR,          // not set
		NEWACCOUNT,     // scr_newAccount
		WELLCOME,       // scr_welcome
		LOGIN,          // scr_login
		COMMANDS,       // scr_commands
		EXIT,           // scr_exit
		PRIVATE,        // scr_private
		PUBLIC,         // scr_public
		PROFILE,        // scr_profile
		MESSAG          // scr_message
	};

private:
	Screens current_screen;
	Screens previos_screen;
	std::string save_path{"ChatData.bin"};

	std::vector<User> users_array;
	std::deque<std::string> public_msgArr;
	std::unordered_map<std::string, Hash> pass_table;
	int current_user;

	
	void scr_newAccount();
	void scr_welcome();
	void scr_login();
	void scr_exit();
	void scr_private();
	void scr_commands();
	void scr_profile();
	void scr_public();
	void scr_load();
	void scr_message(Message& m);
	
	void showHistory();
	void showMailbox();
	void showUsers();
	void clearLine();
	void cmdProcessing();
	void myCinClear();
	void rememberMail(std::string str);
	void mySleep(int time = 120);
	void cmd_default(std::string& str);
	bool findUser(std::string name, int& pos);
	bool strCmp_read(std::string& str, int& num);
	bool strCmp_pm(std::string& str_cmd, std::string& str_msg);

	bool save();
	bool load();
	void saveStr(std::string& str, std::ofstream& fout);
	void loadStr(std::string& str, std::ifstream& fin);
	void saveHash(Hash& hash, std::ofstream& fout);
	void loadHash(Hash& hash, std::ifstream& fin);

public:
	Chat();
	Chat(std::string path);
	Chat(Chat& other) = delete;
	Chat& operator=(Chat& other) = delete;

	void start();
};

#endif // CHAT