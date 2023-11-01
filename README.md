<h1>Итоговый проект по модулю Основные конструкции C++</h1>
<h3>Создатель: Василий Тац</h3>

<h1>Классы</h1>

<h3>Message</h3>
- Класс сообщения. <br />
- Содержит 3 поля: имя автора(string), текст сообщения(string), отчет о прочтении(bool).<br />

	std::string getMsg()  
                          // возвращает строку(string) с текстом сообщения
	std::string getAuthor()
                          // возвращает строку(string) с именем автора сообщения
	bool getFlag()
                          // возвращает значение переменой Flag. Если сообщение не было прочитано, то false, иначе true
	void setReaded()
                          // присваивает переменной Flag значение true
                          
<h3>Mailbox</h3>
- Класс почтового ящика.<br />
- Содержит 3 поля: массив элементов класса Message (Message*), размер почтового ящика (int), текущее заполнение(int).<br />
- Предстваляет собой буфер, который хранит последние "размер почтового ящика" сообщений.<br />

	int getCapity()        
                            // возвращает текущее количетво сообщений
	int getUnreadCnt()
                            // возвращает количество непрочитанных сообщений
	Message* getMailsArray()
                            // возвращает указетель на массив объектов типа Message
	void addMessage(Message msg)
                           // добавляет объект класса Message в массив
	bool getMessage(Message& msg, int position = 0)
                           // пробует записать объект класса Message из внутреннего массива по позиции position в переменную объекта класса Message msg
                           // возвращет true если записть прошла успешно, иначе false

<h3>User</h3>
- Класс пользовалеля<br />
- Содержит 3 поля: логин (string), пароль (string), объект класса Mailbox. <br />

	int getMessageCnt()
                                    // возвращет количество сообщений(Message) в почтовом ящике(Mailbox)пользователя
	std::string getName()
                                    // возвращает имя пользователя
	Mailbox* getMailboxPtr()
                                    // возврящает указаель на оъект класса Mailbox
	bool checkPass(std::string pass)
                                    // сравнивает строку(string) pass со строкой(string), хранящей пароль пользователя
                                    // возврящает true если строки совпадают, иначе false
	void init(std::string name, std::string pass)
                                    //
	void sendMessage(std::string message, User& target)
                                    // принимает строку(string) message, создает сообщение(объект класса Message) и отправляет его пользователю(User)
	void receiveMessage(Message msg)
                                    // записывает сообщение(Message) msg в почтовый ящик

<h3>Chat</h3>
- Класс программы чата <br />
- Содержит 10 полей:  <br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* идентификатор текущего экрана (переменная типа пользовательского перечисления (enum)) <br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* идентификатор предыдущего экрана (переменная типа пользовательского перечисления (enum)) <br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* путь к файлу сохранения
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* буфер сообщений общего чата (массив элементов типа string)<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* массив пользователей (элементов типа User)<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* позиция текущего пользователя<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* количество пользователей чата<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* количество сообщений в буфере общего чата<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* размер массива пользователей<br />
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* размер буфера сообщений общего чата<br />
- Чат имеет набор рабочих экранов (функции печати экрана в консоль), и фунцию обработки вводимых данных<br />
&nbsp;&nbsp;&nbsp;Пользователь может перемещаться между рабочими экранами с помощью консольных команд чата<br />

	private:
	  void scr_newAccount();
                            // экран регистрации нового пользователя
	  void scr_welcome();
                            // экран пиветствия
	  void scr_login();
                            // экран входа пользователя
	  void scr_exit();
                            // экран выхода из программы
	  void scr_private()
                            // экран приватных сообщений
	  void scr_commands()
                            // экран со списком консольных команд чата
	  void scr_profile()
                            // экран профиля пользовалеля (личные сообщения приходят в профиль)
	  void scr_public()
                            // экран общего чата для всех пользователей
	  void scr_load()
                            // экран отображения состояния загрузки сохранения из файла
	  void scr_message(Message& m)
                            // экран просмотра личного сообщения (показывает сообщение целиком)
	  bool save()
	                    // сохранение в бинарный файл при выходе из чата через коменду \close
		            // возвращает true если сохранение прошло успешно, иначе false
	  bool load()
                            // загрузка данных из бинарного файла при запуске программы чата
		            // возвращает true если загрузка прошла успешно, иначе false
	  void showHistory()
                            // печать истории сообщений публичного чата
	  void showMailbox()
                            // печатает список личных сообщений
	  void showUsers()
                            // печатает список пользователей
	  void clearLine()
                            // перевод каретки на строку вверх, очистка строки, перемещение каретки в начало строки
	  void cmdProcessing()
                            // обработчик всего вводимого текста из консоли (поиск команд во вводимой строке, управляющая сменой экранов фунция)
	  void myCinClear()
                            // ручная очистка мусора из буфера ввода (нужно для корректной работы std::getline())
	  void rememberMail(std::string str)
                            // сохранение сообщения общего чата в архив
	  void mySleep(int time = 120)
                            // тормозит поток выполнения программы на time миллисекунд
	  void cmd_default(std::string& str)
                            // блок кода с обработкой команд, работающих на любом экране (часть обработчика вводимого текса cmdProcessing())
	  void saveStr(std::string& str, std::ofstream& fout)
                            // функция сохранения строки(string) в файл. используется в save()
	  void loadStr(std::string& str, std::ifstream& fin)
                            // функция загрузки строки(string) из файла. используется в load()
	  bool findUser(std::string name, int& pos)
                            // поиск пользователя по имени name, если пользователь найден, то записывает его позицию в массиве в переменную pos
                            // возвращает true если пользователь найден, иначе false
	  bool strCmp_read(std::string& str, int& num)
                            // строковый компилятор для команды \read N (где N номер сообщения)
                            // анализ входящей строки str, если строка соответствует виду команды, то в переменную num записывается число, полученное при анализе строки
                            // возвращает true если анализ входящей строки прошел успешно, иначе false
	  bool strCmp_pm(std::string& str_cmd, std::string& str_msg)
                            // строковый компилятор для отправки приватных сообщений \login text (где login - имя пользователя, text -текст сообщения)
                            // Принимает на вход строку str_cmd. Анализ входящей строки str_cmd, если строка соответствует виду команды,
                            // то в переменную str_cmd будет записано предполагаемое имя пользователя, а в переменную str_msg текст сообщения
                            // возвращает true если анализ входящей строки прошел успешно, иначе false
	public:
	  void start()
                            // запуск чата
	  void addUser(User& u)
                            // добавить пользователя в чат (может генерировать исключения)