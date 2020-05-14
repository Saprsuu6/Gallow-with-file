// ������ &(������) ��� �������� �������� � ������� ���������� �������� ��������� �� ������(� ����������� ��� �� ������, � �� ����� �����)
// ��� ������� *(��������� �� ������)&(������) ��� �������� �������� � ������� ���������� �������� ��������� �� ������ �� ������
// ��������� �� ������ ��������� �� ������ ��� �������
// ��� char ������������� ��������������� ����� � ������� ������ �� ������� ASCI

// ����������� ������������ ������������� �����
#include "Header.h"

void Setings(const HANDLE& h, const HWND& hwnd) {
    system("mode con cols=70 lines=25"); // ��������� �������� ���� �������
    SetConsoleTextAttribute(h, 10); // ��������� �������� �����
    system("title Gallow"); // �������� ���� �������
    // ������ ������ ���������
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    // ��� ����������� �������
    srand(time(0));
}

// ������� ������ ������ ���� � �������������� ���������
void MenuGreenText(const HANDLE& h, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << "Start game." << endl;
    cout << "Exit." << endl;
}

// ������� ������ ������ ���� � �������������� ���������(����� �������� ������)
void MenuRedText(const HANDLE& h, string str, int x, int y, int color) {
    COORD text{ x,y };
    SetConsoleCursorPosition(h, text);
    SetConsoleTextAttribute(h, color);
    cout << str;
}

// ������� ������ � ���������� ���� �������
void Exit() {
    int message = MessageBoxA(0, "Do you realy to exit?", "", MB_YESNO);
    if (message == IDYES)
        system("taskkill /im Gallow.exe");
    else
        main();
}

// ������� ������������ �������� �� ��������� � � ������������� ����� � ������������ ���������
void Loading(const HANDLE& h, int color) {
    COORD c{ 7,0 }; // ����� �������� ����� �� ���� ����������� 
    SetConsoleTextAttribute(h, color);
    for (int i = 0; i < 3; i++) {
        cout << "Loading";
        for (int i = 0; i < 3; i++) {
            Sleep(100);
            SetConsoleCursorPosition(h, c);
            cout << "."; // ���������� �����
            Sleep(200); // ��������� 200 ���.
            c.X++; // ��������� �� �
            if (c.X == 10) { // ���� � = 10, ������� � ������ ������
                system("cls"); // ������� ������
                c.X = 7;
            }
        }
    }
}

// ������� ������ �����
void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2) {
    COORD mouse; // ���������� �����
    HANDLE h_m = GetStdHandle(STD_INPUT_HANDLE); // ���������� ����� ����� � ���������� �������
    SetConsoleMode(h_m, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // ��������� ������ ������������� �����
    const int events = 256; // ���������� ������� �� ������
    INPUT_RECORD all_events[events]; // ������ ������� �� ������ ������������ � ������� 
    DWORD read_event; // ���� ������ � ������� ����������� ���������� ������������ �������
    while (true) { // ����������� ����
        ReadConsoleInput(h_m, all_events, events, &read_event); // ��������� ���� ������� �������. � ������� 
        for (int i = 0; i < read_event; i++) { // ���� ������� �������
            mouse.X = all_events[i].Event.MouseEvent.dwMousePosition.X; // ��������� ��������� �����
            mouse.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y; // ��������� ��������� �����
            MenuGreenText(h, 0, 0, color2); // ������� ������ ������
            if (mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0)
                MenuRedText(h, "Start game.", 0, 0, color); // ������� ������ �������� ������ ��� ���������
            else if (mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1)
                MenuRedText(h, "Exit.", 0, 1, color); // ������� ������ �������� ������ ��� ���������
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 5 && mouse.Y == 1) // ���� ���� ������ ������(1ST) ������ ����
                Exit(); // ������� ������                                                                                   
            else if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                mouse.X >= 0 && mouse.X <= 11 && mouse.Y == 0) // ���� ���� ������ ������(1ST) ������ ����
                exit = true; // ���������� ������� �������� ����� �� ������������ ����� � ������ ����
        }
        if (exit == true)
            break; // ����� �� ������������ ����� � ������ ����
    }
}

void CreatePapka() {
    _mkdir("Source");
}

void FillWordsTxt() {
    FILE* file;
    Words words;
    fopen_s(&file, "Source\\Words.txt", "w");
    for (int i = 0; i < words.length; i++)
        fputs(words.str[i], file);
    fclose(file);
}

void FillHintsTxt() {
    FILE* file;
    Hints hints;
    fopen_s(&file, "Source\\Hints.txt", "w");
    for (int i = 0; i < hints.length; i++)
        fputs(hints.str[i], file);
    fclose(file);
}

// word. ������ ����������� ��������� ����� ������ ���� ���������
void CreateWord(Word& word) { // ���� �������� �� 12 ���������
    Words words;
    Hints hints;
    FILE* file = {};
    int str = 0;
    char* temp_hint = new char[1000];
    char* temp_word = new char[100];
    int random = rand() % 10;
    fopen_s(&file, "Source\\Words.txt", "r");
    while (!feof(file)) {
        fgets(temp_word, 99, file);
        if (str == random) {
            word.str = temp_word;
            break;
        }
        str++;
    }
    fclose(file);
    str = 0;
    fopen_s(&file, "Source\\Hints.txt", "r");
    while (!feof(file)) {
        fgets(temp_hint, 999, file);
        if (str == random) {
            hints._str = temp_hint;
            break;
        }
        str++;
    }
    fclose(file);
    CountLetters(word); // ������� �������� �������� ����� ����� \0
}

// ������� �������� �������� ����� ����� \0
void CountLetters(Word& word) {
    int letters = 0;
    for (int i = 0; i < word.length; i++) {
        if (word.str[i] > 0 && word.str[i] < 256) // ���� ������ ��������� � ��������� �������� ASCI
            letters++;
    }
    word.length = letters - 1; // ������ � ���������� ��������� ���������� ��������
}

// �������� ����� ��� ����
void Frame(const HANDLE& h, const Word& word, int hight, int width) {
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0)
                cout << char(201);
            else if (i == hight - 1 && j == 0)
                cout << char(200);
            else if (i == 0 && j == width - 1)
                cout << char(187);
            else if (i == hight - 1 && j == width - 1)
                cout << char(188);
            else if (i == 0 && j == 17)
                cout << char(203);
            else if (i == hight - 1 && j == 17)
                cout << char(202);
            else if (i == 0 || i == hight - 1)
                cout << char(205);
            else if (j == 0 || j == width - 1 || j == 17)
                cout << char(186);
            else if (i == 2 && j > 0 && j < word.length + 1) // ������ ������� "-" ���  ����������� ���������� ��������
                cout << "-";
            else
                cout << " ";
        }
        cout << endl;
    }
}

// ������� ������ 
void GameplayPrint(const HANDLE& h, const Word& word, int width) {
    COORD c{ 1,3 };
    SetConsoleCursorPosition(h, c);
    cout << "Enter latter:" << char(26) << " " << char(27); // ����� ��������� ����� �������� �����
    c.Y += 5; // ���������� ���������� � �� 5
    for (int i = 0; i < width; i++) {
        SetConsoleCursorPosition(h, c);
        SetConsoleTextAttribute(h, rand() % 14 + 1);
        cout << ":)"; // ��� �������)
        c.X += 2;
    }
}

// ������� ������ ��������
void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3) {
    COORD input; // ���������� ��� ������ � �������
    int fail = 0; // ��������� ������������ ������
    int code; // ���������� � ����� ������� �������
    char latter_code = 0; // ��� �������
    int latters_left = word.length; // ������� ���� ��������
    int* ar = new int[word.length]; // ����� ��������� �� ��������� ���� ������ � ���� �� �����, ���� ��� ���� ������� ���������
    int ind_of_latter = RandomLatter(word, ar); // �������� ������� �� �������� ���������� �����
    while (true) {
        int exit_from_cycle = 0; // ���������� ��� ������ �� �����
        input.X = 1;
        input.Y = 6;
        SetConsoleCursorPosition(h, input);
        SetConsoleTextAttribute(h, color3); // ����� �����
        cout << "Latters left: " << latters_left; // ������ �� ����������� (1,6)
        input.Y++; //���������� ���������� � �� 1 
        SetConsoleCursorPosition(h, input);
        cout << "Now " << ind_of_latter + 1 << " latter  "; // ������ ���������� ���������� ����  
        while (true) {
            input.Y = 3;
            input.X = 15;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color);
            code = Input(); // ������ ���� �� ������� ������� ������� � � ������ � ����������
            if (code != 13) // ���� ��� �� ����� ������� ENTER �� � ��������� ������������ ��� �����
                latter_code = code;
            else // � ������ ������ � ���������� ����� �� ����� ������������� ��� 13
                exit_from_cycle = code;
            if (latter_code != 9) // ����� ���� ������� ����� ������� �� ���� ������� TAB
                cout << char(latter_code); // ����� �� ����������� (15,3)
            if (exit_from_cycle == 13) // ����� �� ����� ���� ��������� ����� ����� 13
                break;
            input.Y++;
            input.X -= 14;
            SetConsoleCursorPosition(h, input);
            SetConsoleTextAttribute(h, color2);
            cout << "Press ENTER"; // ����� �� ����������� (1,4)
        }
        Check(h, input, word, latter_code, ind_of_latter, ar, latters_left, fail); // �������� �������� ��������
        CheckForFinish(word, latters_left, fail); // �������� �� ����� ����
    }
}

// ������� ��� ������ ��������� �����
int RandomLatter(const Word& word, int*& ar) {
    int value = rand() % word.length; // ������ � ���������� ���������� ����� � ��������� �� 0 �� ���������� ������� - 1 ������������ 
    for (int i = 0; i < word.length; i++) {
        if (ar[i] == value) { // ���� �� �������� ������� ������� ������� �����                   
            while (value == ar[i]) // ������ ������� ���� �� ��������� �����              
                value = rand() % word.length;
            i = 0; // ��������� �������� ����� �� ����������� �������� � ����� ������� �������                             
        }
    }
    ar[value] = value; // ������ �������� � ������ �� ������� �������                     
    return value; // ������� �������� � ������ � ��������� ind_of_latter                             
}

// ������� ����� ������� �� ����������
int Input() {
    int code = _getch(); // ������� _getch() ���������� ��� �� ������� ������� 
    if (code == 224) // ��� ������� �� �������� �� ������� ���������� ��� 224
        code = _getch(); // ������� �� �������� ����������� 
    return code; // ������� �������� � ������ � ��������� code
}

// ������� �������� ��������
void Check(const HANDLE& h, COORD& input, const Word& word, int latter_code, int& ind_of_latter, int*& ar,
    int& latters_left, int& fail) {
    if (latter_code == int(word.str[ind_of_latter])
        || latter_code + 32 == int(word.str[ind_of_latter])
        || latter_code - 32 == int(word.str[ind_of_latter])) { // ���� ���� �������� ������
        input.X = ind_of_latter + 1;
        input.Y = 1;
        SetConsoleCursorPosition(h, input);
        cout << word.str[ind_of_latter]; // ������ ����� ������� ����� �� ��� �����
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "RIGHT:)"); // ������� �������� �������
        ind_of_latter = RandomLatter(word, ar); // ������ ������ ���������� ����� �� �������� ��������� ������ � ������
        latters_left--; // ���������� ���������� ����
    }
    else {
        Effect(h, input, int(Colors::LIGHT_RED), int(Colors::GREEN), "WRONG:("); // ������� �������� �������
        // ��������� �������� ������ �� ���������� �������� �������� ������� � ���������� (18,1), ����� ������
        // ���������� fail ������������� �� ���������� ������ ������� � �����������
        COORD picture{ 18,1 };
        SetConsoleTextAttribute(h, int(Colors::DARK_YELLOW));
        if (word.length == 11) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 2) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 3) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 6) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 7) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 8) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 9) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 10) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 10) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 1) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 5) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 6) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 8) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 9) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 9) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 6) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
            }
            else if (fail == 8) {
                fail++;
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 8) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
            }
            else if (fail == 1) {
                fail++;
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 5) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 6) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 7) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 7) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 4) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 5) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 6) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 6) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
            }
            else if (fail == 2) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 3) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 4) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 5) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 5) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
            }
            else if (fail == 3) {
                fail++;
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 4) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 4) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
            }
            else if (fail == 2) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 3) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 3) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
            }
            else if (fail == 1) {
                fail++;
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 2) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 2) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
            }
            else if (fail == 1) {
                fail++;
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
        else if (word.length == 1) {
            if (fail == 0) {
                fail++;
                GallowPicture(h, picture, 8, 16);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 2);
                HeadtPicture(h, picture, 26, 3);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 26, 4);
                RightArm_LegPicture(h, picture, 25, 4);
                LeftArm_LegPicture(h, picture, 27, 4);
                RightArm_LegPicture(h, picture, 25, 5);
                LeftArm_LegPicture(h, picture, 27, 5);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 25, 6);
                Kanat_Body_RightLeg_LeftLegPicture(h, picture, 27, 6);
                Right_LeftFootPicture(h, picture, 24, 6);
                Right_LeftFootPicture(h, picture, 28, 6);
            }
        }
    }
}

// ������� �������� �������
void Effect(const HANDLE& h, COORD& input, int color, int color2, string str) {
    input.X = 1;
    input.Y = 5;
    for (int i = 0; i < 6; i++) { // ������� ����� ������ ���������� ����� ������� ������� � ����������� (1,5)
        if (i % 2 == 0) // ���� �������� ������ ���� ����
            SetConsoleTextAttribute(h, color);
        else
            SetConsoleTextAttribute(h, color2); // ����� ������
        SetConsoleCursorPosition(h, input);
        cout << str; // ����� �����
        Sleep(200); // ��� 200 ���
    }
    Sleep(100);
    SetConsoleCursorPosition(h, input);
    cout << "       "; // � ����� �� ��� �� ����������� ����� ��� �������
}

// ������� �������� �� ����� ����
void CheckForFinish(const Word& word, int latters_left, int& fail) {
    if (fail == word.length) { // ���� ����� ��������� ������� ��������(���������� ������ ����� ���������� ���� �������� ��������
        MusikGameOver(); // ������ �������
        ForLoose(); // ��������� � ���������
    }
    if (latters_left == 0) { // ���� �� �������� �� ���� �� �������� �����
        MusikWin(); // ������ �������
        GuessedAllLatters(); // ��������� � ��������
    }
}

// ��������� � ���������
void ForLoose() {
    int message = MessageBoxA(0, "You haven't guessed all latters. Do you wnat to play again?", "You loos", MB_YESNO);
    if (message == IDYES)
        main(); // ���� ����� "��" �� ����� � main
    else
        Exit(); // ���� ��� �� �� �����
}

void GuessedAllLatters() {
    int message = MessageBoxA(0, "You have guessed all latters. Do you wnat to play again?", "You win!!!", MB_YESNO);
    if (message == IDYES)
        main(); // ���� ����� "��" �� ����� � main
    else
        Exit(); // ���� ��� �� �� �����
}

// ������� ��� �������
void MusikGameOver() { // ������ ����� ���������� https://studfile.net/preview/600434/page:10/ ������ ���� ���������� ������� �������� ��� ���� ��� ������, ��� ���� ��� ��������
    Beep(587, 500);
    Beep(523, 500);
    Beep(494, 500);
    for (int i = 0; i < 5; i++)
        Beep(466, 100);
}

void MusikWin() {
    Beep(494, 500);
    for (int i = 0; i < 2; i++)
        Beep(523, 100);
    Beep(523, 100);
    Beep(880, 500);
}

// ������ ����� ��������
void GallowPicture(const HANDLE& h, COORD& picture, int hight, int width) {
    for (int i = 0; i < hight; i++) {
        SetConsoleCursorPosition(h, picture);
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == 1 || i == hight - 1 || i == 0 && j < 9) // �������� ����� ����� ����������� ������ ��������
                cout << char(219);
        }
        picture.Y++; // ������������ ���������� �
    }
}

// ������ ������, ������� ��������, ������ ����, ����� ����
// ������ �� ������ �.�. ��� �������� �������, ��� ���������� ��������� �� ����������� �����������
void Kanat_Body_RightLeg_LeftLegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "|";
}

// ������ ������
// ������ �� ������ �.�. ��� �������� �������, ��� ���������� ��������� �� ����������� �����������
void HeadtPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << char(2);
}

// ������ ����� ���� � ����� ����
// ������ �� ������ �.�. ��� �������� �������, ��� ���������� ��������� �� ����������� �����������
void LeftArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "\\";
}

// ������ ������ ����� � ������ �����
// ������ �� ������ �.�. ��� �������� �������, ��� ���������� ��������� �� ����������� �����������
void RightArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "/";
}

// ������ �������
// ������ �� ������ �.�. ��� �������� �������, ��� ���������� ��������� �� ����������� �����������
void Right_LeftFootPicture(const HANDLE& h, COORD& picture, int x, int y) {
    picture.X = x;
    picture.Y = y;
    SetConsoleCursorPosition(h, picture);
    cout << "_";
}