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
const int Scene_Boss = 5;
const int Scene_Exit = 6;

int SceneState = 0;

int Check = 1;

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

	int IHPMedicine1;
	int IHPMedicine2;
	int IHPMedicine3;
	int IMPMedicine1;
	int IMPMedicine2;
	int IMPMedicine3;

	int IWeapon1;
	int IWeapon2;
	int IWeapon3;

	int IArmor1;
	int IArmor2;
	int IArmor3;

	int IAccessory1;
	int IAccessory2;
	int IAccessory3;

	int FAttack;
	int FDefense;
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
void InitializeEnemy(OBJECT* _Enemy, OBJECT* _Player);
void HideCursor();
void SetColor(int _Color);
void SetPosition(int _x, int _y, char* _str, int _Color);
void FirstScene();
void GameStrat();
void GameStory();
void PlayerData(OBJECT* _Player);
void Store(OBJECT* _Player);
void Battle(OBJECT* _Player, OBJECT* _Enemy);
void BasesBattle(OBJECT* _Player, OBJECT* _Enemy);
void EliteEnemy(OBJECT* _Enemy, OBJECT* _Player);
void BattleEnd(OBJECT* _Player, OBJECT* _Enemy);
void BossEnemy(OBJECT* _Enemy);
void Boss(OBJECT* _Player, OBJECT* _Enemy);
void BossBattle(OBJECT* _Player, OBJECT* _Enemy);
void WarriorSkill(OBJECT* _Player, OBJECT* _Enemy);
void ArcherSkill(OBJECT* _Player, OBJECT* _Enemy);
void LastScene();
void Medicine(OBJECT* _Player, OBJECT* _Enemy);

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
	InitializeEnemy(Monster, Player);

	DWORD dwTime = GetTickCount64(); // 1/1000 (1000���� 1��)
	int Delay = 1000;

	int UpCount = 0;
	
	while (true)
	{
		if (dwTime + Delay < GetTickCount64())
		{
			dwTime = GetTickCount64();

			system("cls");
			
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
	case Scene_Boss:
		Boss(_Player, _Enemy);
		break;
	case Scene_PlayerData:
		PlayerData(_Player);
		break;
	case Scene_Exit:
		exit(NULL);
		break;
	}
}

void MenuScene(OBJECT* _Player)
{
	printf_s("Player : %s\n", _Player->Name);
	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}
	printf_s("MenuScene\n");

	printf_s("1. �̵�\n2. ����\n3. ����â\n4. ���� ��\n5. ����\n�Է� : ");

	int i = 0;
	scanf_s("%d", &i);

	if (i == 1)
		SceneState = Scene_Stage;
	else if (i == 2)
		SceneState = Scene_Store;
	else if (i == 3)
		SceneState = Scene_PlayerData;
	else if (i == 4)
		SceneState = Scene_Boss;
	else if (i == 5)
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
	
	SetPosition(Width, Height, (char*)"1.���� 2.�ü� \n", 15);
	SetPosition(Width, Height + 1, (char*)"������ �������ּ��� : ", 15);
	scanf_s("%d", &i);
	system("cls");
	
		if (i == 1)
		{
			_Warrior->Name = SetName();

			_Warrior->Info.IClass = 1;
			_Warrior->Info.ILevel = 1;
			_Warrior->Info.FAttack = 40000 + _Warrior->Info.ILevel * 5;
			_Warrior->Info.FDefense = 10 + _Warrior->Info.ILevel * 5;
			_Warrior->Info.IExp = 0;
			_Warrior->Info.IHP = 10000 + _Warrior->Info.ILevel * 15;
			_Warrior->Info.IMP = 50 + _Warrior->Info.ILevel * 15;
			_Warrior->Info.IGold = 100;

			_Warrior->Info.IHPMedicine1 = 0;
			_Warrior->Info.IHPMedicine2 = 0;
			_Warrior->Info.IHPMedicine3 = 0;
			_Warrior->Info.IMPMedicine1 = 0;
			_Warrior->Info.IMPMedicine2 = 0;
			_Warrior->Info.IMPMedicine3 = 0;

			_Warrior->Info.IWeapon1 = 0;
			_Warrior->Info.IWeapon2 = 0;
			_Warrior->Info.IWeapon3 = 0;

			_Warrior->Info.IArmor1 = 0;
			_Warrior->Info.IArmor2 = 0;
			_Warrior->Info.IArmor3 = 0;

			_Warrior->Info.IAccessory1 = 0;
			_Warrior->Info.IAccessory2 = 0;
			_Warrior->Info.IAccessory3 = 0;
			
			SetPosition(Width, Height, (char*)"����� ������ �����Դϴ�. \n", 15);
		}
		else if (i == 2)
		{
			_Archer->Name = SetName();

			_Archer->Info.IClass = 2;
			_Archer->Info.ILevel = 1;
			_Archer->Info.FAttack = 20 + (_Archer->Info.ILevel * 10);
			_Archer->Info.FDefense = 5 + (_Archer->Info.ILevel * 5);
			_Archer->Info.IExp = 0;
			_Archer->Info.IHP = 80 + (_Archer->Info.ILevel * 10);
			_Archer->Info.IMP = 50 + (_Archer->Info.ILevel * 10);
			_Archer->Info.IGold = 20;
			_Archer->Info.IHPMedicine1 = 0;
			_Archer->Info.IHPMedicine2 = 0;
			_Archer->Info.IHPMedicine3 = 0;
			_Archer->Info.IMPMedicine1 = 0;
			_Archer->Info.IMPMedicine2 = 0;
			_Archer->Info.IMPMedicine3 = 0;

			_Archer->Info.IHPMedicine1 = 0;
			_Archer->Info.IHPMedicine2 = 0;
			_Archer->Info.IHPMedicine3 = 0;
			_Archer->Info.IMPMedicine1 = 0;
			_Archer->Info.IMPMedicine2 = 0;
			_Archer->Info.IMPMedicine3 = 0;

			_Archer->Info.IWeapon1 = 0;
			_Archer->Info.IWeapon2 = 0;
			_Archer->Info.IWeapon3 = 0;

			_Archer->Info.IArmor1 = 0;
			_Archer->Info.IArmor2 = 0;
			_Archer->Info.IArmor3 = 0;

			_Archer->Info.IAccessory1 = 0;
			_Archer->Info.IAccessory2 = 0;
			_Archer->Info.IAccessory3 = 0;
			SetPosition(Width, Height, (char*)"����� ������ �ü��Դϴ�. \n", 15);
		}
		else
		{
			SetPosition(Width, Height, (char*)"������ �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���.\n", 15);
			Sleep(3000);
			system("cls");
			InitializePlayer(_Warrior, _Archer, _Magician);
		}
}

void InitializeEnemy(OBJECT* _Enemy, OBJECT* _Player)
{
	_Enemy->Name = (char*)"���";

	_Enemy->Info.IClass = 1;
	_Enemy->Info.ILevel = _Player->Info.ILevel;
	_Enemy->Info.FAttack = 5 + (_Enemy->Info.ILevel * 5);
	_Enemy->Info.FDefense = 15 + (_Enemy->Info.ILevel * 5);
	_Enemy->Info.IExp = 2;
	_Enemy->Info.IHP = 30 + (_Enemy->Info.ILevel * 15);
	_Enemy->Info.IMP = 5 + (_Enemy->Info.ILevel * 15);
	_Enemy->Info.IGold = 10;
}

void EliteEnemy(OBJECT* _Enemy, OBJECT* _Player)
{
	_Enemy->Name = (char*)"�ٸ�Ʈ ��";

	_Enemy->Info.IClass = 2;
	_Enemy->Info.ILevel = _Player->Info.ILevel;
	_Enemy->Info.FAttack = 8 + (_Enemy->Info.ILevel * 7);
	_Enemy->Info.FDefense = 22 + (_Enemy->Info.ILevel * 7);
	_Enemy->Info.IExp = 3;
	_Enemy->Info.IHP = 35 + (_Enemy->Info.ILevel * 20);
	_Enemy->Info.IMP = 10 + (_Enemy->Info.ILevel * 15);
	_Enemy->Info.IGold = 20;
}

void BossEnemy(OBJECT* _Enemy)
{
	_Enemy->Name = (char*)"����";

	_Enemy->Info.IClass = 3;
	_Enemy->Info.ILevel = 10;
	_Enemy->Info.FAttack = 250;
	_Enemy->Info.FDefense = 250;
	_Enemy->Info.IExp = 0;
	_Enemy->Info.IHP = 2000;
	_Enemy->Info.IMP = 1000;
	_Enemy->Info.IGold = 0;

}

void Boss(OBJECT* _Player, OBJECT* _Enemy)
{
	int n = 0;
	printf_s("Player : %s\n", _Player->Name);

	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}

	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}

	printf_s("�����濡 �����ϼ̽��ϴ�.\n");
	printf_s("1. ����â\n2. ����\n");
	printf_s("���� : ");
	scanf_s("%d", &n);
	system("cls");

	if (n == 1)
	{
		if (_Player->Info.IClass == 1)
		{
			BossBattle(_Player, _Enemy);
		}
		else if (_Player->Info.IClass == 2)
		{
			BossBattle(_Player, _Enemy);
		}
	}

	else if (n == 2)
	{
		time_t tTime = time(NULL);
		int Rand = rand() % 3;

		if (Rand == 1)
		{
			if (_Player->Info.IClass == 1)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("���θ޴��� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (_Player->Info.IClass == 2)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("���θ޴��� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
		}
		else
		{
			if (_Player->Info.IClass == 1)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("������ �����մϴ�.\n");
				Sleep(1000);
				system("cls");
				BossBattle(_Player, _Enemy);
			}
			else if (_Player->Info.IClass == 2)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("������ �����մϴ�.\n");
				Sleep(1000);
				system("cls");
				BossBattle(_Player, _Enemy);
			}
		}
	}
	else
	{
		printf_s("�߸� �����̽��ϴ�.\n");
		printf_s("���� â���� ���ư��ϴ�.\n");
		Sleep(1000);
		system("cls");
		Boss(_Player, _Enemy);
	}
}

void BossBattle(OBJECT* _Player, OBJECT* _Enemy)
{
	BossEnemy(_Enemy);
	int n = 0;

	printf_s("Player : %s\n", _Player->Name);

	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}

	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}

	printf_s("���Ϳ� ������ �����մϴ�.\n");
	printf_s("���� ����\n");
	printf_s("Name : %s\n", _Enemy->Name);
	printf_s("HP : %d\n", _Enemy->Info.IHP);
	printf_s("MP : %d\n", _Enemy->Info.IMP);
	printf_s("Att : %d\n", _Enemy->Info.FAttack);
	printf_s("Dtt : %d\n", _Enemy->Info.FDefense);
	printf_s("Exp : %d\n", _Enemy->Info.IExp);
	printf_s("Level : %d\n", _Enemy->Info.ILevel);

	printf_s("�÷��̾� ����\n");
	if (_Player->Info.IClass == 1)
	{
		printf_s("Name : %s\n", _Player->Name);
		printf_s("Class : ����\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %d\n", _Player->Info.FAttack);
		printf_s("Dtt : %d\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n\n", _Player->Info.ILevel);
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("Name : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %d\n", _Player->Info.FAttack);
		printf_s("Dtt : %d\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n\n", _Player->Info.ILevel);
	}

	printf_s("1. �⺻ ����\n2. ��ų\n3. ����\n���� : ");
	scanf_s("%d", &n);
	system("cls");

	if (n == 1)
	{
		Battle(_Player, _Enemy);
		BattleEnd(_Player, _Enemy);
	}

	else if (n == 2)
	{
		if (_Player->Info.IClass == 1)
		{
			WarriorSkill(_Player, _Enemy);
		}
		else if (_Player->Info.IClass == 2)
		{
			ArcherSkill(_Player, _Enemy);
		}
	}
	else if (n == 3)
	{
		Medicine(_Player, _Enemy);
	}

	else
	{
		printf_s("�߸� �����̽��ϴ�.\n");
		printf_s("���� â���� ���ư��ϴ�.\n");
		Sleep(1000);
		system("cls");
		BossBattle(_Player, _Enemy);
	}
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
	printf_s("Player : %s\n", _Player->Name);
	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}
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
			printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����\n5. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Choiec);
			system("cls");

			if (Choiec == 1)
			{
				int Weapon = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("1. �콼 �� 10 Gold\n2. ��ö �� 20 Gold\n3. �ֻ�� �� 40 Gold\n4. ����ó��ȭ��\n���� : ");
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
						_Player->Info.IWeapon1++;
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
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else if ((Weapon == 1 && _Player->Info.IGold < 10))
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
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
						_Player->Info.IWeapon2++;
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
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else if ((Weapon == 2 && _Player->Info.IGold < 20))
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if ((Weapon == 3 && _Player->Info.IGold >= 40))
				{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�ֻ�� �� ȿ�� : Att + 40\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ���� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FAttack = _Player->Info.FAttack + 40;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					_Player->Info.IWeapon3++;
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
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
 }
				else if ((Weapon == 3 && _Player->Info.IGold < 40))
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
				}
				else if (Weapon == 4)
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
 }
				else
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
 }
			}
			else if (Choiec == 2)
			{
				int Armor = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("1. �콼 ���� 10 Gold\n2. ��ö ���� 20 Gold\n3. �ֻ�� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
				scanf_s("%d", &Armor);
				system("cls");
				if (Armor == 1 && _Player->Info.IGold >= 10)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ���� ȿ�� : Def + 10\n");
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
						_Player->Info.FDefense = _Player->Info.FDefense + 10;
						_Player->Info.IGold = _Player->Info.IGold - 10;
						_Player->Info.IArmor1++;
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
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else if ((Armor == 1 && _Player->Info.IGold < 10))
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
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
						_Player->Info.IArmor2++;
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
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else if ((Armor == 2 && _Player->Info.IGold < 20))
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if ((Armor == 3 && _Player->Info.IGold >= 40))
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ���� ȿ�� : Def + 40\n");
					printf_s("1. ����\n2. ���\n");
					printf_s("�����Ͻðڽ��ϱ�? : ");
					scanf_s("%d", &WChoice);
					system("cls");
					if (WChoice == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ֻ�� ������ �����߽��ϴ�.\n");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						_Player->Info.FDefense = _Player->Info.FDefense + 40;
						_Player->Info.IGold = _Player->Info.IGold - 40;
						_Player->Info.IArmor3++;
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
						Store(_Player);
					}
				}
				else if ((Armor == 3 && _Player->Info.IGold < 40))
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
				}
				else if (Armor == 4)
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
 }
				else
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
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
					_Player->Info.IAccessory1++;
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
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else if ((Accessory == 1 && _Player->Info.IGold < 10))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
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
					_Player->Info.IAccessory2++;
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
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else if ((Accessory == 2 && _Player->Info.IGold < 20))
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
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
					printf_s("�ֻ�� ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHP = _Player->Info.IHP + 40;
					_Player->Info.IMP = _Player->Info.IMP + 40;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					_Player->Info.IAccessory3++;
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
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				}
			else if ((Accessory == 3 && _Player->Info.IGold < 40))
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
				}
			else if (Accessory == 4)
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
 }
			else
				{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
 }
 }
			else if (Choiec == 4)
			{
				int Medicine = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("ü�� ���� : 1. �ϱ� ü�� ���� 1Gold 2. �߱� ü�� ���� 2Gold 3. ��� ü�� ���� 3Gold\n");
				printf_s("���� ���� : 4. �ϱ� ���� ���� 1Gold 5. �߱� ���� ���� 2Gold 6. ��� ���� ���� 3Gold\n���� : ");
				scanf_s("%d", &Medicine);
				system("cls");
				if (Medicine == 1 && _Player->Info.IGold >= 1)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ϱ� ü�� ���� ȿ�� : 10HP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("�ϱ� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHPMedicine1 = _Player->Info.IHPMedicine1 + n;
					_Player->Info.IGold = _Player->Info.IGold - n;
					MenuScene(_Player);
				}
				else if (Medicine == 1 && _Player->Info.IGold < 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (Medicine == 2 && _Player->Info.IGold >= 2)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߱� ü�� ���� ȿ�� : 20HP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("�߱� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHPMedicine2 = _Player->Info.IHPMedicine2 + n;
					_Player->Info.IGold = _Player->Info.IGold - (2 * n);
					MenuScene(_Player);
				}
				else if (Medicine == 2 && _Player->Info.IGold < 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (Medicine == 3 && _Player->Info.IGold >= 3)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��� ü�� ���� ȿ�� : 30HP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("��� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IHPMedicine3 = _Player->Info.IHPMedicine3 + n;
					_Player->Info.IGold = _Player->Info.IGold - (3 * n);
					MenuScene(_Player);
				}
				else if (Medicine == 3 && _Player->Info.IGold < 3)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (Medicine == 4 && _Player->Info.IGold >= 1)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ϱ� ���� ���� ȿ�� : 10MP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("�ϱ� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IMPMedicine1 = _Player->Info.IMPMedicine1 + n;
					_Player->Info.IGold = _Player->Info.IGold - n;
					MenuScene(_Player);
				}
				else if (Medicine == 4 && _Player->Info.IGold < 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (Medicine == 5 && _Player->Info.IGold >= 2)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߱� ���� ���� ȿ�� : 20MP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("�߱� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IMPMedicine2 = _Player->Info.IMPMedicine2 + n;
					_Player->Info.IGold = _Player->Info.IGold - (2 * n);
					MenuScene(_Player);
				}
				else if (Medicine == 5 && _Player->Info.IGold < 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (Medicine == 6 && _Player->Info.IGold >= 3)
				{
					int n;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��� ���� ���� ȿ�� : 30MP ȸ��\n");
					printf_s("���� �� ������ �Է����ּ���. : ");
					scanf_s("%d", &n);
					printf_s("��� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.IMPMedicine1 = _Player->Info.IMPMedicine1 + n;
					_Player->Info.IGold = _Player->Info.IGold - (3 * n);
					MenuScene(_Player);
				}
				else if (Medicine == 6 && _Player->Info.IGold < 3)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��尡 �����մϴ�. \n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
				}
			}
			else if (Choiec == 5)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("�߸������ϼ̽��ϴ�.\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
			}
		}
		else if (_Player->Info.IClass == 2)
		{
		int Choiec = 0;
		system("cls");
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����\n5. ����ó��ȭ��\n���� : ");
		scanf_s("%d", &Choiec);
		system("cls");

		if (Choiec == 1)
		{
			int Weapon = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("1. �콼 Ȱ 10 Gold\n2. ��ö Ȱ 20 Gold\n3. �ֻ�� Ȱ 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Weapon);
			system("cls");

			if (Weapon == 1 && _Player->Info.IGold >= 10)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�콼 Ȱ ȿ�� : Att + 15\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");

				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�콼 Ȱ�� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FAttack = _Player->Info.FAttack + 15;
					_Player->Info.IGold = _Player->Info.IGold - 10;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Weapon == 1 && _Player->Info.IGold < 10))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Weapon == 2 && _Player->Info.IGold >= 20)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��ö Ȱ ȿ�� : Att + 30\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("��ö Ȱ�� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FAttack = _Player->Info.FAttack + 30;
					_Player->Info.IGold = _Player->Info.IGold - 20;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Weapon == 2 && _Player->Info.IGold < 20))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if ((Weapon == 3 && _Player->Info.IGold >= 40))
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ֻ�� Ȱ ȿ�� : Att + 55\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� Ȱ�� �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FAttack = _Player->Info.FAttack + 55;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Weapon == 3 && _Player->Info.IGold < 40))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Weapon == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
			}
		}
		else if (Choiec == 2)
		{
			int Armor = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("1. ���� ���� ���� 10 Gold\n2. ����� ���� ���� 20 Gold\n3. �ֻ�� ���� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Armor);
			system("cls");
			if (Armor == 1 && _Player->Info.IGold >= 10)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("���� ���� ���� ȿ�� : Daf + 5\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");

				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("���� ���� ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FDefense = _Player->Info.FDefense + 5;
					_Player->Info.IGold = _Player->Info.IGold - 10;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Armor == 1 && _Player->Info.IGold < 10))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Armor == 2 && _Player->Info.IGold >= 20)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����� ���� ���� ȿ�� : Def + 10\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("����� ���� ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FDefense = _Player->Info.FDefense + 10;
					_Player->Info.IGold = _Player->Info.IGold - 20;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Armor == 2 && _Player->Info.IGold < 20))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if ((Armor == 3 && _Player->Info.IGold >= 40))
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ֻ��  ���� ���� ȿ�� : Def + 25\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� ���� ������ �����߽��ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					_Player->Info.FDefense = _Player->Info.FDefense + 25;
					_Player->Info.IGold = _Player->Info.IGold - 40;
					MenuScene(_Player);
				}
				else if (WChoice == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else if ((Armor == 3 && _Player->Info.IGold < 40))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Armor == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
			}
		}
		else if (Choiec == 3)
		{
			int Accessory = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("1. �콼 ���� 10 Gold\n2. ��ö ���� 20 Gold\n3. �ֻ�� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Accessory);
			system("cls");
			if (Accessory == 1 && _Player->Info.IGold >= 10)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�콼 ���� ȿ�� : HP + 10, MP + 10\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");

				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
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
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Accessory == 1 && _Player->Info.IGold < 10))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Accessory == 2 && _Player->Info.IGold >= 20)
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��ö ���� ȿ�� : HP + 20. MP + 20\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
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
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Accessory == 2 && _Player->Info.IGold < 20))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if ((Accessory == 3 && _Player->Info.IGold >= 40))
			{
				int WChoice = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ֻ�� ���� ȿ�� : HP + 40, MP + 40\n");
				printf_s("1. ����\n2. ���\n");
				printf_s("�����Ͻðڽ��ϱ�? : ");
				scanf_s("%d", &WChoice);
				system("cls");
				if (WChoice == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� ������ �����߽��ϴ�.\n");
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
					printf_s("Class : �ü�\n");
					printf_s("������ ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					Store(_Player);
				}
			}
			else if ((Accessory == 3 && _Player->Info.IGold < 40))
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Accessory == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
			}
		}
		else if (Choiec == 4)
		{
			int Medicine = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("ü�� ���� : 1. �ϱ� ü�� ���� 1Gold 2. �߱� ü�� ���� 2Gold 3. ��� ü�� ���� 3Gold\n");
			printf_s("���� ���� : 4. �ϱ� ���� ���� 1Gold 5. �߱� ���� ���� 2Gold 6. ��� ���� ���� 3Gold\n���� : ");
			scanf_s("%d", &Medicine);
			system("cls");
			if (Medicine == 1 && _Player->Info.IGold >= 1)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ϱ� ü�� ���� ȿ�� : 10HP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("�ϱ� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IHPMedicine1 = _Player->Info.IHPMedicine1 + n;
				_Player->Info.IGold = _Player->Info.IGold - n;
				MenuScene(_Player);
			}
			else if (Medicine == 1 && _Player->Info.IGold < 1)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Medicine == 2 && _Player->Info.IGold >= 2)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߱� ü�� ���� ȿ�� : 20HP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("�߱� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IHPMedicine2 = _Player->Info.IHPMedicine2 + n;
				_Player->Info.IGold = _Player->Info.IGold - (2 * n);
				MenuScene(_Player);
			}
			else if (Medicine == 2 && _Player->Info.IGold < 2)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Medicine == 3 && _Player->Info.IGold >= 3)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��� ü�� ���� ȿ�� : 30HP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("��� ü�� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IHPMedicine3 = _Player->Info.IHPMedicine3 + n;
				_Player->Info.IGold = _Player->Info.IGold - (3 * n);
				MenuScene(_Player);
			}
			else if (Medicine == 3 && _Player->Info.IGold < 3)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Medicine == 4 && _Player->Info.IGold >= 1)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ϱ� ���� ���� ȿ�� : 10MP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("�ϱ� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IMPMedicine1 = _Player->Info.IMPMedicine1 + n;
				_Player->Info.IGold = _Player->Info.IGold - n;
				MenuScene(_Player);
			}
			else if (Medicine == 4 && _Player->Info.IGold < 1)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Medicine == 5 && _Player->Info.IGold >= 2)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߱� ���� ���� ȿ�� : 20MP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("�߱� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IMPMedicine2 = _Player->Info.IMPMedicine2 + n;
				_Player->Info.IGold = _Player->Info.IGold - (2 * n);
				MenuScene(_Player);
			}
			else if (Medicine == 5 && _Player->Info.IGold < 2)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (Medicine == 6 && _Player->Info.IGold >= 3)
			{
				int n;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��� ���� ���� ȿ�� : 30MP ȸ��\n");
				printf_s("���� �� ������ �Է����ּ���. : ");
				scanf_s("%d", &n);
				printf_s("��� ���� ������ %d�� �����ϼ̽��ϴ�.\n", n);
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				_Player->Info.IMPMedicine1 = _Player->Info.IMPMedicine1 + n;
				_Player->Info.IGold = _Player->Info.IGold - (3 * n);
				MenuScene(_Player);
			}
			else if (Medicine == 6 && _Player->Info.IGold < 3)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��尡 �����մϴ�. \n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߸� �����ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
			}
		}
		else if (Choiec == 5)
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
		}
		else
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("�߸������ϼ̽��ϴ�.\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
		}
		}
	}
	else if (n == 2)
	{
	if (_Player->Info.IClass == 1)
	{
		int Choiec = 0;
		system("cls");
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : ����\n");
		printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����\n5. ����ó��ȭ��\n���� : ");
		scanf_s("%d", &Choiec);
		system("cls");

		if (Choiec == 1)
		{
			int Weapon = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("1. �콼 �� 10 Gold\n2. ��ö �� 20 Gold\n3. �ֻ�� �� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Weapon);
			system("cls");

			if (Weapon == 1)
			{
				if (_Player->Info.IWeapon1 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ���� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�콼 ���� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 10;
						_Player->Info.IGold = _Player->Info.IGold + 10;
						_Player->Info.IWeapon1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ���� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
			}
			else if (Weapon == 2)
			{
				if (_Player->Info.IWeapon2 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ���� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("��ö ���� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 20;
						_Player->Info.IGold = _Player->Info.IGold + 20;
						_Player->Info.IWeapon2--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ���� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Weapon == 3)
			{
				if (_Player->Info.IWeapon3 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ���� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ֻ�� ���� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 40;
						_Player->Info.IGold = _Player->Info.IGold + 40;
						_Player->Info.IWeapon3--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ���� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Weapon == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸������ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
		}
		else if (Choiec == 2)
		{
			int Armor = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("1. �콼 ���� 10 Gold\n2. ��ö ���� 20 Gold\n3. �ֻ�� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Armor);
			system("cls");
			if (Armor == 1)
			{
				if (_Player->Info.IArmor1 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�콼 ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 10;
						_Player->Info.IGold = _Player->Info.IGold + 10;
						_Player->Info.IArmor1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 2)
			{
				if (_Player->Info.IArmor2 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("��ö ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 20;
						_Player->Info.IGold = _Player->Info.IGold + 20;
						_Player->Info.IArmor2--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 3)
			{
				if (_Player->Info.IArmor3 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ֻ�� ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 40;
						_Player->Info.IGold = _Player->Info.IGold + 40;
						_Player->Info.IArmor3--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸������ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
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

			if (Accessory == 1)
			{
				if (_Player->Info.IAccessory1 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�콼 ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.IHP = _Player->Info.IHP - 10;
						_Player->Info.IMP = _Player->Info.IMP - 10;
						_Player->Info.IGold = _Player->Info.IGold + 10;
						_Player->Info.IAccessory1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�콼 ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Accessory == 2)
			{
				if (_Player->Info.IAccessory2 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("��ö ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.IHP = _Player->Info.IHP - 20;
						_Player->Info.IMP = _Player->Info.IMP - 20;
						_Player->Info.IGold = _Player->Info.IGold + 20;
						_Player->Info.IAccessory2--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("��ö ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Accessory == 3)
			{
				if (_Player->Info.IAccessory1 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ֻ�� ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.IHP = _Player->Info.IHP - 40;
						_Player->Info.IMP = _Player->Info.IMP - 40;
						_Player->Info.IGold = _Player->Info.IGold + 40;
						_Player->Info.IAccessory1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�ֻ�� ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Accessory == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("�߸������ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
		}
	}
	else if (_Player->Info.IClass == 2)
	{
		int Choiec = 0;
		system("cls");
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("1. ����\n2. ��\n3. ��ű�\n4. ����\n5. ����ó��ȭ��\n���� : ");
		scanf_s("%d", &Choiec);
		system("cls");

		if (Choiec == 1)
		{
			int Weapon = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("1. �콼 Ȱ 10 Gold\n2. ��ö Ȱ 20 Gold\n3. �ֻ�� Ȱ 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Weapon);
			system("cls");

			if (Weapon == 1)
			{
				if (_Player->Info.IWeapon1 > 0)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�콼 Ȱ�� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &WChoice);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�콼 Ȱ�� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 15;
						_Player->Info.IGold = _Player->Info.IGold + 10;
						_Player->Info.IWeapon1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�콼 Ȱ�� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
			}

			else if (Weapon == 2)
			{
				if (_Player->Info.IWeapon2 > 0)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("��ö Ȱ�� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &WChoice);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("��ö Ȱ�� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 30;
						_Player->Info.IGold = _Player->Info.IGold + 20;
						_Player->Info.IWeapon2--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}

					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}

					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}

				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("��ö Ȱ�� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
			}

			else if (Weapon == 3)
			{
				if (_Player->Info.IWeapon3 > 0)
				{
					int WChoice = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� Ȱ�� �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &WChoice);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ֻ�� Ȱ�� �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FAttack = _Player->Info.FAttack - 55;
						_Player->Info.IGold = _Player->Info.IGold + 30;
						_Player->Info.IWeapon3--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}

					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}

					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� Ȱ�� �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
 }

			else if (Weapon == 4)
			{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
 }
			else
			{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("�߸������ϼ̽��ϴ�.\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
			}

		}

		else if (Choiec == 2)
		{
			int Armor = 0;
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("1. ���� ���� ���� 10 Gold\n2. ����� ���� ���� 20 Gold\n3. �ֻ�� ���� ���� 40 Gold\n4. ����ó��ȭ��\n���� : ");
			scanf_s("%d", &Armor);
			system("cls");
			if (Armor == 1)
			{
				if (_Player->Info.IArmor1 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("���� ���� ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ñ�\n");
						printf_s("���� ���� ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 5;
						_Player->Info.IGold = _Player->Info.IGold + 10;
						_Player->Info.IArmor1--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("���� ���� ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 2)
			{
				if (_Player->Info.IArmor2 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("��ö ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : ����\n");
						printf_s("����� ���� ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 10;
						_Player->Info.IGold = _Player->Info.IGold + 20;
						_Player->Info.IArmor2--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("����� ���� ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 3)
			{
				if (_Player->Info.IArmor3 > 0)
				{
					int n = 0;
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� ���� ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
					scanf_s("%d", &n);
					system("cls");

					if (n == 1)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ֻ�� ���� ������ �Ǹ� �Ǿ����ϴ�.");
						printf_s("MenuScene�� ���ư��ϴ�.\n");
						_Player->Info.FDefense = _Player->Info.FDefense - 25;
						_Player->Info.IGold = _Player->Info.IGold + 40;
						_Player->Info.IArmor3--;
						Sleep(1000);
						system("cls");
						MenuScene(_Player);
					}
					else if (n == 2)
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�ǸŸ� ����߽��ϴ�. \n");
						printf_s("����â���� �ǵ��ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
					else
					{
						printf_s("Player : %s\n", _Player->Name);
						printf_s("Class : �ü�\n");
						printf_s("�߸� �����ϼ̽��ϴ�.\n");
						printf_s("����â���� ���ư��ϴ�.\n");
						Sleep(1000);
						system("cls");
						Store(_Player);
					}
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ��  ���� ������ �����ϴ�.\n");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					Sleep(1000);
					MenuScene(_Player);
				}
			}
			else if (Armor == 4)
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�߸������ϼ̽��ϴ�.\n");
				printf_s("����â���� �ǵ��ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				Store(_Player);
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

		if (Accessory == 1)
		{
			if (_Player->Info.IAccessory1 > 0)
			{
				int n = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�콼 ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
				scanf_s("%d", &n);
				system("cls");

				if (n == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�콼 ������ �Ǹ� �Ǿ����ϴ�.");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					_Player->Info.IHP = _Player->Info.IHP - 10;
					_Player->Info.IMP = _Player->Info.IMP - 10;
					_Player->Info.IGold = _Player->Info.IGold + 10;
					_Player->Info.IAccessory1--;
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (n == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ǸŸ� ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�콼 ������ �����ϴ�.\n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				MenuScene(_Player);
			}
		}
		else if (Accessory == 2)
		{
			if (_Player->Info.IAccessory2 > 0)
			{
				int n = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��ö ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
				scanf_s("%d", &n);
				system("cls");

				if (n == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("��ö ������ �Ǹ� �Ǿ����ϴ�.");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					_Player->Info.IHP = _Player->Info.IHP - 20;
					_Player->Info.IMP = _Player->Info.IMP - 20;
					_Player->Info.IGold = _Player->Info.IGold + 20;
					_Player->Info.IAccessory2--;
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (n == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ǸŸ� ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("��ö ������ �����ϴ�.\n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				MenuScene(_Player);
			}
		}
		else if (Accessory == 3)
		{
			if (_Player->Info.IAccessory1 > 0)
			{
				int n = 0;
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ֻ�� ������ �Ǹ�\n1. �Ǹ��ϱ�\n2. ����ϱ�\n���� : ");
				scanf_s("%d", &n);
				system("cls");

				if (n == 1)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ֻ�� ������ �Ǹ� �Ǿ����ϴ�.");
					printf_s("MenuScene�� ���ư��ϴ�.\n");
					_Player->Info.IHP = _Player->Info.IHP - 40;
					_Player->Info.IMP = _Player->Info.IMP - 40;
					_Player->Info.IGold = _Player->Info.IGold + 40;
					_Player->Info.IAccessory1--;
					Sleep(1000);
					system("cls");
					MenuScene(_Player);
				}
				else if (n == 2)
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("�ǸŸ� ����߽��ϴ�. \n");
					printf_s("����â���� �ǵ��ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
				else
				{
					printf_s("Player : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("�߸� �����ϼ̽��ϴ�.\n");
					printf_s("����â���� ���ư��ϴ�.\n");
					Sleep(1000);
					system("cls");
					Store(_Player);
				}
			}
			else
			{
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("�ֻ�� ������ �����ϴ�.\n");
				printf_s("MenuScene�� ���ư��ϴ�.\n");
				Sleep(1000);
				MenuScene(_Player);
			}
		}
		else if (Accessory == 4)
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
		}
		else
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("�߸������ϼ̽��ϴ�.\n");
			printf_s("����â���� �ǵ��ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			Store(_Player);
		}
 }
	}
}
	else if (n == 3)
	{
	printf_s("���θ޴��� ���ư��ϴ�.\n");
	Sleep(1000);
	system("cls");
	MenuScene(_Player);
 }
}

void PlayerData(OBJECT* _Player) // �÷��̾� ����â
{
	if (_Player->Info.IClass == 1)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("����� ������ �����Դϴ�.\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %d\n", _Player->Info.FAttack);
		printf_s("Dtt : %d\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n", _Player->Info.ILevel);
		printf_s("Gold : %d\n", _Player->Info.IGold);
		printf_s("�ϱ� ü�� ���� : %d\n", _Player->Info.IHPMedicine1);
		printf_s("�߱� ü�� ���� : %d\n", _Player->Info.IHPMedicine2);
		printf_s("��� ü�� ���� : %d\n", _Player->Info.IHPMedicine3);
		printf_s("�ϱ� ���� ���� : %d\n", _Player->Info.IMPMedicine1);
		printf_s("�߱� ���� ���� : %d\n", _Player->Info.IMPMedicine2);
		printf_s("��� ���� ���� : %d\n\n", _Player->Info.IMPMedicine3);
		printf_s("���� ���\n");

		if (_Player->Info.IWeapon1 > 0)
		{
			printf_s("�콼 �� * %d\n", _Player->Info.IWeapon1);
			printf_s("ȿ�� : Att + 10 * %d\n\n", _Player->Info.IWeapon1);
		}

		if (_Player->Info.IWeapon2 > 0)
		{
			printf_s("��ö �� * %d\n", _Player->Info.IWeapon2);
			printf_s("ȿ�� : Att + 20 * %d\n\n", _Player->Info.IWeapon2);
		}

		if (_Player->Info.IWeapon3 > 0)
		{
			printf_s("�ֻ�� �� * %d\n", _Player->Info.IWeapon3);
			printf_s("ȿ�� : Att + 40 * %d\n\n", _Player->Info.IWeapon3);
		}

		if (_Player->Info.IWeapon1 < 1 && _Player->Info.IWeapon2 < 1 && _Player->Info.IWeapon3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		if (_Player->Info.IArmor1 > 0)
		{
			printf_s("�콼 ���� * %d\n", _Player->Info.IArmor1);
			printf_s("ȿ�� : Def + 10 * %d\n\n", _Player->Info.IArmor1);
		}

		if (_Player->Info.IArmor2 > 0)
		{
			printf_s("��ö ���� * %d\n", _Player->Info.IArmor2);
			printf_s("ȿ�� : Def + 20 * %d\n\n", _Player->Info.IArmor2);
		}

		if (_Player->Info.IArmor3 > 0)
		{
			printf_s("�ֻ�� ���� * %d\n", _Player->Info.IArmor3);
			printf_s("ȿ�� : Def + 40 * %d\n\n", _Player->Info.IArmor3);
		}

		if (_Player->Info.IArmor1 < 1 && _Player->Info.IArmor2 < 1 && _Player->Info.IArmor3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		if (_Player->Info.IAccessory1 > 0)
		{
			printf_s("�콼 ���� * %d\n", _Player->Info.IAccessory1);
			printf_s("ȿ�� : HP + 10 * %d, MP + 10 * %d\n\n", _Player->Info.IAccessory1, _Player->Info.IAccessory1);
		}

		if (_Player->Info.IAccessory2 > 0)
		{
			printf_s("��ö ���� * %d\n", _Player->Info.IAccessory2);
			printf_s("ȿ�� : HP + 20 * %d, MP + 20 * %d\n\n", _Player->Info.IAccessory2, _Player->Info.IAccessory2);
		}

		if (_Player->Info.IAccessory3 > 0)
		{
			printf_s("�ֻ�� ���� * %d\n", _Player->Info.IAccessory3);
			printf_s("ȿ�� : HP + 40 * %d, MP + 40 * %d\n\n", _Player->Info.IAccessory3, _Player->Info.IAccessory3);
		}

		if (_Player->Info.IAccessory1 < 1 && _Player->Info.IAccessory2 < 1 && _Player->Info.IAccessory3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		int i = 0;
		printf_s("1. ��ųâ\n2. �޴�\n���� : ");
		scanf_s("%d", &i);

		if (i == 1)
		{
			int k = 0;
			system("cls");
			printf_s("Player : %s\n", _Player->Name);
			printf_s("����� ������ �����Դϴ�.\n");
			printf_s("���� ��ų ���\n");
			printf_s("1. ���� ����\nȿ�� : Att + 20, MP - 2\n\n");
			printf_s("2. ���� ����\nȿ�� : �ι� ����\n\n");
			printf_s("���θ޴��� ���ư��Ƕ�� 1�� �����ּ���.\n");
			scanf_s("%d", &k);
			switch (k)
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
		else if (i == 2)
		{
			system("cls");
			MenuScene(_Player);
		}
		else
		{
			printf_s("�߸� �����̽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			system("cls");
			PlayerData(_Player);
		}
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("����� ������ �ü��Դϴ�.\n");
		printf_s("HP : %d\n", _Player->Info.IHP);
		printf_s("MP : %d\n", _Player->Info.IMP);
		printf_s("Att : %d\n", _Player->Info.FAttack);
		printf_s("Dtt : %d\n", _Player->Info.FDefense);
		printf_s("Exp : %d\n", _Player->Info.IExp);
		printf_s("Level : %d\n", _Player->Info.ILevel);
		printf_s("Gold : %d\n", _Player->Info.IGold);
		printf_s("�ϱ� ü�� ���� : %d\n", _Player->Info.IHPMedicine1);
		printf_s("�߱� ü�� ���� : %d\n", _Player->Info.IHPMedicine2);
		printf_s("��� ü�� ���� : %d\n", _Player->Info.IHPMedicine3);
		printf_s("�ϱ� ���� ���� : %d\n", _Player->Info.IMPMedicine1);
		printf_s("�߱� ���� ���� : %d\n", _Player->Info.IMPMedicine2);
		printf_s("��� ���� ���� : %d\n\n", _Player->Info.IMPMedicine3);

		if (_Player->Info.IWeapon1 > 0)
		{
			printf_s("�콼 Ȱ * %d\n", _Player->Info.IWeapon1);
			printf_s("ȿ�� : Att + 15 * %d\n\n", _Player->Info.IWeapon1);
		}

		if (_Player->Info.IWeapon2 > 0)
		{
			printf_s("��ö Ȱ * %d\n", _Player->Info.IWeapon2);
			printf_s("ȿ�� : Att + 30 * %d\n\n", _Player->Info.IWeapon2);
		}

		if (_Player->Info.IWeapon3 > 0)
		{
			printf_s("�ֻ�� Ȱ * %d\n", _Player->Info.IWeapon3);
			printf_s("ȿ�� : Att + 40 * %d\n\n", _Player->Info.IWeapon3);
		}

		if (_Player->Info.IWeapon1 < 1 && _Player->Info.IWeapon2 < 1 && _Player->Info.IWeapon3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		if (_Player->Info.IArmor1 > 0)
		{
			printf_s("���� ���� ���� * %d\n", _Player->Info.IArmor1);
			printf_s("ȿ�� : Def + 5 * %d\n\n", _Player->Info.IArmor1);
		}

		if (_Player->Info.IArmor2 > 0)
		{
			printf_s("����� ���� ���� * %d\n", _Player->Info.IArmor2);
			printf_s("ȿ�� : Def + 10 * %d\n\n", _Player->Info.IArmor2);
		}

		if (_Player->Info.IArmor3 > 0)
		{
			printf_s("�ֻ�� ���� ���� * %d\n", _Player->Info.IArmor3);
			printf_s("ȿ�� : Def + 25 * %d\n\n", _Player->Info.IArmor3);
		}

		if (_Player->Info.IArmor1 < 1 && _Player->Info.IArmor2 < 1 && _Player->Info.IArmor3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		if (_Player->Info.IAccessory1 > 0)
		{
			printf_s("�콼 ���� * %d\n", _Player->Info.IAccessory1);
			printf_s("ȿ�� : HP + 10 * %d, MP + 10 * %d\n\n", _Player->Info.IAccessory1, _Player->Info.IAccessory1);
		}

		if (_Player->Info.IAccessory2 > 0)
		{
			printf_s("��ö ���� * %d\n", _Player->Info.IAccessory2);
			printf_s("ȿ�� : HP + 20 * %d, MP + 20 * %d\n\n", _Player->Info.IAccessory2, _Player->Info.IAccessory2);
		}

		if (_Player->Info.IAccessory3 > 0)
		{
			printf_s("�ֻ�� ���� * %d\n", _Player->Info.IAccessory3);
			printf_s("ȿ�� : HP + 40 * %d, MP + 40 * %d\n\n", _Player->Info.IAccessory3, _Player->Info.IAccessory3);
		}

		if (_Player->Info.IAccessory1 < 1 && _Player->Info.IAccessory2 < 1 && _Player->Info.IAccessory3 < 1)
		{
			printf_s("���� ����\n\n");
		}

		int i = 0;
		printf_s("1. ��ųâ\n2. �޴�\n���� : ");
		scanf_s("%d", &i);

		if (i == 1)
		{
			int k = 0;
			system("cls");
			printf_s("Player : %s\n", _Player->Name);
			printf_s("����� ������ �ü��Դϴ�.\n");
			printf_s("���� ��ų ���\n");
			printf_s("1. ���̾� �ַο�\nȿ�� : Att + 20, MP - 2\n\n");
			printf_s("2. ���� ��\nȿ�� : �ι� ����\n\n");
			printf_s("���θ޴��� ���ư��Ƕ�� 1�� �����ּ���.\n");
			scanf_s("%d", &k);
			switch (k)
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
		else if (i == 2)
		{
			system("cls");
			MenuScene(_Player);
		}
		else
		{
			printf_s("�߸� �����̽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			system("cls");
			PlayerData(_Player);
		}
	}
}

void ArcherSkill(OBJECT* _Player, OBJECT* _Enemy)
{
	int n = 0;
	printf_s("Player : %s\n", _Player->Name);
	printf_s("Class : �ü�\n");
	printf_s("�ü� ��ų ���\n\n");
	printf_s("1. ���̾� �ַο�\nȿ�� : Att, MP -2\n\n");
	printf_s("2. ���� ��\nȿ�� : �ι� ����, MP -3\n\n");
	printf_s("���� : ");
	scanf_s("%d", &n);
	system("cls");

	if (n == 1)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("1. ���̾� �ַο츦 ����մϴ�.\n");
		Sleep(1000);
		system("cls");
		_Player->Info.FAttack = _Player->Info.FAttack + 20;
		_Player->Info.IMP = _Player->Info.IMP - 2;
		Battle(_Player, _Enemy);
		_Player->Info.FAttack = _Player->Info.FAttack - 20;
		BattleEnd(_Player, _Enemy);
	}

	else if (n == 2)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("���� ���� ����մϴ�.\n");
		Sleep(1000);
		system("cls");
		_Player->Info.FAttack = _Player->Info.FAttack * 2;
		_Player->Info.IMP = _Player->Info.IMP - 3;
		Battle(_Player, _Enemy);
		_Player->Info.FAttack = _Player->Info.FAttack / 2;
		BattleEnd(_Player, _Enemy);
	}

	else
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : �ü�\n");
		printf_s("�߸� �����̽��ϴ�.\n");
		Sleep(1000);
	}
}

void WarriorSkill(OBJECT* _Player, OBJECT* _Enemy)
{
	int n = 0;
	printf_s("Player : %s\n", _Player->Name);
	printf_s("Class : ����\n");
	printf_s("���� ��ų ���\n\n");
	printf_s("1. ���� ����\nȿ�� : Att + 20, MP - 2\n\n");
	printf_s("2. ���� ����\nȿ�� : �ι� ����, MP - 3\n\n");
	printf_s("���� : ");
	scanf_s("%d", &n);
	system("cls");

	if (n == 1)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : ����\n");
		printf_s("���� ���� ��ų�� ����մϴ�.\n");
		Sleep(1000);
		system("cls");
		_Player->Info.FAttack = _Player->Info.FAttack + 20;
		_Player->Info.IMP = _Player->Info.IMP - 2;
		Battle(_Player, _Enemy);
		_Player->Info.FAttack = _Player->Info.FAttack - 20;
		BattleEnd(_Player, _Enemy);
	}

	else if (n == 2)
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : ����\n");
		printf_s("���Ӻ��� ��ų�� ����մϴ�.\n");
		Sleep(1000);
		system("cls");
		_Player->Info.FAttack = _Player->Info.FAttack * 2;
		_Player->Info.IMP = _Player->Info.IMP - 3;
		Battle(_Player, _Enemy);
		_Player->Info.FAttack = _Player->Info.FAttack / 2;
		BattleEnd(_Player, _Enemy);
	}
	
	else
	{
		printf_s("Player : %s\n", _Player->Name);
		printf_s("Class : ����\n");
		printf_s("�߸� �����̽��ϴ�.\n");
		Sleep(1000);
	}
}

void StageScene(OBJECT * _Player, OBJECT * _Enemy) // �������� ���Ϳ� ����
{
	int ISelect = 0;
	printf_s("Player : %s\n", _Player->Name);
	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}

	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}
	printf_s("StageScene\n");
	printf_s("���Ϳ� �����ƽ��ϴ�.\n");
	printf_s("1. ����â\n2. ����\n���� : ");
	scanf_s("%d", &ISelect);
	system("cls");

	if (ISelect == 1)
	{
		if (_Player->Info.IClass == 1)
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			BasesBattle(_Player, _Enemy);
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Player : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			BasesBattle(_Player, _Enemy);
		}
	}
	else if (ISelect == 2)
	{
		time_t tTime = time(NULL);
		int Rand = rand() % 3;

		if (Rand == 1 || Rand == 2)
		{
			if (_Player->Info.IClass == 1)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("���θ޴��� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else if (_Player->Info.IClass == 2)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("���θ޴��� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
		}
		else
		{
			if (_Player->Info.IClass == 1)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : ����\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("������ �����մϴ�.\n");
				Sleep(1000);
				system("cls");
				Battle(_Player, _Enemy);
			}
			else if (_Player->Info.IClass == 2)
			{
				system("cls");
				printf_s("Player : %s\n", _Player->Name);
				printf_s("Class : �ü�\n");
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("������ �����մϴ�.\n");
				Sleep(1000);
				system("cls");
				Battle(_Player, _Enemy);
			}
		}
	}
	else
	{
		printf_s("�߸� �����̽��ϴ�.\n");
		printf_s("�������� â���� ���ư��ϴ�.\n");
		Sleep(1000);
		system("cls");
		StageScene(_Player, _Enemy);
	}
}

void BattleEnd(OBJECT* _Player, OBJECT* _Enemy)
{
	if (_Player->Info.IHP <= 0)
	{
		int n = 0;
		printf_s("Player : %s\n", _Player->Name);
		printf_s("����ϼ̽��ϴ�.\n");
		printf_s("������ �����մϴ�.\n");
		exit(NULL);
	}
	else if (_Enemy->Info.IHP <= 0)
	{
		printf_s("Player : %s\n", _Player->Name);

		if (_Player->Info.IClass == 1)
			printf_s("Class : ����\n");
		else if (_Player->Info.IClass == 2)
			printf_s("Class : �ü�\n");

		if (_Enemy->Info.IClass == 3)
		{
			printf_s("������ ó�� �߽��ϴ�.\n");
			Sleep(1000);
			system("cls");
			LastScene();
			Sleep(1000);
			system("cls");
			SetPosition(Width, Height, (char*)"�����մϴ�.", 15);
			Sleep(500);
			system("cls");
			SetPosition(Width, Height, (char*)"������ ����ϰ� ��ȭ�� ã�ƿԽ��ϴ�.", 15);
			Sleep(500);
			system("cls");
			SetPosition(Width, Height, (char*)"����� ������ ����˴ϴ�.", 15);
			Sleep(2000);
			exit(NULL);
		}

		printf_s("�������� �¸��ϼ̽��ϴ�.\n");
		printf_s("����ǰ\n");
		printf_s("����ġ : %d\n", _Enemy->Info.IExp);
		printf_s("��� : %d\n", _Enemy->Info.IGold);
		_Player->Info.IExp += _Enemy->Info.IExp;
		_Player->Info.IGold += _Enemy->Info.IGold;

		if (_Player->Info.IExp >= _Player->Info.ILevel * 2 && _Player->Info.ILevel <= 50)
		{
			printf_s("������ �ϼ̽��ϴ�.\n");
			++_Player->Info.ILevel;
			_Player->Info.FAttack = 40 + _Player->Info.ILevel * 5;
			_Player->Info.FDefense = 10 + _Player->Info.ILevel * 5;
			_Player->Info.IHP = 10000 + _Player->Info.ILevel * 15;
			_Player->Info.IMP = 50 + _Player->Info.ILevel * 15;
			_Player->Info.IExp = 0;
		}

		_Enemy->Info.ILevel = _Player->Info.ILevel;
		_Enemy->Info.FAttack = 5 + (_Enemy->Info.ILevel * 5);
		_Enemy->Info.FDefense = 15 + (_Enemy->Info.ILevel * 5);
		_Enemy->Info.IExp = 2;
		_Enemy->Info.IHP = 30 + (_Enemy->Info.ILevel * 15);
		_Enemy->Info.IMP = 5 + (_Enemy->Info.ILevel * 15);
		_Enemy->Info.IGold = 10;
		_Enemy->Info.IClass = 0;
		Sleep(1000);
		system("cls");
		MenuScene(_Player);
	}


	else if (_Enemy->Info.IHP > 0 && _Player->Info.IHP > 0)
	{

		int k = 0;

		if (_Player->Info.IClass == 1)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}

		printf_s("Name : %s\n", _Enemy->Name);
		printf_s("HP : %d\n", _Enemy->Info.IHP);
		printf_s("MP : %d\n", _Enemy->Info.IMP);
		printf_s("Att : %d\n", _Enemy->Info.FAttack);
		printf_s("Dtt : %d\n", _Enemy->Info.FDefense);
		printf_s("Exp : %d\n", _Enemy->Info.IExp);
		printf_s("Level : %d\n", _Enemy->Info.ILevel);
		printf_s("1. �ٽ� �⺻ ���� 2. �ٽ� ��ų ���� 3. ����\n���� : ");
		scanf_s("%d", &k);
		
		if (k == 1)
		{
			while (true)
			{
				Sleep(1000);
				system("cls");
				Battle(_Player, _Enemy);
				if (_Player->Info.IHP < 1)
				{
					BattleEnd(_Player, _Enemy);
					break;
				}
				else if (_Enemy->Info.IHP < 1)
				{
					BattleEnd(_Player, _Enemy);
					break;
				}

				if (_Player->Info.IClass == 1)
				{
					printf_s("Name : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("HP : %d\n", _Player->Info.IHP);
					printf_s("MP : %d\n", _Player->Info.IMP);
					printf_s("Att : %d\n", _Player->Info.FAttack);
					printf_s("Dtt : %d\n", _Player->Info.FDefense);
					printf_s("Exp : %d\n", _Player->Info.IExp);
					printf_s("Level : %d\n\n", _Player->Info.ILevel);
				}
				else if (_Player->Info.IClass == 2)
				{
					printf_s("Name : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("HP : %d\n", _Player->Info.IHP);
					printf_s("MP : %d\n", _Player->Info.IMP);
					printf_s("Att : %d\n", _Player->Info.FAttack);
					printf_s("Dtt : %d\n", _Player->Info.FDefense);
					printf_s("Exp : %d\n", _Player->Info.IExp);
					printf_s("Level : %d\n\n", _Player->Info.ILevel);
				}

				printf_s("Name : %s\n", _Enemy->Name);
				printf_s("HP : %d\n", _Enemy->Info.IHP);
				printf_s("MP : %d\n", _Enemy->Info.IMP);
				printf_s("Att : %d\n", _Enemy->Info.FAttack);
				printf_s("Dtt : %d\n", _Enemy->Info.FDefense);
				printf_s("Exp : %d\n", _Enemy->Info.IExp);
				printf_s("Level : %d\n", _Enemy->Info.ILevel);
				printf_s("1. �ٽ� �⺻ ���� 2. �ٽ� ��ų ���� 3. ����\n���� :");
				scanf_s("%d", &k);
				system("cls");

				if (k == 1)
				{
					BattleEnd(_Player, _Enemy);
					break;
				}

				else if (k == 2 && _Player->Info.IClass == 1)
				{
					WarriorSkill(_Player, _Enemy);
					break;
				}

				else if (k == 2 && _Player->Info.IClass == 2)
				{
					ArcherSkill(_Player, _Enemy);
					break;
				}

				else if (k == 3)
				{
					time_t tTime = time(NULL);
					int Rand = rand() % 3;

					if (Rand == 1 || Rand == 2)
					{
						if (_Player->Info.IClass == 1)
						{
							system("cls");
							printf_s("Player : %s\n", _Player->Name);
							printf_s("Class : ����\n");
							printf_s("����ġ�µ� �����߽��ϴ�.\n");
							printf_s("���θ޴��� ���ư��ϴ�.\n");
							Sleep(1000);
							system("cls");
							MenuScene(_Player);
						}
						else if (_Player->Info.IClass == 2)
						{
							system("cls");
							printf_s("Player : %s\n", _Player->Name);
							printf_s("Class : �ü�\n");
							printf_s("����ġ�µ� �����߽��ϴ�.\n");
							printf_s("���θ޴��� ���ư��ϴ�.\n");
							Sleep(1000);
							system("cls");
							MenuScene(_Player);
						}
					}
					else
					{
						if (_Player->Info.IClass == 1)
						{
							system("cls");
							printf_s("Player : %s\n", _Player->Name);
							printf_s("Class : ����\n");
							printf_s("����ġ�µ� �����߽��ϴ�.\n");
							printf_s("������ �����մϴ�.\n");
							Sleep(1000);
							system("cls");
							BasesBattle(_Player, _Enemy);
						}
						else if (_Player->Info.IClass == 2)
						{
							system("cls");
							printf_s("Player : %s\n", _Player->Name);
							printf_s("Class : �ü�\n");
							printf_s("����ġ�µ� �����߽��ϴ�.\n");
							printf_s("������ �����մϴ�.\n");
							Sleep(1000);
							system("cls");
							BasesBattle(_Player, _Enemy);
						}
					}
					break;
				}
			}
		}

		else if (k == 2)
		{
			while (true)
			{
				Sleep(1000);
				system("cls");

				if (_Player->Info.IClass == 1)
				{
					WarriorSkill(_Player, _Enemy);
					break;
				}

				else if (_Player->Info.IClass == 2)
				{
					ArcherSkill(_Player, _Enemy);
					break;
				}

				if (_Player->Info.IHP < 1)
				{
					BattleEnd(_Player, _Enemy);
					break;
				}
				else if (_Enemy->Info.IHP < 1)
				{
					BattleEnd(_Player, _Enemy);
					break;
				}

				if (_Player->Info.IClass == 1)
				{
					printf_s("Name : %s\n", _Player->Name);
					printf_s("Class : ����\n");
					printf_s("HP : %d\n", _Player->Info.IHP);
					printf_s("MP : %d\n", _Player->Info.IMP);
					printf_s("Att : %d\n", _Player->Info.FAttack);
					printf_s("Dtt : %d\n", _Player->Info.FDefense);
					printf_s("Exp : %d\n", _Player->Info.IExp);
					printf_s("Level : %d\n\n", _Player->Info.ILevel);
				}
				else if (_Player->Info.IClass == 2)
				{
					printf_s("Name : %s\n", _Player->Name);
					printf_s("Class : �ü�\n");
					printf_s("HP : %d\n", _Player->Info.IHP);
					printf_s("MP : %d\n", _Player->Info.IMP);
					printf_s("Att : %d\n", _Player->Info.FAttack);
					printf_s("Dtt : %d\n", _Player->Info.FDefense);
					printf_s("Exp : %d\n", _Player->Info.IExp);
					printf_s("Level : %d\n\n", _Player->Info.ILevel);
				}
			}
		}
		
		else if (k == 3)
		{
			time_t tTime = time(NULL);
			int Rand = rand() % 45 + 1;

			if ((Rand % 3) == 1 || (Rand % 3) == 2)
			{
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("���θ޴��� ���ư��ϴ�.\n");
				Sleep(1000);
				system("cls");
				MenuScene(_Player);
			}
			else
			{
				printf_s("����ġ�µ� �����߽��ϴ�.\n");
				printf_s("������ �����մϴ�.\n");
				Sleep(1000);
				system("cls");
				BasesBattle(_Player, _Enemy);
			}
		}	
	}
}

void BasesBattle(OBJECT* _Player, OBJECT* _Enemy)
{
	time_t tTime = time(NULL);
	int Rand = rand() % 3;

	if (Rand == 1 || Rand == 2)
	{
		InitializeEnemy(_Enemy, _Player);
		int n = 0;
		printf_s("���Ϳ� ������ �����մϴ�.\n");
		printf_s("���� ����\n");
		printf_s("Name : %s\n", _Enemy->Name);
		printf_s("HP : %d\n", _Enemy->Info.IHP);
		printf_s("MP : %d\n", _Enemy->Info.IMP);
		printf_s("Att : %d\n", _Enemy->Info.FAttack);
		printf_s("Dtt : %d\n", _Enemy->Info.FDefense);
		printf_s("Exp : %d\n", _Enemy->Info.IExp);
		printf_s("Level : %d\n\n", _Enemy->Info.ILevel);

		printf_s("�÷��̾� ����\n");
		if (_Player->Info.IClass == 1)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}
		printf_s("1. �⺻ ����\n2. ��ų\n3. ����\n���� : ");
		scanf_s("%d", &n);
		system("cls");

		if (n == 1)
		{
			Battle(_Player, _Enemy);
			BattleEnd(_Player, _Enemy);
		}

		else if (n == 2 && _Player->Info.IClass == 1)
		{
			WarriorSkill(_Player, _Enemy);
		}

		else if (n == 2 && _Player->Info.IClass == 2)
		{
			ArcherSkill(_Player, _Enemy);
		}
		else if (n == 3)
		{
			Medicine(_Player, _Enemy);
		}
	}
	else
	{
		EliteEnemy(_Enemy, _Player);
		int n = 0;
		printf_s("���Ϳ� ������ �����մϴ�.\n");
		printf_s("���� ����\n");
		printf_s("Name : %s\n", _Enemy->Name);
		printf_s("HP : %d\n", _Enemy->Info.IHP);
		printf_s("MP : %d\n", _Enemy->Info.IMP);
		printf_s("Att : %d\n", _Enemy->Info.FAttack);
		printf_s("Dtt : %d\n", _Enemy->Info.FDefense);
		printf_s("Exp : %d\n", _Enemy->Info.IExp);
		printf_s("Level : %d\n", _Enemy->Info.ILevel);

		printf_s("�÷��̾� ����\n");
		if (_Player->Info.IClass == 1)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : ����\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Name : %s\n", _Player->Name);
			printf_s("Class : �ü�\n");
			printf_s("HP : %d\n", _Player->Info.IHP);
			printf_s("MP : %d\n", _Player->Info.IMP);
			printf_s("Att : %d\n", _Player->Info.FAttack);
			printf_s("Dtt : %d\n", _Player->Info.FDefense);
			printf_s("Exp : %d\n", _Player->Info.IExp);
			printf_s("Level : %d\n\n", _Player->Info.ILevel);
		}
		printf_s("1. �⺻ ����\n2. ��ų\n3. ����\n���� : ");
		scanf_s("%d", &n);
		system("cls");
		
		if (n == 1)
		{
			Battle(_Player, _Enemy);
			BattleEnd(_Player, _Enemy);
		}

		else if (n == 2 && _Player->Info.IClass == 1)
		{
			WarriorSkill(_Player, _Enemy);
		}

		else if (n == 2 && _Player->Info.IClass == 2)
		{
			ArcherSkill(_Player, _Enemy);
		}
		else if (n == 3)
		{
			Medicine(_Player, _Enemy);
		}
	}
}

void Medicine(OBJECT* _Player, OBJECT* _Enemy)
{
	int n = 0;
	printf_s("Player : %s\n", _Player->Name);
	if (_Player->Info.IClass == 1)
	{
		printf_s("Class : ����\n");
	}
	else if (_Player->Info.IClass == 2)
	{
		printf_s("Class : �ü�\n");
	}
	printf_s("\n�ϱ� ü�� ���� : %d ȿ�� : HP + 10\n", _Player->Info.IHPMedicine1);
	printf_s("�߱� ü�� ���� : %d ȿ�� : HP + 20\n", _Player->Info.IHPMedicine2);
	printf_s("��� ü�� ���� : %d ȿ�� : HP + 30\n", _Player->Info.IHPMedicine3);
	printf_s("�ϱ� ���� ���� : %d ȿ�� : MP + 10\n", _Player->Info.IMPMedicine1);
	printf_s("�߱� ���� ���� : %d ȿ�� : MP + 20\n", _Player->Info.IMPMedicine2);
	printf_s("��� ���� ���� : %d ȿ�� : MP + 30\n\n", _Player->Info.IMPMedicine3);
	printf_s("1. �ϱ� ü�� ���� 2. �߱� ü�� ���� 3. ��� ü�� ����\n");
	printf_s("4. �ϱ� ���� ���� 5. �߱� ���� ���� 6. ��� ���� ����\n");
	printf_s("����Ͻ� ������ ���� : ");
	scanf_s("%d", &n);
	system("cls");

	if (n == 1)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IHPMedicine1 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IHPMedicine1 > 0)
		{
			printf_s("�ϱ� ü�� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IHP = _Player->Info.IHP + 10;
		}
	}

	else if (n == 2)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IHPMedicine2 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IHPMedicine2 > 0)
		{
			printf_s("�߱� ü�� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IHP = _Player->Info.IHP + 20;
		}
	}

	else if (n == 3)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IHPMedicine3 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IHPMedicine3 > 0)
		{
			printf_s("��� ü�� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IHP = _Player->Info.IHP + 30;
		}
	}

	else if (n == 4)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IMPMedicine1 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IMPMedicine1 > 0)
		{
			printf_s("�ϱ� ���� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IMP = _Player->Info.IMP + 10;
		}
	}

	else if (n == 5)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IMPMedicine2 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IMPMedicine2 > 0)
		{
			printf_s("�߱� ���� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IMP = _Player->Info.IMP + 20;
		}
	}

	else if (n == 6)
	{
		printf_s("Player : %s\n", _Player->Name);
		if (_Player->Info.IClass == 1)
		{
			printf_s("Class : ����\n");
		}
		else if (_Player->Info.IClass == 2)
		{
			printf_s("Class : �ü�\n");
		}

		if (_Player->Info.IMPMedicine3 < 1)
		{
			printf_s("������ �����ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
		}
		else if (_Player->Info.IMPMedicine3 > 0)
		{
			printf_s("��� ���� ������ ����߽��ϴ�.\n");
			printf_s("����â���� ���ư��ϴ�.\n");
			_Player->Info.IMP = _Player->Info.IMP + 30;
		}
	}

	else
	{
		printf_s("�߸������ϼ̽��ϴ�.\n");
		printf_s("����â���� ���ư��ϴ�.\n");
	}
	printf_s("Player HP : %d\n", _Player->Info.IHP);
	printf_s("Player MP : %d\n", _Player->Info.IMP);
	Sleep(1000);
	system("cls");

	if (_Enemy->Info.IClass == 1 || _Enemy->Info.IClass == 2)
	{
		BasesBattle(_Player, _Enemy);
	}
	else if (_Enemy->Info.IClass == 3)
	{
		BossBattle(_Player, _Enemy);
	}
}

void Battle(OBJECT* _Player, OBJECT* _Enemy)
{
	if (_Player->Info.FAttack > _Enemy->Info.FDefense)
	{
		_Enemy->Info.IHP = _Enemy->Info.IHP - (_Player->Info.FAttack - _Enemy->Info.FDefense);
	}
	else
	{
		_Enemy->Info.IHP -= 1;
	}
	if (_Enemy->Info.FAttack > _Player->Info.FDefense)
	{
		_Player->Info.IHP -= _Enemy->Info.FAttack - _Player->Info.FDefense;
	}
	else
	{
		_Player->Info.IHP -= 1;
	}
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

void FirstScene()
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

void GameStrat()
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
			system("cls");
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

void LastScene()
{
	int Width = (50) - (strlen("  / $$$$$$$$ / $$ /  $$ / $$$$$$$$    / $$$$$$$$ / $$  / $$  / $$$$$$$\n") / 2);
	int n = 0;

	for (int i = 0; i < 5; i++)
	{
		SetPosition(Width + n, Height + 1,(char*)"  / $$$$$$$$ / $$ /  $$ / $$$$$$$$    / $$$$$$$$ / $$  / $$  / $$$$$$$\n", 6);
		SetPosition(Width + n, Height + 2, (char*)"| __  $$__/ | $$ |  $$ | $$_____/    | $$_____/ | $$$ | $$ | $$__  $$\n", 6);
		SetPosition(Width + n, Height + 3, (char*)"    | $$    | $$ |  $$ | $$          | $$       | $$$$| $$ | $$  \ $$\n", 6);
		SetPosition(Width + n, Height + 4, (char*)"    | $$    | $$$$$$$$ | $$$$$       | $$$$$    | $$ $$ $$ | $$  | $$\n", 6);
		SetPosition(Width + n, Height + 5, (char*)"    | $$    | $$__  $$ | $$__/       | $$__/    | $$  $$$$ | $$  | $$\n", 6);
		SetPosition(Width + n, Height + 6, (char*)"    | $$    | $$ |  $$ | $$          | $$       | $$\  $$$ | $$  | $$\n", 6);
		SetPosition(Width + n, Height + 7, (char*)"    | $$    | $$ |  $$ | $$$$$$$$    | $$$$$$$$ | $$ \  $$ | $$$$$$$/\n", 6);
		SetPosition(Width + n, Height + 8, (char*)"    |__/    |__/  |__/ |________/    |________/ |__ / \__/ |_______ /\n", 6);

		n++;
		Sleep(500);
		system("cls");
	}	
}