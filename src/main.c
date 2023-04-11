#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int game[4][4]; // 游戏核心
int copy[4][4]; // 拷贝数组

int length = 4;

// 函数声明
void random();         // 随机坐标
void draw();           // 绘画函数
void left();           // 按下左
void rotate(size_t n); // 旋转几次90度
void win();

int main(int argc, char const *argv[])
{
  random();
  random();
  draw();

  while (1)
  {
    if (_kbhit())
    {                      // 如果有按键按下，则_kbhit()函数返回真
      int key1 = _getch(); // 使用_getch()函数获取按下的键值
      int key2 = _getch(); // 对于一些键会有第二个键值
      if (key1 == 224)
      {
        if (key2 == 75) // 左
        {
          left();
        }
        if (key2 == 72) // 上
        {
          rotate(1);
          left();
          rotate(3);
        }
        if (key2 == 77) // 右
        {
          rotate(2);
          left();
          rotate(2);
        }
        if (key2 == 80) // 下
        {
          rotate(3);
          left();
          rotate(1);
        }
        draw();
        win();
      }
      if (key1 == 27)
        break;
    }
  }
  return 0;
}

void random()
{
  srand((unsigned)time(NULL)); // 用时间播种
  int x = (rand() % 4);
  int y = (rand() % 4);
  while (1 == 1)
  {
    if (game[x][y] == 0)
    {
      game[x][y] = ((rand() % 2) + 1) * 2;
      break;
    }
    else
    {
      x = (rand() % 4);
      y = (rand() % 4);
    }
  }
}

void draw()
{
  // system("clear");
  system("cls");
  printf("\n \n");
  for (size_t x = 0; x < 4; x++)
  {
    printf("|");
    for (size_t y = 0; y < 4; y++)
    {
      printf("|\t%d\t|", game[x][y]);
    }
    printf("|\n");
  }
}

void left()
{
  int run = 0;
  for (size_t x = 0; x < length; x++)
  {
    for (size_t i = 0; i < length; i++)
    {
      if (game[x][i] == 0)
      {
        for (size_t j = i; j < length; j++)
        {
          if (game[x][j] != 0)
          {
            game[x][i] = game[x][j];
            game[x][j] = 0;
            run = 1;
            break;
          }
        }
      }
    }
    for (size_t y = 0; y < length - 1; y++)
    {
      if (game[x][y] != 0 && game[x][y] == game[x][y + 1])
      {
        game[x][y] = 2 * game[x][y];
        game[x][y + 1] = 0;
        run = 1;
      }
    }
    for (size_t i = 0; i < length; i++)
    {
      if (game[x][i] == 0)
      {
        for (size_t j = i; j < length; j++)
        {
          if (game[x][j] != 0)
          {
            game[x][i] = game[x][j];
            game[x][j] = 0;
            break;
          }
        }
      }
    }
  }
  if (run == 1)
  {
    random();
  }
}

void rotate(size_t n)
{
  while (n != 0)
  {
    for (size_t x = 0; x < length; x++)
    {
      for (size_t y = 0; y < length; y++)
      {
        copy[x][y] = game[x][y];
      }
    }
    for (size_t x = 0; x < length; x++)
    {
      for (size_t y = 0; y < length; y++)
      {
        game[x][y] = copy[y][length - 1 - x];
      }
    }
    n--;
  }
}

void win()
{
  for (size_t x = 0; x < length; x++)
  {
    for (size_t y = 0; y < length; y++)
    {
      if (game[x][y] == 2048)
      {
        printf("you win!!!");
        exit(0);
      }
    }
  }
}