//Написать компьютерную программу, содержащую
//  - Описание структуры, содержащей поля типа string, int, double;
//  - Набор функций для работы со списком на базе этой структуры:
//  - Добавление элемента в начало списка;
//  - Добавление элемента в конец списка;
//  - Добавление элемента в список после заданного элемента;
//- Добавление элемента в список перед заданным элементом;
//  - Удаление из списка элемента с заданным именем;
//  - Вывод содержания списка на экран;
//  - Функцию main, содержащую сценарий работы со списком, использующий разработанный инструментарий.

#include <iostream>

using namespace std;

struct Student
{
    string name; //имя
    int age; //возраст
    double scholarship; //стипендия (до копеек)
    Student *next; //указатель на следующий элемент списка
};

//функция создания экземпляра студента по его атрибутам
Student *createStudent(string name, int age, double scholarship)
{
    Student *student = new Student();
    student->name = name;
    student->age = age;
    student->scholarship = scholarship;
    student->next = NULL;
    return student;
}

//добавляет студента на первую позицию в списке
void addFirst(Student *&head, Student *student)
{
    student->next = head;
    head = student;
}

//добавление в конец списка
void addLast(Student *&head, Student *student)
{
    if (head == NULL) //если элементов нет
    {
        addFirst(head, student);
    }
    else
    {
        Student *tmp = head;
        while (tmp->next != NULL) //находим указатель на последний элемент
        {
            tmp = tmp->next;
        }

        tmp->next = student; //последний становится предпоследним, указывает на добавляемый
        //student->next = NULL; //для безопасности
    }
}

//добавление после заданного по имени
int addAfter(Student *head, string name, Student *student)
{
    if(head == NULL)
    {
        return 1; //ошибка список пуст
    }

    Student *tmp = head;
    while(tmp != NULL) //перебор студентов
    {
        if(tmp->name == name) //условие нахождения имени
            break;
        tmp = tmp->next;
    }

    if(tmp == NULL) //если такого имени нет
        return 2;

    student->next = tmp->next;
    tmp->next = student;
    return 0;
}

//добавление перед заданным по имени
int addBefore(Student *&head, string name, Student *student)
{
    if(head == NULL)
    {
        return 1; //ошибка список пуст
    }

    Student *tmp = head;
    if(tmp->name == name) //добавление на первое место списка
    {
        addFirst(head, student);
        return 0;
    }

    if (head->next == NULL) //у единственного элемента нет нужного имени
        return 2;

    Student *prev = head;
    tmp = head->next;
    while (tmp != NULL)
    {
        if (tmp->name == name)
        {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) //нет такого имени
        return 3;

    prev->next = student;
    student->next = tmp;
    return 0;
}

//удалить по имени
int deleteByName(Student *&head, string name)
{
    if(head == NULL)
    {
        return 1; //ошибка список пуст
    }

    Student *tmp = head;
    if(tmp->name == name) //если голова указывает на нужное имя, сразу удаляем
    {
        head = tmp->next;
        delete tmp;
        return 0;
    }
    if (head->next == NULL) //если единственный элемент не подходит
        return 2;

    Student *prev = tmp;
    tmp = head->next;
    while (tmp != NULL)
    {
        if(tmp->name == name)
        {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) //отсутствие имени
    {
        return 3;
    }

    prev->next = tmp->next; //перед удалением связываем крайние элементы
    delete tmp;
    return 0;
}

//печать списка
void print(Student *head)
{
    if (head == NULL)
    {
        cout << "Students list is empty" << endl;
        return;
    }

    cout << "Students list:" << endl;

    Student *tmp = head;
    while (tmp != NULL)
    {
        cout << "name = " << tmp->name << " age = " << tmp->age << " scholarship = " << tmp->scholarship << endl;
        tmp = tmp->next;
    }
    cout << endl;
}

//функция удаления списка студентов
void deleteStudents(Student *&head)
{
    Student *tmp; //временный указатель на удаляемого студента

    while (head != NULL) //пока есть элементы
    {
        tmp = head; //прихраниваем указатель на текущий первый элемент
        head = tmp->next; //головой назначаем следующий
        delete tmp; //удаляем текущий элемент
    }
    //head = NULL; //список пуст
}

int main()
{
    int error;
    Student *head = NULL; //указатель на начало списка студентов

    addFirst(head, createStudent("Vasya", 17, 6548.11));
    print(head);

    addFirst(head, createStudent("Olya", 20, 7483.12));
    addLast(head, createStudent("Petya", 19, 15032.07));
    print(head);

    error = addAfter(head, "Olya", createStudent("Kolya", 16, 4349.87));
    if(error == 1)
    {
        cout << "the list is empty" << endl;
    }
    else if (error == 2)
    {
        cout << "no such name found" << endl;
    }
    print(head);

    error = deleteByName(head, "Vasya");
    if(error == 1)
    {
        cout << "the list is empty" << endl;
    }
    else if (error == 2)
    {
        cout << "the only elem doesn't have such name" << endl;
    }
    else if (error == 3)
    {
        cout << "no such name found" << endl;
    }
    print(head);

    error = addBefore(head, "Petya", createStudent("Zhenya", 18, 3278.43));
    if(error == 1)
    {
        cout << "the list is empty" << endl;
    }
    else if (error == 2)
    {
        cout << "the only elem doesn't have such name" << endl;
    }
    else if (error == 3)
    {
        cout << "no such name found" << endl;
    }
    print(head);

//    addAfter(head, "Kolya", createStudent("Oleg", 20, 38940.90));
//    print(head);

    deleteStudents(head); //удаляем список

    print(head);

    return 0;
}
