#pragma once
int map[20][10]{ 0 };
int map_AI[20][10]{ 0 };
void copymap()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			map_AI[i][j] = map[i][j];
}
int hight(int ai)
{
	int p = 0;
	for (int i = 0; i < 20; i++)
		if (map_AI[i][ai] == 1)return 20 - i;
	return p;
}
class BlockSet
{
public:
	int id;
	int	box[4][4];
	int x, y;
	int minCol, maxCol, minD;
	BlockSet() {}
	BlockSet(int id,int x, int y, int b[4][4], int minCol, int maxCol, int mind) :x(x), y(y), minCol(minCol), maxCol(maxCol), minD(mind),id(id)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				box[i][j] = b[i][j];
	}
	BlockSet& operator =(const BlockSet &b)
	{
		this->x = b.x;
		this->y = b.y;
		minCol = b.minCol;
		minD = b.minD;
		maxCol = b.maxCol;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				box[i][j] = b.box[i][j];
		return *this;
	}
	bool Checkbox_L()//方块越界检测
	{
		return x + minCol - 1 <0;
	}
	bool Checkbox_R()//方块越界检测
	{
		return x + maxCol + 2 > 10;
	}
	//方块最低检测
	bool Checkbox_Down()
	{
		return y + minD > 18;
	}
	//方块是否符合种子条件
	bool CheckStop()
	{
		if (Checkbox_Down())return true;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (map[y + i + 1][x + j] == 1 && box[i][j] == 1) return true;
		return false;
	}
	bool CheckStopL()
	{
		if (Checkbox_L())return true;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (map[y + i][x + j - 1] == 1 && box[i][j] == 1) return true;
		return false;
	}

	bool CheckStopR()
	{
		if (Checkbox_R())return true;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (map[y + i][x + j + 1] == 1 && box[i][j] == 1) return true;
		return false;
	}

	//方块下落方法
	void Down()
	{
		y++;
	}
	void Right() { x++; }
	void Left() { x--; }
};