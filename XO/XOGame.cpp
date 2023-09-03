#include <bits/stdc++.h>

using namespace std;

char table[100][100];
int n , a;

bool hasWon(int x , int y){
    //line
    int counter = 0;
    int lol = 0;
    bool result = false;
    for (int i = x; i < n && i - x < a; i++)
    {
        if (table[x][y] == table[i][y]) counter ++;
        else if (table[i][y] == '-') lol++;
        else {counter = 0; break;}
    }
    if (x == n - (a - 1) ) if ( table[x - 1][y] == '-') lol ++;
    if (counter >= a) throw(table[x][y]);
    if (counter == a - 1 && lol == 1) result = true;
    //column
    counter = 0;
    lol = 0;
    for (int i = y; i < n && i - y < a; i++)
    {
        if (table[x][y] == table[x][i]) counter ++;
        else if (table[x][i] == '-') lol++;
        else { counter = 0; break;}
    }
    if (y == n - (a - 1) ) if (table[x][y - 1] == '-') lol ++;
    if (counter >= a) throw(table[x][y]);
    if (counter == a - 1 && lol == 1) result = true;
    //cross x+
    counter = 0;
    lol = 0;
    for (int i = 0; (i + x < n && i + y < n && i < a); i++)
    {
        if (table[x][y] == table[i + x][i + y]) counter ++;
        else if (table[i + x][i + y] == '-') lol ++;
        else {counter = 0; break;}
    }
    if (x == n -(a - 1) || y == n - (a - 1) ) if (table[x - 1][y - 1] == '-') lol++;
    if (counter == a) throw(table[x][y]);
    if (counter == a - 1 && lol == 1) result = true;
    //cross x-
    counter = 0;
    lol = 0;
    for (int i = 0; (i + x < n && y - i >= 0 && i< a); i++)
    {
        if (table[x][y] == table[x + i][y - i]) counter ++;
        else if (table[x + i][y - i] == '-') lol ++;
        else {counter = 0; break;}
    }
    if (x == n - (a - 1) || y == a - 2) if (table[x - 1][y + 1] == '-') lol ++;
    if (counter == a) throw(table[x][y]);
    if (counter == a - 1 && lol == 1) result = true;
    
    return result;
}

void shit ()
{

    if (a == 0) throw "lol";
    if (a == 1)
    {
        for (int i = 0 ; i <n ; i++)
        {
            for (int j = 0 ; j < n ; j ++)
            {
                if (table[i][j] == 'X')
                {
                    throw ('X');
                }
                else if (table[i][j] == 'O')
                {
                    throw ('O');
                }
            }
        }
        // if (x || o)
        //     throw 2;
        // else if (empty)
        //     cout << "Both";
        return ;
    }

    for (int i = 0 ; i <n; i++)
    {
        for (int j = 0 ; j < n ; j ++)
        {
            if (table[i][j] != '-') hasWon(i , j);
        }
    }
    // if (x && o)
    //     cout << "Both";
    // else if (x)
    //     cout  << "X";
    // else if (o)
    //     cout << "O";
    // else
    //     cout  << "None";

}

void get_info()
{
    char waste;
    cin >> n >> a;
    if (n >= 100)
        throw "TOO BIG";
    if (a > n)
        throw "IMPOSSIBLE!";
    for (int i = 0 ; i <n ; i++)
    {
        for (int j = 0 ; j < n ; j ++)
        {
            table[i][j] = '-';
        } 
    }
}

void show()
{
    system("cls");
    string spaces = " ";
    if (n / 10 != 0)
        spaces += spaces;
    printf(" %s" , spaces.c_str());
    for (int i = 0 ; i< n ; i++) {printf("%d" , i+1); if ( (i+1) / 10 != 0) printf (" "); else printf("  ");}
    printf("\n");
    for (int i = 0; i < n; i ++)
    {
        printf("%d" , i+1 );
        if ( (i+1) / 10 != 0) printf (" ");
        else printf("  ");
        for (int j = 0 ; j < n ; j++)
        {
            printf("%c%s" , table[i][j] , spaces.c_str());
        }
        printf("\n");
    }
}

int main()
{
    get_info();
    int x , y;
    try
    {
        int counter = 0;
        while (true)
        {
            show();
            try
            {
                if (counter%2 == 0)
                {
                    printf("player X : ");
                    cin >> x >> y;
                    if (table[x - 1][y - 1] != '-')
                        throw 2;
                    table[x - 1][y - 1] = 'X';
                }
                else
                {
                    printf("player O : ");
                    cin >> x >> y;
                    if (table[x - 1][y - 1] != '-')
                        throw 2;
                    table[x - 1][y - 1] = 'O';
                }
            }
            catch(...)
            {
                continue;
            }
            shit();
            counter ++;
        }
    
    }
    catch (char c)
    {
        show();
        printf ("%c WON!" , c);
    }

}