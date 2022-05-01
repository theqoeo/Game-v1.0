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
const int Scene_Store = 3;
const int Scene_PlayerData = 4;
const int Scene_Exit = 5;

int SceneState = 0;

int Check = 1;

const int ISelect = 0;
const int Width = 40;
const int Height = 5;

DWORD SetnameTime = 0;

typedef struct tagInfo
{
	int IHP;
	int IMP;
	int IExp;
	int ILevel;
	int IGold;
	int IClass;

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
void MenuScene(OBJECT* _Player);
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
void PlayerData(OBJECT* _Player);
void Store(OBJECT* _Player);

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
			if (Player->Info.IClass == 1)
			{
				printf_s("Class : ����\n");
			}
			else if (Player->Info.IClass == 2)
			{
				printf_s("Class : �ü�\n");
			}
			else if (Player->Info.IClass == 3)
			{
				printf_s("Class : ������\n");
			}
			else
			{
				printf_s("Class : ����\n");
			}
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
		MenuScene(_Player);
		break;
	case Scene_Stage:
		StageScene(_Player, _Enemy);
		break;
	case Scene_Store:
		Store(_Player);
		break;
	case Scene_PlayerData:
		PlayerData(_Player);
		break;
	case Scene_Exit:
		exit(NULL);// ** ���α׷� ����
		break;
	}
}

void MenuScene(OBJECT* _Player)
{
	printf_s("MenuScene\n");

	printf_s("1. �̵�\n2. ����\n3. ����\n4. ����\n�Է� : ");

	int i = 0;
	scanf_s("%d", &i);

	if (i == 1)
		SceneState = Scene_Stage;
	else if (i == 2)
		SceneState = Scene_Store;
	else if (i == 3)
		SceneState = Scene_PlayerData;
	else if (i == 4)
		SceneState = Scene_Exit;
	else
	{
		printf_s("�߸� �����̽��ϴ�. \n");
		Sleep(1500);
		system("cls");
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}
		else if (_Player->Info.IClass == 3)
		{
			printf_s("Class : ������\n");
		}
		else
		{
			printf_s("Class : ����\n");
		}
		MenuScene(_Player);
	}
}

void InitializePlayer(OBJECT * _Warrior, OBJECT * _Archer, OBJECT * _Magician) // �÷��̾� ���� ����
{
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

			_Warrior->Info.IClass = 1;
			_Warrior->Info.FAttack = 15;
			_Warrior->Info.FDefense = 10;
			_Warrior->Info.IExp = 0;
			_Warrior->Info.IHP = 100;
			_Warrior->Info.IMP = 50;
			_Warrior->Info.ILevel = 1;
			_Warrior->Info.IGold = 20;
			SetPosition(Width, Height, (char*)"����� ������ �����Դϴ�. \n", 15);
			break;
		}
		else if (i == 2)
		{
			_Archer->Name = SetName();

			_Archer->Info.IClass = 2;
			_Archer->Info.FAttack = 20;
			_Archer->Info.FDefense = 5;
			_Archer->Info.IExp = 0;
			_Archer->Info.IHP = 80;
			_Archer->Info.IMP = 50;
			_Archer->Info.ILevel = 1;
			_Archer->Info.IGold = 20;
			SetPosition(Width, Height, (char*)"����� ������ �ü��Դϴ�. \n", 15);
			break;
		}
		else if (i == 3)
		{
			_Magician->Name = SetName();

			_Magician->Info.IClass = 3;
			_Magician->Info.FAttack = 10;
			_Magician->Info.FDefense = 5;
			_Magician->Info.IExp = 0;
			_Magician->Info.IHP = 70;
			_Magician->Info.IMP = 100;
			_Magician->Info.ILevel = 1;
			_Magician->Info.IGold = 20;
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

void Store(OBJECT* _Player) // ����
{
	int n = 0;
	printf_s("1. ����\n2. �Ǹ�\n3. ���θ޴�\n���� : ");
	scanf_s("%d", &n);
	system("cls");
	if (n == 1)
	{
		if (_Player->Info.IClass == 1)
		{
			int Choiec = 0;
			system("cls");
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Choiec);
			system("cls");

			if (Choiec == 1)
			{
				int Weapon = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("1. �콼 �� 10 Gold\n2. ��ö �� 20 Gold\n3. ¯¯���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
				scanf_s("%d", &Weapon);
				system("cls");

				if (Weapon == 1 && _Player->Info.IGold >= 10)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 �� ȿ�� : Att + 10\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");

					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�콼 ���� �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FAttack = _Player->Info.FAttack + 10;
						_Player->Info.IGold = _Player->Info.IGold - 10;
						MenuScene(_Player);
					}
					else if (WChoice == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("������ ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						Store(_Player);
					}
				}
				else if ((Weapon == 1 && _Player->Info.IGold < 10))
				{
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					MenuScene(_Player);
				}
				else if (Weapon == 2 && _Player->Info.IGold >= 20)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö �� ȿ�� : Att + 20\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");
					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("��ö ���� �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FAttack = _Player->Info.FAttack + 20;
						_Player->Info.IGold = _Player->Info.IGold - 20;
						MenuScene(_Player);
					}
					else if (WChoice == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("������ ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						Store(_Player);
					}
				}
				else if ((Weapon == 2 && _Player->Info.IGold < 20))
				{
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					MenuScene(_Player);
				}
				else if ((Weapon == 3 && _Player->Info.IGold >= 40))
				{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("¯¯���� ȿ�� : Att + 40\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("¯¯���� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FAttack = _Player->Info.FAttack + 40;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
 }
				else if ((Weapon == 3 && _Player->Info.IGold < 40))
				{
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				MenuScene(_Player);
				}
				else if (Weapon == 4)
				{
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				Store(_Player);
 }
				else
				{
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
 }
			}
			else if (Choiec == 2)
			{
				int Armor = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("1. �콼 ���� 10 Gold\n2. ��ö ���� 20 Gold\n3. �̳� �ܴ��� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
				scanf_s("%d", &Armor);
				system("cls");
				if (Armor == 1 && _Player->Info.IGold >= 10)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ���� ȿ�� : Daf + 10\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");

					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�콼 ���� �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FDefense = _Player->Info.FDefense + 10;
						_Player->Info.IGold = _Player->Info.IGold - 10;
						MenuScene(_Player);
					}
					else if (WChoice == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("������ ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						Store(_Player);
					}
				}
				else if ((Armor == 1 && _Player->Info.IGold < 10))
				{
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					MenuScene(_Player);
				}
				else if (Armor == 2 && _Player->Info.IGold >= 20)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ���� ȿ�� : Def + 20\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");
					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("��ö ������ �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FDefense = _Player->Info.FDefense + 20;
						_Player->Info.IGold = _Player->Info.IGold - 20;
						MenuScene(_Player);
					}
					else if (WChoice == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("������ ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						Store(_Player);
					}
				}
				else if ((Armor == 2 && _Player->Info.IGold < 20))
				{
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					MenuScene(_Player);
				}
				else if ((Armor == 3 && _Player->Info.IGold >= 40))
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�̳� �ܴ��� ���� ȿ�� : Def + 40\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");
					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("¯¯���� �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FDefense = _Player->Info.FDefense + 40;
						_Player->Info.IGold = _Player->Info.IGold - 40;
						MenuScene(_Player);
					}
					else if (WChoice == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("������ ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						Store(_Player);
					}
				}
				else if ((Armor == 3 && _Player->Info.IGold < 40))
				{
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				MenuScene(_Player);
				}
				else if (Armor == 4)
				{
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				Store(_Player);
 }
				else
				{
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
 }
			}
			else if (Choiec == 3)
			{
			int Accessory = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("1. �콼 ���� 10 Gold\n2. ��ö ���� 20 Gold\n3. �ֻ�� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Accessory);
			system("cls");
			if (Accessory == 1 && _Player->Info.IGold >= 10)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�콼 ���� ȿ�� : HP + 10, MP + 10\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");

				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHP = _Player->Info.IHP + 10;
					_Player->Info.IMP = _Player->Info.IMP + 10;
					_Player->Info.IGold = _Player->Info.IGold - 10;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Accessory == 1 && _Player->Info.IGold < 10))
			{
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				MenuScene(_Player);
			}
			else if (Accessory == 2 && _Player->Info.IGold >= 20)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��ö ���� ȿ�� : HP + 20. MP + 20\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHP = _Player->Info.IHP + 20;
					_Player->Info.IMP = _Player->Info.IMP + 20;
					_Player->Info.IGold = _Player->Info.IGold - 20;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Accessory == 2 && _Player->Info.IGold < 20))
				{
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				MenuScene(_Player);
				}
			else if ((Accessory == 3 && _Player->Info.IGold >= 40))
				{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�ֻ�� ���� ȿ�� : HP + 40, MP + 40\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("¯¯���� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHP = _Player->Info.IHP + 40;
					_Player->Info.IMP = _Player->Info.IMP + 40;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
				}
			else if ((Accessory == 3 && _Player->Info.IGold < 40))
				{
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				MenuScene(_Player);
				}
			else if (Accessory == 4)
				{
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				Store(_Player);
 }
			else
				{
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
 }
 }
			else if (Choiec == 4)
			{
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				Store(_Player);
			}
			else
			{
			printf_s("�߸������ϼ̽��ϴ�.\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			Store(_Player);
			}
		}
		else if (_Player->Info.IClass == 2)
		{
		int Choiec = 0;
		system("cls");
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����ó��ȭ��\n���� : ");
		scanf_s("%d", &Choiec);
		system("cls");

 }
	}
}

void PlayerData(OBJECT* _Player) // �÷��̾� ����â
{
	if (_Player->Info.IClass == 1)
	{
		printf_s("����� ������ �����Դϴ�.\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %f\n", _Player->Info.FAttack);
		printf_s("Dtt : %f\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n", _Player->Info.ILevel);
		printf_s("Gold : %d\n", _Player->Info.IGold);
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("����� ������ �ü��Դϴ�.\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %f\n", _Player->Info.FAttack);
		printf_s("Dtt : %f\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n", _Player->Info.ILevel);
		printf_s("Gold : %d\n", _Player->Info.IGold);
	}
	else if (_Player->Info.IClass == 3)
	{
		printf_s("����� ������ �������Դϴ�.\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %f\n", _Player->Info.FAttack);
		printf_s("Dtt : %f\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n", _Player->Info.ILevel);
		printf_s("Gold : %d\n", _Player->Info.IGold);
	}

	int i = 0;
	printf_s("�޴��� ���ư��ǰŸ� 1�� �����ּ���. \n");
	scanf_s("%d", &i);
	
	switch (i)
	{
	case 1:
		system("cls");
		SceneState = Scene_Menu;
		break;
	default:
		printf_s("�߸� �����̽��ϴ�.");
		Sleep(2000);
		system("cls");
		PlayerData(_Player);
		break;
	}
}

void StageScene(OBJECT * _Player, OBJECT * _Enemy) // �������� ���Ϳ� ����
{
	SetPosition(Width, Height, (char*)"StageScene\n", 15);
	SetPosition(Width, Height, (char*)"1. ���� 2. ����\n", 15);
	SetPosition(Width, Height + 1, (char*)"���͸� �����ƽ��ϴ�.\n", 15);
	SetPosition(Width, Height + 2, (char*)"���� : ", 15);
	scanf_s("%d", &ISelect);


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
	SetPosition(Width, Height, (char*)"������ ������ �����ҷ��� �ϰ� �ֽ��ϴ�.\n", 15);
	SetPosition(Width, Height + 1, (char*)"���͸� ��� �������� ������ ��ġ���ּ���,\n", 15);
	Sleep(2000);
	system("cls");
	SceneState++;
}