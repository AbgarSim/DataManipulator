#include <iostream>
#include <cstring>
#include "Data.cpp"
#include <limits>

using namespace std;
data iDSearch(int serchById);
void clearBuffer(); //Clears buffer after cin
void printStructLine(data prop); //Prints a property
void addItem(data item);  //Adds a property to a file and calculates its ID
void input(); //Inputs the property into a file (uses addItem method)
void listAll(); //Displays all of the file contents
void removeLine(int ID); //Removes a struct with a specific ID
data findLine(char *name); //Finds a struct by name
void edit(int ID, data property); //Edits property with a specific ID
void executeEdit();
int main() {
    int n;
    cout << "Hello, This is menu!" << endl;
    menu:
    cout << "Make you're choice" << endl;
    cout << "1)List all products" << endl;
    cout << "2)Find a product by name" << endl;
    cout << "3)Add a product" << endl;
    cout << "4)Edit a product" << endl;
    cout << "5)Remove a product" << endl;
    cout << "6)Exit" << endl;

    cin >> n;
    clearBuffer();

    switch (n) {
        case 1:
            listAll();
            goto menu;
        case 2: char name[20];
            cout << "Enter name to findLine line" << endl;
            cin >> name;
            clearBuffer();
            printStructLine(findLine(name));
            goto menu;
        case 3:
            input();
            listAll();
            goto menu;
        case 4:
            executeEdit();
            listAll();
            goto menu;
        case 5:
            int ID;
            cout << "Enter line ID to removeLine " << endl;
            cin >> ID;
            removeLine(ID);
            goto menu;
        case 6:
            return 0;
        default:
            cout << "Please select from menu" << endl;
            main();
    }
    return 0;
}

void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
} //Clears buffer after cin
void printStructLine(data prop) {
    printf("  %d. %-30s * %-30s *\n", prop.ID, prop.name, prop.description);
} //Prints a property
void addItem(data item) {
    FILE *fileStream = fopen("data", "a+");
    if (fileStream == NULL) {
        cout << "Can't open file to write" << endl;
    } else {
        data last;
        fseek(fileStream, -sizeof(item), SEEK_END);
        fread(&last, sizeof(last), 1, fileStream);
        item.ID = (last.ID > 0) ? last.ID + 1 : 1;
        fwrite(&item, sizeof(item), 1, fileStream);
    }
    fclose(fileStream);
} //Adds a property to a file and calculates its ID
void input() {
    string inputName;
    string inputDescription;
    data dataLine;


    cout << "Enter name:" << endl;
    getline(cin, inputName);
    strcpy(dataLine.name, inputName.c_str());

    cout << "Enter description:" << endl;
    getline(cin, inputDescription);
    strcpy(dataLine.description, inputDescription.c_str());
    addItem(dataLine);
}//Inputs the property into a file (uses addItem method)
void listAll() {
    int f = 0, k = 0;
    data dataLine;
    FILE *fileStream = fopen("data", "r");
    if (fileStream == NULL) {
        cout << "not found" << endl;
    } else {
        while (!feof(fileStream)) {
            fread(&dataLine, sizeof(dataLine), 1, fileStream);
            if (feof(fileStream)) break;
            if (dataLine.ID > 0) {
                if (f == 0) {
                    f = 1;
                    printf("%-10s%-30s%13s\n", "ID", "Name", "Description");
                }
                printStructLine(dataLine);
                k++;
            }
            memset(&dataLine, 0, sizeof(struct data));
        }
    }
    if (k == 0) {
        cout << "not found" << endl;
    }
    fclose(fileStream);
}//Displays all of the file contents
void removeLine(int ID) {
    data item;
    data nullLine{
            0,
            "",
            0
    };
    FILE *fileStream = fopen("data", "r+");
    rewind(fileStream);
    if (fileStream == NULL) {
        cout << "Can't open file to write" << endl;
    } else {
        while (!feof(fileStream)) {
            fread(&item, sizeof(item), 1, fileStream);
            if (feof(fileStream)) break;
            if (item.ID == ID) {
                fseek(fileStream, -(sizeof(nullLine)), SEEK_CUR);
                fwrite(&nullLine, sizeof(nullLine), 1, fileStream);
                fclose(fileStream);
                return;
            }
            memset(&item, 0, sizeof(struct data));
        }
    }
    fclose(fileStream);
    cout << "Can't removeLine property with ID of " << ID << endl;
    return;
}//Removes a struct with a specific ID
data findLine(char *name) {
    data item;
    FILE *fileStream = fopen("data", "r");

    if (fileStream == NULL) {
        cout << "Can't open file to read" << endl;
    } else {
        while (!feof(fileStream)) {
            fread(&item, sizeof(item), 1, fileStream);
            if (feof(fileStream)) break;
            if (strcmp(name, item.name) == 0) {
                return item;
            }
            memset(&item, 0, sizeof(struct data));
        }
    }
    fclose(fileStream);
    return data {
            0,
            NULL,
            NULL
    };
}//Finds a struct by name
void executeEdit() {
    int ID = 0;
    data item;
    while (ID <= 0) {
        cout << "Enter property ID for editing: ";
        cin >> ID;
        if (ID <= 0) {
            cout << "Enter valid ID" << endl;
        }
        item = iDSearch(ID);
        if (item.ID == 0) {
            cout << "data struct with that ID wasn't found" << endl;
            ID = 0;
        }
    }
    clearBuffer();
    string name;
    string description;
    cout << "Edit name (" << item.name << "): ";
    getline(cin, name);
    strcpy(item.name, name.c_str());
    cout << "Edit Description: (" << item.description << "): ";
    getline(cin, description);
    strcpy(item.description, description.c_str());
    edit(ID, item);
    cout << "Property saved!";
}
void edit(int ID, data property) {
    data item;
    FILE *fileStream = fopen("data", "r+");
    rewind(fileStream);
    if (fileStream == NULL) {
        cout << "Can't open file to write" << endl;
    } else {
        while (! feof(fileStream)) {
            fread(&item, sizeof(item), 1, fileStream);
            if (feof(fileStream)) break;
            if (item.ID == ID) {
                fseek(fileStream, -(sizeof(property)), SEEK_CUR);
                fwrite(&property, sizeof(property), 1, fileStream);
                fclose(fileStream);
                return;
            }
            memset(&item, 0, sizeof(struct data));
        }
    }
    fclose(fileStream);
    cout << "Can't edit property with ID of " << ID << endl;
    return;
}
data iDSearch(int serchById) {
    data item;
    FILE *fileStream = fopen("data", "r");
    if (fileStream == NULL) {
        cout << "Can't open file to read" << endl;
    } else {
        while (! feof(fileStream)) {
            fread(&item, sizeof(item), 1, fileStream);
            if (feof(fileStream)) break;

            if (item.ID == serchById) {
                fclose(fileStream);
                return item;
            }
            memset(&item, 0, sizeof(struct data));
        }
    }
    fclose(fileStream);
    return data {
            0,
            "",
            ""
    };
}
