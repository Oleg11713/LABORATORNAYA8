#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

template<class T>
class Clock {
private:
	T hour;
	T minute;
	T second;
public:
	~Clock()
	{
		cout << "Объект удален!!!" << endl;
	}
	Clock()
	{
		hour = 0;
		minute = 0;
		second = 0;
	};
	Clock(T h, T m, T s)
	{
		hour = h;
		minute = m;
		second = s;
	}
	Clock(const Clock<T>& clock)
	{
		hour = clock.hour;
		minute = clock.minute;
		second = clock.second;
	}
	void changeHour(T ptr)
	{
		hour = ptr;
	}
	void changeMinute(T ptr)
	{
		minute = ptr;
	}
	void changeSecond(T ptr)
	{
		second = ptr;
	}
	T getHour()
	{
		return hour;
	}
	T getMinute()
	{
		return minute;
	}
	T getSecond()
	{
		return second;
	}
	void zadanie();
	void show();
	friend istream& operator>>(istream&, Clock<T>&);
	void operator+=(int);
};

template <class T>
void Clock<T>::zadanie()
{
	if (hour < 12)
		cout << "Данное время до полудня" << endl << endl;
	else if (hour == 12 && minute == 0 && second == 0)
		cout << "Полдень" << endl << endl;
	else cout << "Данное время после полудня" << endl << endl;
}

template <class T>
void Clock<T>::show()
{
	if (hour <= 9)
		cout << "0" << hour << ":";
	else cout << hour << ":";
	if (minute <= 9)
		cout << "0" << minute << ":";
	else cout << minute << ":";
	if (second <= 9)
		cout << "0" << second << endl;
	else cout << second << endl;
}

template<class T>
istream& operator>>(istream& in, Clock<T>& clock)
{
	in >> clock.hour;
	in >> clock.minute;
	in >> clock.second;
	return in;
}

int getInt();

template<class T>
void Clock<T>::operator+=(int second1)
{
	hour = hour + (second + second1) / 3600;
	minute = minute + ((second + second1) % 3600) / 60;
	second = ((second + second1) % 3600) % 60;
	while (second >= 60)
	{
		minute += 1;
		second = second - 60;
	}
	while (minute >= 60)
	{
		hour += 1;
		minute = minute - 60;
	}
	while (hour >= 24)
		hour = hour - 24;
	cout << "Получившееся время: ";
	show();
	system("pause");
}

template <class T1>
struct Status {
	T1* RealPtr;
	int Count;
};

template<class T1>
class SmartClock {
	Status<T1>* StatPtr;
public:
	T1* operator->()const {
		if (StatPtr) return StatPtr->RealPtr;
		else return NULL;
	}
	SmartClock(T1* ptr = 0) {
		if (!ptr) StatPtr = NULL;
		else {
			StatPtr = new Status<T1>;
			StatPtr->RealPtr = ptr;
			StatPtr->Count = 1;
		}
	}
	SmartClock(const SmartClock<T1>& p) :StatPtr(p.StatPtr) {
		if (StatPtr) StatPtr->Count++;
	}
	~SmartClock() {
		if (StatPtr) {
			StatPtr->Count--;
			if (StatPtr->Count <= 0) {
				delete StatPtr->RealPtr;
				delete StatPtr;
			}
		}
		cout << "Указатель удален" << endl;
	}
	SmartClock<T1>& operator=(const SmartClock<T1>& p) {
		if (StatPtr) {
			StatPtr->Count--;
			if (StatPtr->Count <= 0) {
				delete StatPtr->RealPtr;
				delete StatPtr;
			}
		}
		StatPtr = p.StatPtr;
		if (StatPtr) StatPtr->Count++;
		return *this;
	}
};


int menuMain();
template <class T1>
int menuChange(SmartClock<T1>&);
int getTime(int);

int main()
{
	setlocale(0, "rus");
	SmartClock<Clock<int>> pt1(new Clock<int>);
	SmartClock<Clock<int>> pt2 = pt1, pt3 = pt1;
	while (true)
	{
		int chooseMenu1 = menuMain();
		if (chooseMenu1 == 0)
		{
			while (true)
			{
				int chooseMenu2 = menuChange(pt1);
				if (chooseMenu2 == 0)
				{
					cout << "Введите часы: ";
					int ptr = getTime(24);
					pt1->changeHour(ptr);
					system("cls");
				}
				else
					if (chooseMenu2 == 1)
					{
						cout << "Введите минуты: ";
						int ptr = getTime(60);
						pt1->changeMinute(ptr);
						system("cls");
					}
					else
						if (chooseMenu2 == 2)
						{
							cout << "Введите секунды: ";
							int ptr = getTime(60);
							pt1->changeSecond(ptr);
							system("cls");
						}
						else
							if (chooseMenu2 == 3) break;
			}
		}
		else
			if (chooseMenu1 == 1)
			{
				pt2->show();
				system("pause");
			}
			else
				if (chooseMenu1 == 2)
				{
					pt2->show();
					pt2->zadanie();
					system("pause");
				}
				else
					if (chooseMenu1 == 3)
					{
						cout << "Введите, сколько секунд добавить к данному времени: ";
						int second1 = getInt();
						pt2->operator+=(second1);
					}
					else
						if (chooseMenu1 == 4) break;
	}
	return 0;
}

int menuMain()
{
	int choiceButton = 0, button = 0;
	system("cls");
	while (true)
	{
		choiceButton = (choiceButton + 5) % 5;

		if (choiceButton == 0) cout << " -> Изменить время" << endl;
		else cout << " Изменить время" << endl;

		if (choiceButton == 1) cout << " -> Посмотреть время" << endl;
		else cout << " Посмотреть время" << endl;

		if (choiceButton == 2) cout << " -> Определить после полудня или до полудня данное время" << endl;
		else cout << " Определить после полудня или до полудня данное время" << endl;

		if (choiceButton == 3) cout << " -> Добавить к данному времени секунды" << endl;
		else cout << " Добавить к данному времени секунды" << endl;

		if (choiceButton == 4) cout << " -> Выход" << endl;
		else cout << " Выход" << endl;

		button = _getch();
		if (button == 224)
		{
			button = _getch();
			if (button == 72) choiceButton--;
			if (button == 80) choiceButton++;
		}
		if (button == 13) {
			system("cls");
			return choiceButton;
		}
		system("cls");
	}
}

template <class T1>
int menuChange(SmartClock<T1>& obj)
{
	int choose_menu = 0, keyboard_button = 0;
	while (true) {
		choose_menu = (choose_menu + 4) % 4;

		if (choose_menu == 0) { cout << " -> Часы: " << obj->getHour() << endl; }
		else cout << " Часы: " << obj->getHour() << endl;

		if (choose_menu == 1) { cout << " -> Минуты: " << obj->getMinute() << endl; }
		else cout << " Минуты: " << obj->getMinute() << endl;

		if (choose_menu == 2) { cout << " -> Секунды: " << obj->getSecond() << endl; }
		else cout << " Секунды: " << obj->getSecond() << endl;

		if (choose_menu == 3) { cout << " -> Выйти в главное меню " << endl; }
		else cout << " Выйти в главное меню " << endl;


		keyboard_button = _getch();
		if (keyboard_button == 224) {
			keyboard_button = _getch();
			if (keyboard_button == 72) choose_menu--;
			if (keyboard_button == 80) choose_menu++;
		}
		if (keyboard_button == 13) { system("cls"); return choose_menu; }
		system("cls");
	}
}

int getTime(int c) {
	string numbers;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (numbers.length() != 0) {
					cout << '\b' << " " << '\b';
					numbers.erase(numbers.length() - 1);
				}
			}
			else
				if (key == 13 && numbers.length() != 0 && stoi(numbers) < c) break;
				else
					if (key >= '0' && key <= '9') {
						numbers = numbers + (char)key;
						cout << (char)key;
					}
	}
	cout << endl;
	return stoi(numbers);
}

int getInt() {
	string numbers;
	while (true) {
		int key;
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		else
			if (key == 8) {
				if (numbers.length() != 0) {
					cout << '\b' << " " << '\b';
					numbers.erase(numbers.length() - 1);
				}
			}
			else
				if (key == 13 && numbers.length() != 0) break;
				else
					if (key >= '0' && key <= '9') {
						numbers = numbers + (char)key;
						cout << (char)key;
					}
	}
	cout << endl;
	return stoi(numbers);
}
