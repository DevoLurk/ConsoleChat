#include<iostream>
#include"Chat.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

/* 
    User u1("ddd", "123");
    User u2("qwe", "qwe");
    User u3("qwe", "qwe");
    User u4("qwe2", "qwe");
    User u5("qwe3", "qwe");
    User u6("qwe4", "qwe");

    Message m1("Helloo", "Nina");
    Message m2("How are you?", "Nina");
    Message m3("I was in the libruary yesturday. There where to many books for my project. Can you come with to help?", "Nina");
    Message m4("When you borrow me your psp?", "Diman");
    Message m5("Lets go fishing on wednesday. I foud a new place.", "Vadim");
    Message m6("Bro, I need 100 dollars for my new clothes. Bro please, I whanted it for too long", "Diman");
    Message m7("I whant to make the biggest pizza in the world", "Bro12342342bro");

    m6.setReaded();
    m5.setReaded();

    u1.receiveMessage(m1);
    u1.receiveMessage(m2);
    u1.receiveMessage(m3);
    u1.receiveMessage(m4);
    u1.receiveMessage(m5);
    u1.receiveMessage(m6);
    u2.receiveMessage(m7);
*/

    Chat chat;
 /*
   try
    {
        chat.addUser(u1);
        chat.addUser(u2);
        chat.addUser(u4);
        chat.addUser(u5);
        chat.addUser(u6);
    }
    catch (exception& e)
    {
        printf("\033[31m %s \033[0m \n", e.what());
    }
*/
    chat.start();

    return 0;
}
