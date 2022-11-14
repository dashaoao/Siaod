#include "Bsearch_tree.h"
#include "AVL_tree.h"
#include <string>
#include "binar_file.h"

void binar_menu()
{
    binar_file bfile = binar_file();
    cout << "Выберете действие с файлом:\n1.Перевести в бинарный\n2.Вывести файл\n3.Удалить по ключу\n4.Добавить элемент\n5.Выйти\n";
    while (true)
    {
        char choose;
        cout << "Операция:\t";
        cin >> choose;
        if (choose == '1')
        {
            string line = "";
            string buf = "";
            cout << "Введите название файла\n";
            while (line == "")
            {
                getline(cin, line);
                buf += line;
            }
            cout << "Введите название будущего бинарного файла\n";
            string name;
            while (name == "")
                getline(cin, name);
            if (bfile.text_to_binar(buf, name))
                cout << "Бинарный файл создан\n";
            cin.clear();
        }
        else if (choose == '2')
        {
            cout << "Введите название бинарного файла\n";
            string name = "";
            while (name == "")
                getline(cin, name);
            bfile.print_file(name);
        }
        else if (choose == '3')
        {
            cout << "Введите название бинарного файла\n";
            string name = "";
            while (name == "")
                getline(cin, name);
            cout << "Введите ключ удаляемого элемента\n";
            string key = "";
            getline(cin, key);
            if (bfile.delete_by_key(name, key))
                cout << "Элемент удален\n";
        }
        else if (choose == '4')
        {
            cout << "Введите название бинарного файла\n";
            string name;
            while (name == "")
                getline(cin, name);
            cout << "Введите информацию о записи:\t";
            business st;
            cin >> st.license;
            cin >> st.name;
            cin >> st.founder;
            if (bfile.insert_element(name, st))
                cout << "Элемент добавлен\n";
        }
        else if (choose == '5')
        {
            return;
        }
        else cout << "Попробуйте снова\n";
    }
}

void bsearch_menu()
{
    Bsearch_tree tree;
    cout << "Выберите действие с бинарным деревом:\n1.Построить дерево по файлу\n2.Вывести дерево\n3.Поиск по ключу\n4.Добавление элемента\n5.Удаление по ключу\n6.Выйти\n";
    char c;
    while (true)
    {
        cout << "Операция:\t";
        cin >> c;
        if (c == '1')
        {
            tree = Bsearch_tree();
            cout << "Введите название бинарного файла\n";
            string name;
            cin >> name;
            if (tree.build_tree(name))
            {
                cout << "Дерево построено\n";
            }
            else cout << "Попробуйте снова\n";
        }

        else if (c == '2')
        {
            tree.print_tree();
        }
        else if (c == '3')
        {
            cout << "Введите ключ для поиска\n";
            string license = "";
            cin >> license;
            business found = tree.find(license);
            if (found.license[0] == '-' && found.license[1] == '1')
                cout << "Элемент не найден\n";
            else
                cout << "Элемент найден:\t" << found.license << " " << found.founder << " " << found.name << endl;
        }
        else if (c == '4')
        {
            string license;
            binar_file bfile = binar_file();
            cout << "Введите информацию о записи:\t";
            business st;
            cin >> st.license;
            license = st.license;
            cin >> st.name;
            cin >> st.founder;
            if (bfile.insert_element(tree.get_file_name(), st))
            {
                tree.insert(license);
                binar_file bin = binar_file();
                cout << "Элемент добавлен\n";
            }
        }
        else if (c == '5')
        {
            cout << "Введите ключ для удаления\n";
            string license = "";
            cin >> license;
            if (tree.erase(license))
                cout << "Элемент удален\n";
            else cout << "Элемент не найден\n";
        }
        else if (c == '6')
        {
            return;
        }
        else
        {
            cout << "Попробуйте снова\n";
        }
    }
}

void AVL_menu()
{
    AVL_tree tree;
    cout << "Выберите действие с АВЛ-деревом:\n1.Построить дерево по файлу\n2.Вывести дерево\n3.Добавить элемент\n4.Удалить элемент по ключу\n5.Найти элемент\n6.Выйти\n";
    char c;
    while (true)
    {
        cout << "Операция:\t";
        cin >> c;
        if (c == '1')
        {
            tree = AVL_tree();
            cout << "Введите название бинарного файла\n";
            string name;
            cin >> name;
            cout << endl;
            if (tree.build_tree(name))
            {
                cout << "Дерево построено!\n";
            }
            else cout << "Неверное имя файла\n";
        }
        else if (c == '2')
        {
            tree.print_tree();
        }
        else if (c == '3')
        {
            cout << "Введите ключ:\n";
            string license;
            cin >> license;
            tree.insert(license);
            cout << "Элемент добавлен\n";
        }
        else if (c == '4')
        {
            cout << "Введите ключ для удаления\n";
            string license = "";
            cin >> license;
            if (tree.erase(license)) {
                cout << "Элемент удален\n";
            }
            else cout << "Элемент не найден\n";
        }
        else if (c == '5')
        {
            cout << "Введите ключ для поиска\n";
            string license = "";
            cin >> license;
            if (tree.find_by_key(license))
                cout << "Элемент найден\n";
            else cout << "Элемент не найден\n";
        }
        else if (c == '6')
        {
            return;
        }
        else
        {
            cout << "Попробуйте снова\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    char c;
    while (true)
    {
        cout << "Выберите с чем будем работать:\n1 Бинарный файл \n2.Бинарное дерево поиска\n3.АВЛ-дерево\n4.Выйти\n";
        cout << "Операция:\t";
        cin >> c;
        switch (c)
        {
        case '1':
            binar_menu();
            break;
        case '2':
            bsearch_menu();
            break;
        case '3':
            AVL_menu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "Попробуйте еще раз\n";
            break;
        }
    }
}
