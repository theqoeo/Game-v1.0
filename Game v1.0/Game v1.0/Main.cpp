#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>


// ** ���� : https://www.youtube.com/watch?v=_nuS86ITjIM


// ** ����	 0
// ** ��ο� �Ķ�	 1
// ** ��ο� �ʷ�	 2
// ** ��ο� �ϴ�	 3
// ** ��ο� ����	 4
// ** ��ο� ����	 5
// ** ��ο� ���	 6
// ** ȸ��	 7
// ** ��ο� ȸ��	 8
// ** �Ķ�	 9
// ** �ʷ�	 10
// ** �ϴ�	 11
// ** ����	 12
// ** ����	 13
// ** ���	 14
// ** �Ͼ�	 15

const int PLAYER = 0;
const int ENEMY = 1;
const int MAX = 2;

const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;

int SceneState = 0;

int Check = 1;

DWORD SetnameTime = 0;

typedef struct tagInfo
{
	int IHP;
	int IMP;
	int IExp;
	int ILevel;
	int IGold;

	float FAttack;
	float FDefense;
}INFO;

typedef struct tagObject
{
	char* Name;
	INFO Info;
}OBJECT;

char* SetName();
void InitializePlayer(OBJECT* _Warrior, OBJECT* _Archer, OBJECT* _Magician);
void SceneManager(OBJECT* _Player, OBJECT* _Enemy);
void MenuScene();
void PlayerScene(OBJECT* _Player);
void StageScene(OBJECT* _Player, OBJECT* _Enemy);
void EnemyScene(OBJECT* _Enemy);
void InitializeEnemy(OBJECT* _Enemy);
void HideCursor();
void SetColor(int _Color);
void SetPosition(int _x, int _y, char* _str, int _Color);
void FirstScene();
void GameStrat();
void GameStory();

int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� ��.
	HideCursor();

	// ** �ܼ�â�� ����� ����.
	system("mode con:cols=120 lines=30");

	// ** �ݼ�â�� �̸��� ����
	system("title ��뿵 Framework v0.6");

	// ** ó����
	FirstScene();
	GameStrat();
	SetColor(15);

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player, Player, Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);

	DWORD dwTime = GetTickCount64(); // 1/1000 (1000���� 1��)
	int Delay = 1000;

	int UpCount = 0;
	
	while (true)
	{
		if (dwTime + Delay < GetTickCount64())
		{
			dwTime = GetTickCount64();

			system("cls");

			printf_s("Player : %s\n", Player->Name);

			// ** ���� ����
			SceneManager(Player, Monster);
		}
	}

	return 0;
}

char* SetName()
{
	int Width = 40;
	int Height = 5;

	// ** scanf �Լ��� ���ڿ��� �Է¹ޱ� ���� ���ڿ��� �������ִ� �迭�� ����.
	char Buffer[128] = "";

	SetPosition(Width, Height + 2, (char*)"�̸� �Է� : ", 15);

	// ** ���ڿ��� �Է� ����.
	scanf("%s", Buffer);

	// ** �Է� �������� �迭 ������, ��ȯ ���� ĳ���� ���������̹Ƿ� ���ڿ��� ���������.
	// ** ���ڿ��� ���� �ϱ����� �����Ͱ� ����Ű�� ������ �Է¹��� ���ڿ��� ��ư���ŭ�� ũ��� �޸� �Ҵ�.
	char* pName = (char*)malloc(strlen(Buffer) + 1);

	// ** Buffer �� ���� ���ڿ��� pName ���� ����.
	strcpy(pName, Buffer);

	system("cls");
	// ** ��ȯ.
	return pName;
}

void SceneManager(OBJECT * _Player, OBJECT * _Enemy)
{
	switch (SceneState)
	{
	case Scene_Logo:
		GameStory();
		break;
	case Scene_Menu:
		MenuScene();
		break;
	case Scene_Stage:
		StageScene(_Player, _Enemy);
		break;
	case Scene_Exit:
		exit(NULL);// ** ���α׷� ����
		break;
	}
}

void MenuScene()
{
	printf_s("MenuScene\n");

	printf_s("1. �̵�\n2. ����\n3.  ����\n�Է� : ");

	int i = 0;
	scanf_s("%d", &i);

	if (i == 1)
		SceneState = Scene_Stage;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void InitializePlayer(OBJECT * _Warrior, OBJECT * _Archer, OBJECT * _Magician) // �÷��̾� ���� ����
{
	int Width = 40;
	int Height = 5;
	int i = 0;

	SetPosition(Width, Height, (char*)"1.���� 2.�ü� 3. ������\n", 15);
	SetPosition(Width, Height + 1, (char*)"������ �������ּ��� : ", 15);
	scanf_s("%d", &i);
	system("cls");
	while (true)
	{
		if (i == 1)
		{
			_Warrior->Name = SetName();

			_Warrior->Info.FAttack = 15;
			_Warrior->Info.FDefense = 10;
			_Warrior->Info.IExp = 0;
			_Warrior->Info.IHP = 100;
			_Warrior->Info.IMP = 50;
			_Warrior->Info.ILevel = 1;
			_Warrior->Info.IGold = 0;
			SetPosition(Width, Height, (char*)"����� ������ �����Դϴ�. \n", 15);
			break;
		}
		else if (i == 2)
		{
			_Archer->Name = SetName();

			_Archer->Info.FAttack = 20;
			_Archer->Info.FDefense = 5;
			_Archer->Info.IExp = 0;
			_Archer->Info.IHP = 80;
			_Archer->Info.IMP = 50;
			_Archer->Info.ILevel = 1;
			_Archer->Info.IGold = 0;
			SetPosition(Width, Height, (char*)"����� ������ �ü��Դϴ�. \n", 15);
			break;
		}
		else if (i == 3)
		{
			_Magician->Name = SetName();

			_Magician->Info.FAttack = 10;
			_Magician->Info.FDefense = 5;
			_Magician->Info.IExp = 0;
			_Magician->Info.IHP = 70;
			_Magician->Info.IMP = 100;
			_Magician->Info.ILevel = 1;
			_Magician->Info.IGold = 0;
			SetPosition(Width, Height, (char*)"����� ������ �������Դϴ�. \n", 15);
			break;
		}
		else
		{
			SetPosition(Width, Height, (char*)"������ �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���.\n", 15);
			Sleep(3000);
			system("cls");
			InitializePlayer(_Warrior, _Archer, _Magician);
			break;
		}
	}
}

void InitializeEnemy(OBJECT * _Enemy)
{
	_Enemy->Name = (char*)"Enemy";

	_Enemy->Info.FAttack = 5;
	_Enemy->Info.FDefense = 15;
	_Enemy->Info.IExp = 0;
	_Enemy->Info.IHP = 30;
	_Enemy->Info.IMP = 5;
	_Enemy->Info.ILevel = 1;
}

void PlayerScene(OBJECT* _Player)
{
	if (SetnameTime + 10000 < GetTickCount64())
		Check = 1;

	if (Check)
	{
		SetnameTime = GetTickCount64();

		_Player->Name = SetName();
		Check = 0;
	}
}

void StageScene(OBJECT * _Player, OBJECT * _Enemy)
{
	// ** ����
	int Width = 40;
	int Height = 5;
	int ISelect = 0;

	OBJECT* Objects[MAX];

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player, Player, Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);
	SetPosition(Width, Height, (char*)"StageScene\n", 15);
	SetPosition(Width, Height, (char*)"1. ���� 2. ����\n", 15);
	SetPosition(Width, Height + 1, (char*)"���͸� �����ƽ��ϴ�.\n", 15);
	SetPosition(Width, Height + 2, (char*)"���� : ", 15);
	scanf_s("%d", &ISelect);

	switch (ISelect)
	{
	case 1:
		if (Objects[PLAYER]->Info.FAttack > Objects[ENEMY]->Info.FDefense)
		{
			Objects[ENEMY]->Info.IHP -= Objects[PLAYER]->Info.FAttack - Objects[ENEMY]->Info.FDefense;
		}
		else
			Objects[ENEMY]->Info.IHP -= 1;
		if (Objects[ENEMY]->Info.FAttack > Objects[PLAYER]->Info.FDefense)
		{
			Objects[PLAYER]->Info.IHP -= Objects[ENEMY]->Info.FAttack - Objects[PLAYER]->Info.FDefense;
		}
		else
			Objects[PLAYER]->Info.IHP -= 1;
		break;
	default:
		break;
	}
	SceneState++;

	PlayerScene(_Player);
	EnemyScene(_Enemy);
}

void EnemyScene(OBJECT * _Enemy)
{

}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void FirstScene()// ���ӽ��� ȭ��
{
	int Width = (50) - (strlen("RRRRRRRRRRRRRRRRR   PPPPPPPPPPPPPPPPP           GGGGGGGGGGGGG\n") / 2);
	int Height = 5;
	int n = 0;

	for (int i = 0; i < 5; i++)
	{
		SetPosition(Width + n, Height + 1, (char*)"RRRRRRRRRRRRRRRRR   PPPPPPPPPPPPPPPPP           GGGGGGGGGGGGG\n", 6);
		SetPosition(Width + n, Height + 2, (char*)"R::::::::::::::::R  P::::::::::::::::P       GGG::::::::::::G\n", 6);
		SetPosition(Width + n, Height + 3, (char*)"R::::::RRRRRR:::::R P::::::PPPPPP:::: : P    GG:::::::::::::: : G\n", 6);
		SetPosition(Width + n, Height + 4, (char*)"RR:::: : R     R:::: : RPP:::: : P     P:::: : P  G:::: : GGGGGGGG::::G\n", 6);
		SetPosition(Width + n, Height + 5, (char*)"R::::R     R:::: : R  P::::P     P:::: : P G:::: : G       GGGGGG\n", 6);
		SetPosition(Width + n, Height + 6, (char*)"R::::R     R:::: : R  P::::P     P:::: : PG:::: : G\n", 6);
		SetPosition(Width + n, Height + 7, (char*)"R::::RRRRRR:::: : R   P::::PPPPPP:::: : P G:::: : G\n", 6);
		SetPosition(Width + n, Height + 8, (char*)"R:::::::::::: : RR    P:::::::::::: : PP  G:::: : G    GGGGGGGGGG\n", 6);
		SetPosition(Width + n, Height + 9, (char*)"R::::RRRRRR:::: : R   P::::PPPPPPPPP    G:::: : G    G::::::::G\n", 6);
		SetPosition(Width + n, Height + 10, (char*)"R::::R     R:::: : R  P::::P            G:::: : G    GGGGG::::G\n", 6);
		SetPosition(Width + n, Height + 11, (char*)"R::::R     R:::: : R  P::::P            G:::: : G        G::::G\n", 6);
		SetPosition(Width + n, Height + 12, (char*)"R::::R     R:::: : R  P::::P             G:::: : G       G::::G\n", 6);
		SetPosition(Width + n, Height + 13, (char*)"RR:::: : R     R:::: : RPP::::::PP            G:::: : GGGGGGGG::::G\n", 6);
		SetPosition(Width + n, Height + 14, (char*)"R::::::R     R:::: : RP::::::::P             GG:::::::::::::: : G\n", 6);
		SetPosition(Width + n, Height + 15, (char*)"R::::::R     R:::: : RP::::::::P               GGG::::::GGG:: : G\n", 6);
		SetPosition(Width + n, Height + 16, (char*)"RRRRRRRR     RRRRRRRPPPPPPPPPP                  GGGGGG   GGGG\n", 6);
		n++;

		Sleep(500);
		system("cls");
	}
}

void GameStrat()// ���� ����, ������ ����
{
	int Width = 40;
	int Height = 5;
	int ISelect = 0;

	SetPosition(Width, Height, (char*)"1. �����ϱ� 2. ������\n", 15);
	SetPosition(Width, Height + 1, (char*)"������ �����Ͻðڽ��ϱ�?\n", 15);
	SetPosition(Width, Height + 2, (char*)"���� : ", 15);
	scanf_s("%d", &ISelect);
	system("cls");

	while (true)
	{
		if (ISelect == 1)
		{
			SetPosition(Width, Height, (char*)"������ �����մϴ�. ", 15);
			Sleep(2000);
			break;
		}
		else if (ISelect == 2)
		{
			SetPosition(Width, Height, (char*)"������ �����մϴ�. ", 15);
			exit(NULL);
			break;
		}
		else
		{
			SetPosition(Width, Height, (char*)"�߸������ϼ̽��ϴ�. �ٽ� �������ּ���.\n", 15);
			Sleep(2000);
			system("cls");
			GameStrat();
			break;
		}
	}
}

void GameStory()// ���� ���丮
{
	int Width = 40;
	int Height = 5;

	SetPosition(Width, Height, (char*)"������ ������ �����ҷ��� �ϰ� �ֽ��ϴ�.\n", 15);
	SetPosition(Width, Height + 1, (char*)"���͸� ��� �������� ������ ��ġ���ּ���,\n", 15);
	Sleep(2000);
	system("cls");
	SceneState++;
}