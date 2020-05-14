// ����������� ������ ��� ������ ���������
#include<iostream> // ��� ����������� ����� ������
#include<Windows.h> // ��� �������� HANDLE(����� ����������(������)���� �������), HWND(����� ����������(������)���� ������� ��� ����), COORD(����������� ��������� ������������)
#include<ctime> // ��� ��������� �����, ������ ������� �� 1983 ���� (���� ��������� �++)
#include<conio.h> // ��� ������� _getch() (���� � ����������)
#include<direct.h>
using namespace std;

// �������� ������������
enum class Colors { GREEN = 10, RED = 4, PINK = 13, LIGHT_RED = 12, DARK_YELLOW = 6 };

// �������� ��������� ����� ���������� �� ������ � ������� ��������
struct Word {
    int length;
    char* str = new char[length];
};

struct Words {
    static const int length = 10;
    const char* str[length] = { "Minecraft\n","Orangen\n","Blue\n","Water\n","Rock\n",
        "Money\n","Bread\n","Vodka\n","Bear\n","Milk\n" };
};

struct Hints {
    char* _str = new char[length];
    static const int length = 10;
    const char* str[length] = { "This is a game of our childhood\n","Color of tropcis fruit\n","99% color on Earth\n",
        "We couldn't live without it\n","It's genre of music\n","We use it every day\n","Sometime we have eat it or always\n",
        "This thing gelp us from radiation\n","Alcoholic light drink\n","It's have more calcium\n" };
};


//struct WordsBase {
//    static const int size = 20;
//    const char* words[size] = { "������\n","������\n","����\n","���\n","�����\n","���\n","������\n","�����\n",
//        "������\n","����\n","������\n","������\n","�����\n","������\n","���������\n","�����\n","�����\n","���\n",
//        "�������\n","������\n"};
//};

// �������� ���������� ������� ��� ���� ����� ����� ���� ���������� � ������� �� ������ ����� ���� 
void Setings(const HANDLE& h, const HWND& hwnd);
void MenuGreenText(const HANDLE& h, int x, int y, int color);
void MenuEvent(HANDLE& h, Word& word, bool exit, int color, int color2);
void MenuRedText(const HANDLE& h, string str, int x, int y, int color);
int main();
void Exit();
void Loading(const HANDLE& h, int color);
void CreateWord(Word& word);
void Frame(const HANDLE& h, const Word& word, int hight, int width);
void GameplayPrint(const HANDLE& h, const Word& word, int width);
void CountLetters(Word& word);
void GamePlay(const HANDLE& h, const Word& word, int enter, int color, int color2, int color3);
int RandomLatter(const Word& word, int*& ar);
int Input();
void Check(const HANDLE& h, COORD& input, const Word& word, int latter_code, int& ind_of_latter, int*& ar,
    int& latters_left, int& fail);
void Effect(const HANDLE& h, COORD& input, int color, int color2, string str);
void CheckForFinish(const Word& word, int latters_left, int& fail);
void MusikWin();
void GallowPicture(const HANDLE& h, COORD& picture, int hight, int width);
void Kanat_Body_RightLeg_LeftLegPicture(const HANDLE& h, COORD& picture, int x, int y);
void HeadtPicture(const HANDLE& h, COORD& picture, int x, int y);
void LeftArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y);
void RightArm_LegPicture(const HANDLE& h, COORD& picture, int x, int y);
void Right_LeftFootPicture(const HANDLE& h, COORD& picture, int x, int y);
void MusikGameOver();
void GuessedAllLatters();
void ForLoose();
void CreatePapka();
void FillWordsTxt();
void FillHintsTxt();