#include "Chat.h"


Chat::Chat()
{
    current_user = NULL;
    current_screen = NOSCR;
    previos_screen = NOSCR;
}

Chat::Chat(std::string path) : Chat()
{
    save_path = path;
}

void Chat::start()
{
    if (current_screen == NOSCR)
    {
        scr_load();

        if (users_array.empty())
            scr_newAccount();
    }
    

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
            mySleep();
            scr_welcome();
            std::cin >> ch;
            break;
        }
        myCinClear();
    } 
}

void Chat::scr_newAccount()
{
    previos_screen = current_screen;
    current_screen = NEWACCOUNT;

    if (users_array.size() == users_array.max_size())
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t\033[36m      Max users count in chat reached\033[0m");

        mySleep();
        scr_exit();
    }

    std::string login;
    std::string pass;

    system("cls");
    printf("\n\n\n");
    printf("\t\t\033[36m      Creating new account\033[0m\n\n");
    printf("\t\t\033[36m    LOGIN: \033[0m");
    std::cin >> login;

    if (findUser(login, current_user))
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

    users_array.emplace_back(login);
    Hash hash = sha1((char*)pass.c_str(), pass.size());

    pass_table.emplace(std::make_pair(login, hash));
    current_user = users_array.size() - 1;

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

        Hash hash = sha1((char*)pass.c_str(), pass.size());

        if (hash == pass_table[login])
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

void Chat::showMailbox()
{
    Mailbox* box = users_array[current_user].getMailboxPtr();

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
        str_out.assign(box->getMailsArray()[i].getMsg(), 0, 17);    // shortening messages
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
            printf("  %3d.", i + 1);
            printf(" %11s: ", name_out.c_str());
            printf("\033[90m");
            printf("%s", str_out.c_str());
            printf("\033[0m");
        }
        else
        {
            printf("  %3d.", i + 1);
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
    for (auto i{ 0 }; i < users_array.size(); i++)
        if (users_array[i].getName() == name)
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

    if (save())
    {
        printf("\n\n\t\t     Complete\033[0m");
        mySleep(250);
    }
    else
    {
        printf("\n\n\t\t     Save error\033[0m");
        mySleep(250);
    }

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
                if ((pos >= 1) && (pos <= users_array[current_user].getMessageCnt()) ) // if message position relevant
                {
                    --pos; // we print from 1 so user enters nums from 1 (not from 0)
                    msgArr = users_array[current_user].getMailboxPtr()->getMailsArray();

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
                    users_array[pos].receiveMessage(msg);

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

        if (users_array[current_user].getName().length() > 11)      // shortening of long names
        {
            name_out.append(users_array[current_user].getName(), 0, 9);
            name_out += "..";
        }
        else
            name_out = users_array[current_user].getName();
        
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
    Mailbox* box = users_array[current_user].getMailboxPtr();

    system("cls");
    printf("\n");
    printf("\t\033[36m Hello \033[0m %s\n", users_array[current_user].getName().c_str());
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
    printf("\n\t\033[36m PUBLIC CHAT BEGINNING\033[0m\n\n"); 

    if(!public_msgArr.empty())
        printf("\t\033[36mlsst %d messages loaded\033[0m\n\n", public_msgArr.size());
    

    showHistory();
    cmdProcessing();
}

void Chat::scr_private()
{
    previos_screen = current_screen;
    current_screen = PRIVATE;

    system("cls");
    printf("\n\t\033[36m       Currently %d users in chat\033[0m\n\n", users_array.size());

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

    for (auto i{ 0 }; i < users_array.size(); i++)
    {
        if ((i % 8) == 0)
            printf("\n\t");

        printf("\033[32m");
        printf("%s, ", users_array[i].getName().c_str());

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
    if (public_msgArr.empty())
        return;

    for (auto i{ 0 }; i < public_msgArr.size(); i++)
        printf("\t%s\n", public_msgArr[i].c_str());
}

void Chat::rememberMail(std::string str) // remember 1000 last mails
{
    if(public_msgArr.size() < 1000)
        public_msgArr.push_back(str);
    else
    {
        public_msgArr.pop_front();
        public_msgArr.push_back(str);
    }
}

bool Chat::save()
{
    std::ofstream fout(save_path, std::ios_base::binary);

    if (!fout.is_open()) // if file is not opened/created
        return false; 

    size_t capity;

    capity = public_msgArr.size();
    fout.write((char*)&capity, sizeof(size_t));           // save mails count

    for (auto i{ 0 }; i < public_msgArr.size(); ++i)    // save mails array
        saveStr(public_msgArr[i], fout);

    capity = users_array.size();
    fout.write((char*)&capity, sizeof(size_t));            // save users count

    for (auto i{ 0 }; i < users_array.size(); ++i)      // save Users array
    {
        bool foo;
        Message* msg_arr;

        std::string str_out = users_array[i].getName();     // save login
        saveStr(str_out, fout);

        Hash hash_to_save = pass_table[str_out];
        saveHash(hash_to_save, fout);

        msg_arr = users_array[i].getMailboxPtr()->getMailsArray();
        capity = users_array[i].getMailboxPtr()->getCapity();
       
        fout.write((char*)&capity, sizeof(size_t)); // save Mailbox size

        for (auto j{ 0 }; j < capity; ++j) 
        {
            str_out = msg_arr[j].getAuthor();
            saveStr(str_out, fout);           // save name
            str_out = msg_arr[j].getMsg();
            saveStr(str_out, fout);           // save message text

            foo = msg_arr[j].getFlag();        
            fout.write((char*)&foo, sizeof(bool));  // save flag
        }
    }

    fout.close();
    return true;
}

bool Chat::load()
{
    std::ifstream fin(save_path, std::ios_base::binary);

    if (!fin.is_open()) // if file is not opened
        return false;

    size_t load_data_size;
    std::string load_data;

    fin.read((char*)&load_data_size, sizeof(size_t));

    for (auto i{ 0 }; i < load_data_size; ++i)
    {
        loadStr(load_data, fin);
        public_msgArr.push_back(load_data);
    }


    fin.read((char*)&load_data_size, sizeof(size_t));
    users_array.reserve(load_data_size);

    for (auto i{ 0 }; i < load_data_size; ++i)
    { 
        bool foo;
        size_t capity;
        std::string name, txt;
        Hash hash_to_load;

        loadStr(name, fin);
        users_array.emplace_back(name);

        loadHash(hash_to_load, fin);

        pass_table.emplace(std::make_pair(name, hash_to_load));
        
        fin.read((char*)&capity, sizeof(size_t));

        if (!capity)
            continue;

        for (auto j{ 0 }; j < capity; ++j)
        {
            loadStr(name, fin); 
            loadStr(txt, fin);
            fin.read((char*)&foo, sizeof(bool));

            Message msg_scan(txt, name);

            if (foo)
                msg_scan.setReaded();

            users_array[i].receiveMessage(msg_scan);
        }
    }

    fin.close();
    return true;
}

void Chat::saveStr(std::string& str, std::ofstream& fout)
{
    int size = sizeof(char) * str.length();

    fout.write((char*)&size, sizeof(int)); 
    fout.write(str.c_str(), size);
}

void Chat::loadStr(std::string& str, std::ifstream& fin)
{
    int size;

    fin.read((char*)&size, sizeof(int));
    str.resize(size / sizeof(char));
    fin.read((char*)str.c_str(), size);
}

void Chat::scr_load()
{
    system("cls");
    printf("\033[36m\n\n\n");
    printf("\t\t      Loadind data");

    for (auto i{ 0 }; i < 5; ++i)
    {
        mySleep(180);
        printf(".");
    }

    if (load())
    {
        mySleep(270);
        printf("\n\t\t       success\n");
        mySleep(520);
        clearLine();
    }
    else
    {
        mySleep(270);
        printf("\n\t\t        falue\n");
        mySleep(520);
        clearLine();
    }
    printf("\033[0m");
}

void Chat::saveHash(Hash& hash, std::ofstream& fout)
{
    fout.write((char*)&hash._part1, sizeof(uint));
    fout.write((char*)&hash._part2, sizeof(uint));
    fout.write((char*)&hash._part3, sizeof(uint));
    fout.write((char*)&hash._part4, sizeof(uint));
    fout.write((char*)&hash._part5, sizeof(uint));
}

void Chat::loadHash(Hash& hash, std::ifstream& fin)
{
    fin.read((char*)&hash._part1, sizeof(uint));
    fin.read((char*)&hash._part2, sizeof(uint));
    fin.read((char*)&hash._part3, sizeof(uint));
    fin.read((char*)&hash._part4, sizeof(uint));
    fin.read((char*)&hash._part5, sizeof(uint));
}