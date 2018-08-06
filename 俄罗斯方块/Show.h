#pragma once
#include"Box.h"
#include<deque>
#include<iostream>
#include<random>
#include<conio.h>
#include<Windows.h>
#include<math.h>
#include<fstream>
#define UP    0x48
#define DOWN  0x50
#define LEFT  0x4B
#define RIGHT 0x4D
#define INVAILD_KEY_CODE -1

//基础方块
static std::default_random_engine e;
static std::uniform_int_distribution<int> u(0, 6);

class WindowsPlayer
{
private:
	//权值
	int d1=10,d2=10,d3=10,d4=10;
	int num, trans;
	//当前方块
	BlockSet blo;

	int b[7][4][4][4]
	{
		//■■■■
		{
			{
				{ 0,1,0,0 },
				{ 0,1,0,0 },
				{ 0,1,0,0 },
				{ 0,1,0,0 }
			},
			{
				{ 0,0,0,0 } ,
				{ 0,0,0,0 },
				{ 1,1,1,1 } ,
				{ 0,0,0,0 }
			},
			{
				{ 0,0,1,0 },
				{ 0,0,1,0 },
				{ 0,0,1,0 },
				{ 0,0,1,0 }
			},
			{
				{ 0,0,0,0 } ,
				{ 1,1,1,1 } ,
				{ 0,0,0,0 } ,
				{ 0,0,0,0 }
			}
		},

		//■■
		//■■
		{
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
		},

		//■■
		//  ■■
		{
			{
				{ 0,0,0,0 },
				{ 1,1,0,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,1,0,0 },
				{ 1,1,0,0 },
				{ 1,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,0,0 },
				{ 1,1,0,0 },
				{ 0,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,1,0,0 },
				{ 1,1,0,0 },
				{ 1,0,0,0 },
				{ 0,0,0,0 }
			},
		},

		//  ■■
		//■■
		{
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 1,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,0,0,0 },
				{ 1,1,0,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,0,0 },
				{ 0,1,1,0 },
				{ 1,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,0,0,0 },
				{ 1,1,0,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 }
			},
		},

		//  ■
		//■■■
		{
			{
				{ 0,0,0,0 },
				{ 0,1,0,0 },
				{ 1,1,1,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,0,0,0 },
				{ 1,1,0,0 },
				{ 1,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,1,1,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,1,0,0 },
				{ 1,1,0,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 }
			},
		},

		//■
		//■	
		//■■
		{
			{
				{ 1,0,0,0 },
				{ 1,0,0,0 },
				{ 1,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,1,1,0 },
				{ 1,0,0,0 },
				{ 0,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,1,0,0 },
				{ 0,1,0,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,0,1,0 },
				{ 1,1,1,0 },
				{ 0,0,0,0 },
				{ 0,0,0,0 }
			}
		},
		//■■
		//■	
		//■
		{
			{
				{ 1,1,0,0 },
				{ 1,0,0,0 },
				{ 1,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,1,1,0 },
				{ 0,0,1,0 },
				{ 0,0,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 0,1,0,0 },
				{ 0,1,0,0 },
				{ 1,1,0,0 },
				{ 0,0,0,0 }
			},
			{
				{ 1,0,0,0 },
				{ 1,1,1,0 },
				{ 0,0,0,0 },
				{ 0,0,0,0 }
			}
		}

	};
	//得分
	int price = 0;
	//记录方块顺序
	std::deque<int> sequenceBlock;
	BlockSet block[6][4];
private:
	void initBlock()
	{
		block[0][0] = BlockSet(0,0, 0, b[0][0], 1, 1, 3);
		block[0][1] = BlockSet(0, 0, 0, b[0][1], 0, 3, 2);
		block[0][2] = BlockSet(0, 0, 0, b[0][2], 2, 2, 3);
		block[0][3] = BlockSet(0, 0, 0, b[0][3], 0, 3, 1);

		block[1][0] = BlockSet(1,0, 0, b[1][0], 1, 2, 2);
		block[1][1] = BlockSet(1,0, 0, b[1][1], 1, 2, 2);
		block[1][2] = BlockSet(1,0, 0, b[1][2], 1, 2, 2);
		block[1][3] = BlockSet(1,0, 0, b[1][3], 1, 2, 2);

		block[2][0] = BlockSet(2,0, 0, b[2][0], 0, 2, 2);
		block[2][1] = BlockSet(2,0, 0, b[2][1], 0, 1, 2);
		block[2][2] = BlockSet(2,0, 0, b[2][2], 0, 2, 2);
		block[2][3] = BlockSet(2,0, 0, b[2][3], 0, 1, 2);

		block[3][0] = BlockSet(3,0, 0, b[3][0], 0, 2, 2);
		block[3][1] = BlockSet(3,0, 0, b[3][1], 0, 1, 2);
		block[3][2] = BlockSet(3,0, 0, b[3][2], 0, 2, 2);
		block[3][3] = BlockSet(3,0, 0, b[3][3], 0, 1, 2);

		block[4][0] = BlockSet(4,0, 0, b[4][0], 0, 2, 2);
		block[4][1] = BlockSet(4,0, 0, b[4][1], 0, 1, 2);
		block[4][2] = BlockSet(4,0, 0, b[4][2], 0, 2, 1);
		block[4][3] = BlockSet(4,0, 0, b[4][3], 0, 1, 2);

		block[5][0] = BlockSet(5,0, 0, b[5][0], 0, 1, 2);
		block[5][1] = BlockSet(5,0, 0, b[5][1], 0, 2, 1);
		block[5][2] = BlockSet(5,0, 0, b[5][2], 0, 1, 2);
		block[5][3] = BlockSet(5,0, 0, b[5][3], 0, 2, 1);

		block[6][0] = BlockSet(6,0, 0, b[6][0], 0, 1, 2);
		block[6][1] = BlockSet(6,0, 0, b[6][1], 0, 2, 1);
		block[6][2] = BlockSet(6,0, 0, b[6][2], 0, 1, 2);
		block[6][3] = BlockSet(6,0, 0, b[6][3], 0, 2, 1);

	}

	//是否达成清楚条件
	bool isClear(int n)
	{
		for (int j = 0; j < 10; j++)
			if (map[n][j] == 0)
				return 0;
		return 1;
	}
	bool isClear_AI(int n)
	{
		for (int j = 0; j < 10; j++)
			if (map_AI[n][j] == 0)
				return 0;
		return 1;
	}
	//将所有满足清楚条件的行清除
	void Clear()
	{
		for (int i = 19; i > 0; i--)
		{
			if (isClear(i))
			{
				for (int j = 0; j < 10; j++)
				{
					map[i][j] = 0;
					for (int k = i; k > 1; k--)
					{
						if (map[k][j] == 0 && map[k - 1][j] == 1)
						{
							map[k][j] = 1;
							map[k - 1][j] = 0;
						}
					}
				}
				i++;
				price += 100;
			}
		}
	}
	int Clear_AI()
	{
		int price_AI = 0;
		for (int i = 19; i > 0; i--)
		{
			if (isClear_AI(i))
			{
				for (int j = 0; j < 10; j++)
				{
					map_AI[i][j] = 0;
					for (int k = i; k > 1; k--)
					{
						if (map_AI[k][j] == 0 && map_AI[k - 1][j] == 1)
						{
							map_AI[k][j] = 1;
							map_AI[k - 1][j] = 0;
						}
					}
				}
				i++;
				price_AI += 100;
			}
		}
		return price_AI;
	}
	//逻辑代码
	void BOOLs()
	{
		while (_kbhit())
		{
			int c = _getch();
			if (c == RIGHT)
			{
				if (!blo.CheckStopR())
					blo.Right();
			}
			else if (c == LEFT)
			{
				if (!blo.CheckStopL())
					blo.Left();
			}
			//翻转
			else if (c == UP)
			{
				trans = (trans + 1) % 4;
				int x1 = blo.x;
				int y1 = blo.y;
				BlockSet linshi = block[num][trans];
				linshi.x = x1;
				linshi.y = y1;
				if (!linshi.CheckStop())
				{
					blo = block[num][trans];
					blo.x = x1;
					blo.y = y1;
					if (blo.x + blo.minCol < 0)blo.x = 0 - blo.minCol;
					if (blo.x + blo.maxCol >= 10)blo.x = 9 - blo.maxCol;
				}
				return;
			}
		}
	}
	void BOOls_AI()
	{//
		//定义操作单元
		std::deque<int> operating;
		int score[4][10];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				score[i][j] = -100000000;
				BlockSet m = block[blo.id][i];
				m.x = j - m.minCol;
				m.y = 0;
				if (j+m.maxCol - m.minCol >9 )
					continue;

				copymap();
				score[i][j] = 50;
				//模拟方块下落
				while (!m.CheckStop())
				{
					m.Down();
				}
				for (int k = 0; k < 4; k++)
				{
					for (int l = 0; l < 4; l++)
					{
						if (m.box[k][l] == 1)
						{
							map_AI[m.y + k][m.x + l] = 1;
						}
					}
				}
				score[i][j] += Clear_AI()/100*d1;
				for (int k = m.minCol + m.x; k <= m.maxCol + m.x; k++)
				{
					for (int l = m.y + m.minD - 1; l <= 19; l++)
					{
						if (map_AI[l][k] == 0)
						{
							score[i][j] -= d2;
						}
					}
				}
				int n[10],nn=0,da=0;
				for (int m = 0; m < 10; m++)
				{
					n[m] = hight(m);
					nn += n[m];
				}
				nn /= 10;
				for (int m = 0; m < 10; m++)
				{
					da += abs(n[m] - nn);
				}
				score[i][j] -=da * d3;
			}
		}
		int maxi = 0, maxt = 0, s = score[0][0];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (s < score[i][j]) 
				{ s = score[i][j]; maxi = j; maxt = i; }
			}
		}
		blo = block[blo.id][maxt];
		blo.x = maxi-blo.minCol;
		blo.y = 0;
	}

	void MoveDown()
	{
		if (blo.CheckStop())
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (blo.box[i][j] == 1)
					{
						map[blo.y + i][blo.x + j] = 1;
					}
				}
			}
			num = u(e);
			//如果找到
			while (std::find(sequenceBlock.begin(), sequenceBlock.end(), num) != sequenceBlock.end())
			{
				num = u(e);
			}
			sequenceBlock.push_back(num);
			while (sequenceBlock.size() > 3)
			{
				sequenceBlock.pop_front();
			}
			trans = 0;
			blo = block[num][trans];
			blo.id = num;
			blo.x = 5;
			blo.y = 0;
			BOOls_AI();
		}
		blo.Down();
		Clear();
	}
	bool isFail()
	{
		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 10; i++)
				if (map[j][i] == 1)
					return false;
		return true;
	}
	void drawBox(HDC& hdc2, int i, int j, int x = 0, int y = 0)
	{
		//上
		MoveToEx(hdc2, 43 + 20 * (x + j), 43 + 20 * (y + i), 0);
		LineTo(hdc2, 57 + 20 * (x + j), 43 + 20 * (y + i));
		//左
		MoveToEx(hdc2, 43 + 20 * (x + j), 43 + 20 * (y + i), 0);
		LineTo(hdc2, 43 + 20 * (x + j), 57 + 20 * (y + i));
		//下
		MoveToEx(hdc2, 43 + 20 * (x + j), 57 + 20 * (y + i), 0);
		LineTo(hdc2, 57 + 20 * (x + j), 57 + 20 * (y + i));
		//右
		MoveToEx(hdc2, 57 + 20 * (x + j), 43 + 20 * (y + i), 0);
		LineTo(hdc2, 57 + 20 * (x + j), 57 + 20 * (y + i));
	}

public:
	WindowsPlayer()
	{
		initBlock();
	}
	void start()
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		for (int d1 = 1; d1 < 20; d1++)
		{
			for (int d2 = 1; d2 < 20; d2++)
			{
				for (int d3 = 1; d3 < 20; d3++)
				{
					memset(map, 0, sizeof(map));
					num = u(e);
					sequenceBlock.push_back(num);
					trans = 0;
					blo = block[num][trans];
					blo.x = 5; blo.y = 0;

					while (isFail())
					{
						RECT rect;
						GetClientRect(hwnd, &rect);
						int w = rect.right, h = rect.bottom;
						HDC hdc2 = CreateCompatibleDC(hdc);
						HBITMAP bitmap = CreateCompatibleBitmap(hdc, w, h);

						SelectObject(hdc2, bitmap);
						SelectObject(hdc2, GetStockObject(WHITE_PEN));
						//逻辑操作
						MoveDown();
						MoveToEx(hdc2, 40, 40, 0);	LineTo(hdc2, 40, 440);
						MoveToEx(hdc2, 240, 40, 0); LineTo(hdc2, 240, 440);
						MoveToEx(hdc2, 40, 440, 0);	LineTo(hdc2, 240, 440);

						for (int i = 0; i < 4; i++)
							for (int j = 0; j < 4; j++)
								if (blo.box[i][j] == 1)
								{
									drawBox(hdc2, i, j, blo.x, blo.y);
								}

						for (int i = 0; i < 20; i++)
							for (int j = 0; j < 10; j++)
							{
								if (map[i][j] == 1)
								{
									drawBox(hdc2, i, j);
								}
							}
						BitBlt(hdc, 0, 0, w, h, hdc2, 0, 0, SRCCOPY);
						DeleteObject(bitmap);
						DeleteDC(hdc2);
						Sleep(5);
					}
					system("cls");
					std::cout << "GAME OVER" << std::endl;
					std::cout << "PRICE:" << price << std::endl;
					std::cout << "\n是否重新开始\n  y/n" << std::endl;

					Sleep(1);
					std::fstream outfile;
					outfile.open("E:\\权值.txt", std::ios::app);
					if (outfile) 
					{
						outfile << "d1=" << d1 << ",d2=" << d2 << ",d3=" << d3 << ",    price="<<price<<"\r\n" ;
						outfile.close();
					}	
					price = 0;
					//char a;
					//std::cin >> a;
					//if (a != 'y')
					//	break;
				}
			}
		}
	}
};
