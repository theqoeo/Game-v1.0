#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>


// ** 참고 : https://www.youtube.com/watch?v=_nuS86ITjIM


// ** 검정	 0
// ** 어두운 파랑	 1
// ** 어두운 초록	 2
// ** 어두운 하늘	 3
// ** 어두운 빨강	 4
// ** 어두운 보라	 5
// ** 어두운 노랑	 6
// ** 회색	 7
// ** 어두운 회색	 8
// ** 파랑	 9
// ** 초록	 10
// ** 하늘	 11
// ** 빨강	 12
// ** 보라	 13
// ** 노랑	 14
// ** 하양	 15

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
	// ** 커서를 안보이게 함.
	HideCursor();

	// ** 콘솔창의 사이즈를 설정.
	system("mode con:cols=120 lines=30");

	// ** 콜솔창의 이름을 설정
	system("title 배대영 Framework v0.6");

	// ** 처음씬
	FirstScene();
	GameStrat();
	SetColor(15);

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player, Player, Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);

	DWORD dwTime = GetTickCount64(); // 1/1000 (1000분의 1초)
	int Delay = 1000;

	int UpCount = 0;
	
	while (true)
	{
		if (dwTime + Delay < GetTickCount64())
		{
			dwTime = GetTickCount64();

			system("cls");

			printf_s("Player : %s\n", Player->Name);

			// ** 게임 루프
			SceneManager(Player, Monster);
		}
	}

	return 0;
}

char* SetName()
{
	int Width = 40;
	int Height = 5;

	// ** scanf 함수로 문자열을 입력받기 위해 문자열을 받을수있는 배열을 선언.
	char Buffer[128] = "";

	SetPosition(Width, Height + 2, (char*)"이름 입력 : ", 15);

	// ** 문자열을 입력 받음.
	scanf("%s", Buffer);

	// ** 입력 받은값은 배열 이지만, 반환 값은 캐릭터 포인터형이므로 문자열을 복사햐야함.
	// ** 문자열을 복사 하기위해 포인터가 가르키는 공간에 입력받은 문자열이 들아갈만큼의 크기로 메모리 할당.
	char* pName = (char*)malloc(strlen(Buffer) + 1);

	// ** Buffer 가 받은 문자열을 pName 으로 복사.
	strcpy(pName, Buffer);

	system("cls");
	// ** 반환.
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
		exit(NULL);// ** 프로그램 종료
		break;
	}
}

void MenuScene()
{
	printf_s("MenuScene\n");

	printf_s("1. 이동\n2. 상점\n3.  종료\n입력 : ");

	int i = 0;
	scanf_s("%d", &i);

	if (i == 1)
		SceneState = Scene_Stage;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void InitializePlayer(OBJECT * _Warrior, OBJECT * _Archer, OBJECT * _Magician) // 플레이어 직업 선택
{
	int Width = 40;
	int Height = 5;
	int i = 0;

	SetPosition(Width, Height, (char*)"1.전사 2.궁수 3. 마법사\n", 15);
	SetPosition(Width, Height + 1, (char*)"직업을 선택해주세요 : ", 15);
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
			SetPosition(Width, Height, (char*)"당신의 직업은 전사입니다. \n", 15);
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
			SetPosition(Width, Height, (char*)"당신의 직업은 궁수입니다. \n", 15);
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
			SetPosition(Width, Height, (char*)"당신의 직업은 마법사입니다. \n", 15);
			break;
		}
		else
		{
			SetPosition(Width, Height, (char*)"직업을 잘못 선택하셨습니다. 다시 선택해주세요.\n", 15);
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
	// ** 전투
	int Width = 40;
	int Height = 5;
	int ISelect = 0;

	OBJECT* Objects[MAX];

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player, Player, Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);
	SetPosition(Width, Height, (char*)"StageScene\n", 15);
	SetPosition(Width, Height, (char*)"1. 공격 2. 도망\n", 15);
	SetPosition(Width, Height + 1, (char*)"몬스터를 마주쳤습니다.\n", 15);
	SetPosition(Width, Height + 2, (char*)"선택 : ", 15);
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

void FirstScene()// 게임시작 화면
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

void GameStrat()// 게임 시작, 나가기 선택
{
	int Width = 40;
	int Height = 5;
	int ISelect = 0;

	SetPosition(Width, Height, (char*)"1. 시작하기 2. 나가기\n", 15);
	SetPosition(Width, Height + 1, (char*)"게임을 시작하시겠습니까?\n", 15);
	SetPosition(Width, Height + 2, (char*)"선택 : ", 15);
	scanf_s("%d", &ISelect);
	system("cls");

	while (true)
	{
		if (ISelect == 1)
		{
			SetPosition(Width, Height, (char*)"게임을 시작합니다. ", 15);
			Sleep(2000);
			break;
		}
		else if (ISelect == 2)
		{
			SetPosition(Width, Height, (char*)"게임을 종료합니다. ", 15);
			exit(NULL);
			break;
		}
		else
		{
			SetPosition(Width, Height, (char*)"잘못선택하셨습니다. 다시 선택해주세요.\n", 15);
			Sleep(2000);
			system("cls");
			GameStrat();
			break;
		}
	}
}

void GameStory()// 게임 스토리
{
	int Width = 40;
	int Height = 5;

	SetPosition(Width, Height, (char*)"마왕이 세상을 정복할려고 하고 있습니다.\n", 15);
	SetPosition(Width, Height + 1, (char*)"몬스터를 잡고 강해져서 마왕을 퇴치해주세요,\n", 15);
	Sleep(2000);
	system("cls");
	SceneState++;
}