#include "Chat.h"


Chat::Chat()
{
    users_cnt = 0;
    mail_cnt = 0;
    current_user = NULL;
    current_screen = NOSCR;
    previos_screen = NOSCR;
    users = new User[max_users];
    pub_msgArr = new std::string[max_mails];
}

Chat::~Chat()
{
    delete[] users;
}

Chat::Chat(Chat&& other) noexcept
{
    users = other.users;
    users_cnt = other.users_cnt;// no need to copy all because chat will inicialize it on start();
    pub_msgArr = other.pub_msgArr;
    mail_cnt = other.mail_cnt;

    other.current_user = NULL;
    other.current_screen = NOSCR;
    other.previos_screen = NOSCR;
    other.users_cnt = 0;
    other.mail_cnt = 0;
    other.users = nullptr;
    other.pub_msgArr = nullptr;
}

Chat& Chat::operator=(Chat&& other) noexcept
{
    users = other.users;
    users_cnt = other.users_cnt; // no need to copy all because chat will inicialize it on start();
    pub_msgArr = other.pub_msgArr;
    mail_cnt = other.mail_cnt;

    other.current_user = NULL;
    other.current_screen = NOSCR;
    other.previos_screen = NOSCR;
    other.users_cnt = 0;
    other.mail_cnt = 0;
    other.users = nullptr;
    other.pub_msgArr = nullptr;

    return *this;
}

void Chat::start()
{
    if (!users_cnt)
        scr_newAccount();

    char ch = ' ';

    while(true)
    {
        switch (ch)
        {
        case 'y':
            mySleep();
            scr_login();
            break;
        case 'n':
            mySleep();
            scr_newAccount();
            break;
        default:
            scr_welcome();
            std::cin >> ch;
            break;
        }
    } 
}

void Chat::scr_newAccount()
{
    previos_screen = current_screen;
    current_screen = NEWACCOUNT;

    if (users_cnt >= (max_users - 1))
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t\033[36m      Max users count in chat reached\033[0m");

        mySleep();
        scr_exit();
    }
    
    std::string login;
    std::string pass;
    int foo;

    system("cls");
    printf("\n\n\n");
    printf("\t\t\033[36m      Creating new account\033[0m\n\n");
    printf("\t\t\033[36m    LOGIN: \033[0m");
    std::cin >> login;

    if (findUser(login, foo))
    {
        system("cls");
        printf("\033[36m");
        printf("\n\n\t\033[36m User\033[0m %s\033[36m already exists\033[0m", login.c_str());
        mySleep(900);
        printf("\n\t\033[36m     Please try again \033[0m");
        mySleep(1200);

        scr_newAccount();
    }
     
    printf("\t\t\033[36m PASSWORD: \033[0m");
    std::cin >> pass;

    current_user = users_cnt;
    users[current_user].init(login, pass);
    users_cnt++;

    mySleep();
    scr_commands();
}

void Chat::scr_welcome()
{
    previos_screen = current_screen;
    current_screen = WELLCOME;

    system("cls");
    printf("\n\n\n");
    printf("\t\t\033[36m          Wellcome to the chat!\033[0m\n\n");
    printf("\t\t\033[36m     do you already have an account?\033[0m\n\n");
    printf("\t\t              type \033[32my\033[0m or \033[31mn\033[0m\n\n");
    printf("\t\t              ");
}

void Chat::scr_login()
{
    previos_screen = current_screen;
    current_screen = LOGIN;

    std::string login;
    std::string pass;

    system("cls");
    printf("\n\n\n");
    printf("\t\t\033[36m    LOGIN: \033[0m");
    std::cin >> login;
    
    if (findUser(login, current_user))
    {
        printf("\t\t\033[36m PASSWORD: \033[0m");
        std::cin >> pass;

        if (users[current_user].checkPass(pass))
        {
            mySleep();
            scr_commands();
        }
        else
        { 
            system("cls");
            printf("\n\n\n");
            printf("\t\033[36m  Wrong password \033[0m\n");
            mySleep(900);
            printf("\t\033[36m  Please try again \033[0m");
            mySleep(1200);

            scr_login();
        }
    }
    else
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\033[36m  Cant find user:    \033[0m %s", login.c_str());
        mySleep(900);
        printf("\n\t\033[36m  Please try again \033[0m");
        mySleep(1500);

        scr_login();
    }
}

void Chat::addUser(User& u)
{
    if (users_cnt < max_users)
    {
        if (u.getName().length() > 0)
        {
            int foo;
            if (!findUser(u.getName(), foo))
            {
                if (!users_cnt)
                {
                    current_user = 0;
                    users[current_user] = std::move(u);
                    users_cnt++;

                }
                else
                {
                    current_user = users_cnt;
                    users[current_user] = std::move(u);
                    users_cnt++;
                }
            }
            else
                throw users_uniq();
        }
        else
            throw users_empty();
    }
    else
        throw bad_users();
}

void Chat::showMailbox()
{
    Mailbox* box = users[current_user].getMailboxPtr();

    if (!box->getCapity())
    {
        printf("\n   You have no mails\n\n");
        return;
    }

    printf("\n");

    std::string str_out;
    std::string name_out;

    for (auto i{ 0 }; i < box->getCapity(); ++i)
    {
        str_out.assign(box->getMailsArray()[i].getMsg(), 0, 15);    // shortening messages
        str_out += "...";

        if (box->getMailsArray()[i].getAuthor().length() > 11)      // shortening of long names
        {
            name_out.append(box->getMailsArray()[i].getAuthor(), 0, 9);
            name_out += "..";
        }
        else
            name_out = box->getMailsArray()[i].getAuthor();

        if (box->getMailsArray()[i].getFlag())  // Unreaded will print grey. Readed will be yellow
        {
            printf("  %d.", i + 1);
            printf(" %11s: ", name_out.c_str());
            printf("\033[90m");
            printf("%s", str_out.c_str());
            printf("\033[0m");
        }
        else
        {
            printf("  %d.", i + 1);
            printf(" %11s: ", name_out.c_str());
            printf("\033[33m");
            printf("%s", str_out.c_str());
            printf("\033[0m");
        }
        printf("\n");
    }
    printf("\n");
}

bool Chat::findUser(std::string name, int& pos)
{
    for (auto i{ 0 }; i < users_cnt; i++)
        if (users[i].getName() == name)
        {
            pos = i;
            return true;
        }

    return false;
}

void Chat::scr_commands()
{
    previos_screen = current_screen;
    current_screen = COMMANDS;

    system("cls");
    printf("\n\n");
    printf("\t\t\033[36m     Commands list\033[0m\n\n");
    printf("\t\033[93m\\private\033[0m - send private messages\n\n");
    printf("\t\033[93m\\public\033[0m  - public chat\n\n");
    printf("\t\033[93m\\profile\033[0m - go to profile + check mails\n\n");
    printf("\t\033[93m\\help\033[0m    - see commands list\n\n");
    printf("\t\033[93m\\close\033[0m   - close programm\n\n");
    printf("\t\033[93m\\logout\033[0m  - go to the starting screen\n\n");
    printf("\t\033[93m\\read N\033[0m  - read message number N (profile screen)\n\n");
    printf("\t\033[93m\\back\033[0m    - return to profile (message reading screen)\n\n");
    printf("\t\033[93m\\\NAME MESSAGE\033[0m  - send message to user (private screen) \n\n");

    cmdProcessing();
}

void Chat::scr_exit()
{
    previos_screen = current_screen;
    current_screen = EXIT;

    system("cls");
    printf("\n\n\n");
    printf("\t\t\033[36m     Saving data");

    for (auto i{ 0 }; i < 4; ++i)
    {
        mySleep(180);
        printf(".");
    }

    printf("\n\n\t\t     complete\033[0m");
    mySleep(250);

    printf("\n\n\n\n\n\n\n");
    exit(0);
}


void Chat::cmdProcessing()
{
    std::string str;

    if (current_screen == COMMANDS)
    {
        while(true)
        {
            printf("\t");
            std::cin >> str;

            cmd_default(str);
            clearLine();
        }
    }
    
    if(current_screen == PROFILE)
    {
        Message* msgArr;
        int pos;

        myCinClear();

        while(true)
        {
            printf("\t");
            std::getline(std::cin, str);

            cmd_default(str);

            if (strCmp_read(str, pos))
            {
                if ((pos >= 1) && (pos <= users[current_user].getMessageCnt()) ) // if message position relevant
                {
                    --pos; // we print from 1 so user enters nums from 1 (not from 0)
                    msgArr = users[current_user].getMailboxPtr()->getMailsArray();

                    scr_message(msgArr[pos]);
                }
            }
            clearLine();
        }
    }

    if(current_screen == PRIVATE)
    { 
        std::string str_msg;
        
        myCinClear();

        while(true)
        {
            printf("\t");
            std::getline(std::cin, str);

            cmd_default(str);

            if (strCmp_pm(str, str_msg)) // str = login, str_msg = message
            {
                int pos;
                if (findUser(str, pos)) // find user position by login
                {
                    Message msg(str_msg, str);
                    users[pos].receiveMessage(msg);

                    clearLine();
                    printf("\033[36m     Message sended to user\033[0m %s\n", str.c_str());
                    mySleep(1000);
                }
                else
                {
                    clearLine();
                    printf("\033[36m     Cant find user\033[0m %s\n", str.c_str());
                    mySleep(1000);
                }
            }
            clearLine();
        }
    }

    if (current_screen == MESSAG)
    {
        while(true)
        {
            printf("\t");
            std::cin >> str;

            cmd_default(str);
            if (str == "\\back") { mySleep(); scr_profile(); }

            clearLine();
        }
    }

    if (current_screen == PUBLIC)            
    { 
        std::string name_out;
        std::string msg_to_save;

        if (users[current_user].getName().length() > 11)      // shortening of long names
        {
            name_out.append(users[current_user].getName(), 0, 9);
            name_out += "..";
        }
        else
            name_out = users[current_user].getName();
        
        myCinClear();

        while(true)
        {
            printf("%11s : ", name_out.c_str());

            std::getline(std::cin, str);

            cmd_default(str);

            clearLine();
            printf("%11s : ", name_out.c_str());
            printf("%s\n", str.c_str());

            msg_to_save = name_out;
            msg_to_save += " : ";
            msg_to_save += str;

            rememberMail(msg_to_save);
        }
    }
}

void Chat::cmd_default(std::string& str)
{
    if ((str == "\\help") && (current_screen != COMMANDS))   { mySleep(); scr_commands(); }

    if ((str == "\\private") && (current_screen != PRIVATE)) { mySleep(); scr_private(); }

    if ((str == "\\public") && (current_screen != PUBLIC))   { mySleep(); scr_public(); }

    if ((str == "\\profile") && (current_screen != PROFILE)) { mySleep(); scr_profile(); }

    if (str == "\\logout") { mySleep(); start(); }

    if (str == "\\close")  { mySleep(); scr_exit(); }
}

void Chat::scr_profile()
{
    previos_screen = current_screen;
    current_screen = PROFILE;
    Mailbox* box = users[current_user].getMailboxPtr();

    system("cls");
    printf("\n");
    printf("\t\033[36m Hello \033[0m %s\n", users[current_user].getName().c_str());
    printf("\t\033[36m You have\033[0m %d\033[36m new mails \033[0m \n\n", box->getUnreadCnt());

    showMailbox();
    cmdProcessing();
}

void Chat::clearLine()
{
    printf("\033[A");       // line up
    printf("\33[2K\r");     // clear line + move curor
}

bool Chat::strCmp_read(std::string& str, int& num) // find commad and num in string
{
    std::string s_cmd, s_num;

    if (str.length() > 9)
        return false;

    s_cmd.assign(str, 0, 6);

    if (s_cmd == "\\read ")
    {
        int numsize = str.length() - s_cmd.length();
        num = 0;

        s_num.assign(str, s_cmd.length(), numsize);

        for (auto i{ 0 }; i < numsize; i++)
        {
            if ((s_num[i] >= '0') && (s_num[i] <= '9'))
            {
                num = num * 10 + (s_num[i] - '0');
            }
            else
                return false;
        }
        return true;
    }
    return false;
}

void Chat::scr_public()
{
    previos_screen = current_screen;
    current_screen = PUBLIC;

    system("cls");
    printf("\n\t\033[36m PUBLIC CHAT BEGINNING\033[0m\n\n\n\n"); 

    if (mail_cnt)
    {
        printf("\033[A\033[A");
        printf("\t\033[36m  %d messages loaded\033[0m\n\n", mail_cnt);
    }

    showHistory();
    cmdProcessing();
}

void Chat::scr_private()
{
    previos_screen = current_screen;
    current_screen = PRIVATE;

    system("cls");
    printf("\n\t\033[36m       Currently %d users in chat\033[0m\n\n", users_cnt);

    showUsers();
    cmdProcessing();
}

void Chat::scr_message(Message& m)
{
    previos_screen = current_screen;
    current_screen = MESSAG;

    system("cls");
    printf("\n\tMessage from \033[32m %s \033[0m", m.getAuthor().c_str());
    printf("\n\n   %s \n\n", m.getMsg().c_str());
    m.setReaded();

    cmdProcessing();
}

void Chat::mySleep(int time)
{
    std::chrono::milliseconds timespan(time);
    std::this_thread::sleep_for(timespan);
}

void Chat::showUsers()
{
    printf("\n\t");

    for (auto i{ 0 }; i < users_cnt; i++)
    {
        if ((i % 8) == 0)
            printf("\n\t");

        printf("\033[32m");
        printf("%s, ", users[i].getName().c_str());

    }
    printf("\b\b.\033[0m\n\n");
}

bool Chat::strCmp_pm(std::string& str_cmd, std::string& str_msg)
{
    if (str_cmd[0] == '\\')
    {
        int pos = str_cmd.find(' ', 2);
        
        if (pos == -1)            // str do not contain ' ' 
            return false;

        str_msg = str_cmd;
        str_cmd.erase(pos, str_cmd.length() - pos);
        str_msg.erase(0, str_cmd.length() + 1);
        str_cmd.erase(0, 1);

        return true;
    }
    return false;
}

void Chat::myCinClear() // need it for getline // I hate the way how getline works..almost spend 3 or 4 hours on this
{
    if (!((previos_screen == PROFILE) || (previos_screen == PRIVATE) || (previos_screen == PUBLIC)))
    {
        std::cin.clear();                 
        while (std::cin.get() != '\n')
        {
            continue;
        }
    }
}

void Chat::showHistory()
{
    if (!mail_cnt)
        return;

    for (auto i{ 0 }; i < mail_cnt; i++)
        printf("\t%s\n", pub_msgArr[i].c_str());
}

void Chat::rememberMail(std::string str)
{
    if (mail_cnt < max_mails)
    {
        pub_msgArr[mail_cnt] = str;
        mail_cnt++;
        return;
    }

    for (auto i{ 1 }; i < max_mails; i++)
    {
        pub_msgArr[i - 1] = pub_msgArr[i];
        pub_msgArr[0] = str;
    }
}