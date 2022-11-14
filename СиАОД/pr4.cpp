#include "Bsearch_tree.h"
#include "AVL_tree.h"
#include <string>
#include "binar_file.h"

void binar_menu()
{
    binar_file bfile = binar_file();
    cout << "�������� �������� � ������:\n1.��������� � ��������\n2.������� ����\n3.������� �� �����\n4.�������� �������\n5.�����\n";
    while (true)
    {
        char choose;
        cout << "��������:\t";
        cin >> choose;
        if (choose == '1')
        {
            string line = "";
            string buf = "";
            cout << "������� �������� �����\n";
            while (line == "")
            {
                getline(cin, line);
                buf += line;
            }
            cout << "������� �������� �������� ��������� �����\n";
            string name;
            while (name == "")
                getline(cin, name);
            if (bfile.text_to_binar(buf, name))
                cout << "�������� ���� ������\n";
            cin.clear();
        }
        else if (choose == '2')
        {
            cout << "������� �������� ��������� �����\n";
            string name = "";
            while (name == "")
                getline(cin, name);
            bfile.print_file(name);
        }
        else if (choose == '3')
        {
            cout << "������� �������� ��������� �����\n";
            string name = "";
            while (name == "")
                getline(cin, name);
            cout << "������� ���� ���������� ��������\n";
            string key = "";
            getline(cin, key);
            if (bfile.delete_by_key(name, key))
                cout << "������� ������\n";
        }
        else if (choose == '4')
        {
            cout << "������� �������� ��������� �����\n";
            string name;
            while (name == "")
                getline(cin, name);
            cout << "������� ���������� � ������:\t";
            business st;
            cin >> st.license;
            cin >> st.name;
            cin >> st.founder;
            if (bfile.insert_element(name, st))
                cout << "������� ��������\n";
        }
        else if (choose == '5')
        {
            return;
        }
        else cout << "���������� �����\n";
    }
}

void bsearch_menu()
{
    Bsearch_tree tree;
    cout << "�������� �������� � �������� �������:\n1.��������� ������ �� �����\n2.������� ������\n3.����� �� �����\n4.���������� ��������\n5.�������� �� �����\n6.�����\n";
    char c;
    while (true)
    {
        cout << "��������:\t";
        cin >> c;
        if (c == '1')
        {
            tree = Bsearch_tree();
            cout << "������� �������� ��������� �����\n";
            string name;
            cin >> name;
            if (tree.build_tree(name))
            {
                cout << "������ ���������\n";
            }
            else cout << "���������� �����\n";
        }

        else if (c == '2')
        {
            tree.print_tree();
        }
        else if (c == '3')
        {
            cout << "������� ���� ��� ������\n";
            string license = "";
            cin >> license;
            business found = tree.find(license);
            if (found.license[0] == '-' && found.license[1] == '1')
                cout << "������� �� ������\n";
            else
                cout << "������� ������:\t" << found.license << " " << found.founder << " " << found.name << endl;
        }
        else if (c == '4')
        {
            string license;
            binar_file bfile = binar_file();
            cout << "������� ���������� � ������:\t";
            business st;
            cin >> st.license;
            license = st.license;
            cin >> st.name;
            cin >> st.founder;
            if (bfile.insert_element(tree.get_file_name(), st))
            {
                tree.insert(license);
                binar_file bin = binar_file();
                cout << "������� ��������\n";
            }
        }
        else if (c == '5')
        {
            cout << "������� ���� ��� ��������\n";
            string license = "";
            cin >> license;
            if (tree.erase(license))
                cout << "������� ������\n";
            else cout << "������� �� ������\n";
        }
        else if (c == '6')
        {
            return;
        }
        else
        {
            cout << "���������� �����\n";
        }
    }
}

void AVL_menu()
{
    AVL_tree tree;
    cout << "�������� �������� � ���-�������:\n1.��������� ������ �� �����\n2.������� ������\n3.�������� �������\n4.������� ������� �� �����\n5.����� �������\n6.�����\n";
    char c;
    while (true)
    {
        cout << "��������:\t";
        cin >> c;
        if (c == '1')
        {
            tree = AVL_tree();
            cout << "������� �������� ��������� �����\n";
            string name;
            cin >> name;
            cout << endl;
            if (tree.build_tree(name))
            {
                cout << "������ ���������!\n";
            }
            else cout << "�������� ��� �����\n";
        }
        else if (c == '2')
        {
            tree.print_tree();
        }
        else if (c == '3')
        {
            cout << "������� ����:\n";
            string license;
            cin >> license;
            tree.insert(license);
            cout << "������� ��������\n";
        }
        else if (c == '4')
        {
            cout << "������� ���� ��� ��������\n";
            string license = "";
            cin >> license;
            if (tree.erase(license)) {
                cout << "������� ������\n";
            }
            else cout << "������� �� ������\n";
        }
        else if (c == '5')
        {
            cout << "������� ���� ��� ������\n";
            string license = "";
            cin >> license;
            if (tree.find_by_key(license))
                cout << "������� ������\n";
            else cout << "������� �� ������\n";
        }
        else if (c == '6')
        {
            return;
        }
        else
        {
            cout << "���������� �����\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    char c;
    while (true)
    {
        cout << "�������� � ��� ����� ��������:\n1 �������� ���� \n2.�������� ������ ������\n3.���-������\n4.�����\n";
        cout << "��������:\t";
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
            cout << "���������� ��� ���\n";
            break;
        }
    }
}
