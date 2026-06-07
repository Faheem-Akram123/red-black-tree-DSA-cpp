#include "redBlackTree.h"
void showMenu()
{
    cout << "\nRed-Black Tree Menu" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout << "4. Inorder Traversal" << endl;
    cout << "5. Preorder Traversal" << endl;
    cout << "6. Postorder Traversal" << endl;
    cout << "8. Exit" << endl;
}

int main()
{
    redBlackTree tree;
    int choice;

    while (true)
    {
        showMenu();
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            int value;
            cout << "Enter Value for Insertion : ";
            cin >> value;
            tree.insert(value);
        }
        else if (choice == 2)
        {
            int value;
            cout << "Enter Value to remove : ";
            cin >> value;
            tree.deleteValue(value);
        }
        else if (choice == 3)
        {
            int value;
            cout << "Enter Value for search : ";
            cin >> value;

            if (tree.searchValue(value))
            {
                cout << "Value found" << endl;
            }
            else
            {
                cout << "Value not found" << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "Inorder: ";
            tree.inorderDisplay();
        }
        else if (choice == 5)
        {
            cout << "Preorder: ";
            tree.preorderDisplay();
        }
        else if (choice == 6)
        {
            cout << "Postorder: ";
            tree.postorderDisplay();
        }
        else if (choice == 7)
        {
            cout << "Exiting program." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please select 1 to 8." << endl;
        }
    }

    return 0;
}
