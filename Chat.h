#ifndef CHAT
#define CHAT

#include<fstream>
#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include"User.h"
#include"myScreens.h"
#include"myException.h"

class Chat
{
private:
	Screens current_screen;
	Screens previos_screen;
	std::string save_path{"ChatData.bin"};
	std::string* pub_msgArr;
	User* users;
	int current_user;
	int users_cnt;
	int mail_cnt;
	int max_users = 100;
	int max_mails = 100;
	
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

	bool save();
	bool load();
	void showHistory();
	void showMailbox();
	void showUsers();
	void clearLine();
	void cmdProcessing();
	void myCinClear();
	void rememberMail(std::string str);
	void mySleep(int time = 120);
	void cmd_default(std::string& str);
	void saveStr(std::string& str, std::ofstream& fout);
	void loadStr(std::string& str, std::ifstream& fin);
	bool findUser(std::string name, int& pos);
	bool strCmp_read(std::string& str, int& num);
	bool strCmp_pm(std::string& str_cmd, std::string& str_msg);

public:
	Chat();
	Chat(std::string path);
	Chat(Chat& other) = delete;
	Chat& operator=(Chat& other) = delete;
	~Chat();

	void start();
	void addUser(User& u);
};

#endif / CHAT