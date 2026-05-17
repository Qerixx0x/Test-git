#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;
struct student {
	char LastName[20];
	char FirstName[20];
	char SecondName[20];
	int Age;
	int FacultyСode;
	int CourseNum;
	int GroupNum;
	double Mark;
	void StudentInput() {
		cout << "Введите фамилию: ";
		cin >> LastName;
		cout << "Введите имя: ";
		cin >> FirstName;
		cout << "Введите отчество: ";
		cin >> SecondName;
		cout << "Введите возраст: ";
		cin >> Age;
		cout << "Введите код факультета: ";
		cin >> FacultyСode;
		cout << "Введите номер курса: ";
		cin >> CourseNum;
		cout << "Введите номер группы: ";
		cin >> GroupNum;
		cout << "Введите средний балл: ";
		cin >> Mark;
	}
	void voice(int i) {
		cout << "| " << left << setw(3) << i
			<< "| " << setw(14) << LastName
			<< "| " << setw(14) << FirstName
			<< "| " << setw(14) << SecondName
			<< "| " << setw(8) << Age
			<< "| " << setw(8) << FacultyСode
			<< "| " << setw(5) << CourseNum
			<< "| " << setw(9) << GroupNum
			<< "| " << setw(8) << fixed << setprecision(2) << Mark << " |" << endl;
	}
};
student* CreateStudentFile(const string& fileName, int& n) {
	ofstream OutFile(fileName, ios::binary);
	if (!OutFile) {
		cerr << "Ошибка создания файла.\n";
		return 0;
	}
	cout << "Введите количество студентов: ";
	cin >> n;
	student* students = new student[n];
	for (int i = 0; i < n; i++) {
		cout << "\nСтудент №" << i + 1 << endl;
		student Stu;
		Stu.StudentInput();
		students[i] = Stu;
		OutFile.write((char*)students, sizeof(student));
	}
	OutFile.close();
	return students;
}
void PrintData(student* students, int n) {
	if ( n == 0) {
		cout << "Нет данных о студентах.\n";
		return;
	}
	cout << "\n" << string(107, '-') << endl;
	cout << "| №  | Фамилия       | Имя           | Отчество      | Возр  | Фак-код  | Курс  | Группа | Ср. балл |" << endl;
	cout << string(107, '-') << endl;

	for (int i = 0; i < n; i++) {
		students[i].voice(i + 1);
	}

	cout << string(107, '-') << endl;
}
void Add( student* students, int& n) {
	student Stu;
	cout << "\nДобавление нового студента:\n";
	Stu.StudentInput();
	student* newStudents = new student[n + 1];
	for (int i = 0; i < n; i++) {
		newStudents[i] = students[i];
	}
	newStudents[n] = Stu;
	n++;

	delete[] students;
	students = newStudents;
	
}
void MenuPrint() {
	cout << "\n=== Меню ===\n";
	cout << "1. Создать файл\n";
	cout << "2. Просмотр содержимого\n";
	cout << "3. Добавить запись\n";
	cout << "4. Удалить запись (по номеру)\n";
	cout << "5. Корректировка записи (по номеру)\n";
	cout << "6. Индивидуальное задание\n";
	cout << "0. Выход\n";
	cout << "Ваш выбор: ";
}
void Delete( student* students, int& n) {
	if (n == 0) {
		cout << "Массив пуст.\n"; 
	}
	int num;
	cout << "Введите номер записи для удаления: ";
	cin >> num;
	if (num < 1 or num > n) {
		cout << "Неверный номер.\n";  
	}
	student* newStudents = new student[n - 1];
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (i != (num - 1)) {
			newStudents[index] = students[i];
			index++;
		}
	}
	n--;
	delete[] students;
	students = newStudents;
}
void Edit( student* students, int n) {
	if (n == 0) {
		cout << "Массив пуст.\n"; 
		return;
	}
	int num;
	cout << "Введите номер записи для корректировки: ";
	cin >> num;
	if (num < 1 or num > n) { cout << "Неверный номер.\n"; return; }
	cout << "Введите новые данные: \n";
	students[num - 1].StudentInput();
}
void Task(student* students, int n) {
	if (n == 0) {
		cout << "Массив пуст.\n"; 
		return; 
	}
	int num;
	cout << "Введите номер курса: ";
	cin >> num;
	ofstream Out("do_task.txt");
	bool found = false;
	for (int i = 0; i < n; i++) {
		if (students[i].CourseNum == num and students[i].Mark >= 9) {
			Out << students[i].LastName << " " << students[i].FirstName << " " << students[i].SecondName << endl;
			found = true;
		}
	}
	Out.close();
	if (found) {
		cout << "ФИО отличников сохранены в файл do_task.txt\n";
	}
	else {
		cout << "Отличники на " << num << " курсе не найдены.\n";
	}
}
void save(const string& fileName, student* students, int n) {
	ofstream Out(fileName, ios::binary | ios::trunc);
	if (!Out) {
		cerr << "Ошибка создания файла.\n";
	}
	if (n > 0) {
		Out.write((char*)students, sizeof(student) * n);
	}
	Out.close();
}
void Menu(const string& fileName) {
	int choice;
	student* currentStudents = nullptr;
	int studentsCount = 0;
	do {
		MenuPrint();
		cin >> choice;
		switch (choice) {
		case 1:
			currentStudents = CreateStudentFile(fileName, studentsCount);
			break;
		case 2:
			PrintData(currentStudents, studentsCount);
			break;
		case 3:
			Add( currentStudents, studentsCount);
			break;
		case 4:
			Delete(currentStudents, studentsCount);
			break;
		case 5:
			Edit(currentStudents, studentsCount);
			break;
		case 6:
			Task(currentStudents, studentsCount);
			break;
		case 0:
			return;
		}

	} while (choice != 0);
	save(fileName, currentStudents, studentsCount);
	return;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	const string fileName = "test.bin";
	Menu(fileName);
}
