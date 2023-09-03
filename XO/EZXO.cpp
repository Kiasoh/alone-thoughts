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
    if (counter >= a) throw("Nice Try!");
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
    if (counter >= a) throw("Nice Try!");
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
    if (counter == a) throw("Nice Try!");
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
    if (counter == a) throw("Nice Try!");
    if (counter == a - 1 && lol == 1) result = true;
    
    return result;
}

int main()
{
    bool x = false , o = false;
    
    char waste;
    cin >> n >> a;
    scanf("%c" , &waste);
    for (int i = 0 ; i <n ; i++)
    {
        for (int j = 0 ; j < n ; j ++)
        {
            scanf ("%c" , &table[i][j]);
        }
        scanf("%c" , &waste);   
    }

    if (a == 0) throw "lol";
    if (a == 1)
    {
        bool empty = false;
        for (int i = 0 ; i <n && (!x || !o || !empty) ; i++)
        {
            for (int j = 0 ; j < n && (!x || !o || !empty) ; j ++)
            {
                if (table[i][j] == 'X' && !x)
                {
                    x = true;
                }
                else if (table[i][j] == 'O' && !o)
                {
                    o = true;
                }
                else if (table[i][j] == '-' && !empty)
                    empty = true;
            }
        }
        if (x || o)
            cout << "Finished";
        else if (empty)
            cout << "Both";
        return 0;
    }
    try{
        for (int i = 0 ; i <n && (!x || !o) ; i++)
        {
            for (int j = 0 ; j < n && (!x || !o) ; j ++)
            {
                if (table[i][j] == 'X')
                {
                    if (x)
                        hasWon(i , j);
                    else x = hasWon(i , j);
                }
                else if (table[i][j] == 'O')
                {
                    if (o)
                        hasWon(i , j);
                    else o = hasWon(i , j);
                }
            }
        }
        if (x && o)
            cout << "Both";
        else if (x)
            cout  << "X";
        else if (o)
            cout << "O";
        else
            cout  << "None";
    }
    catch (...)
    {
        cout  << "Finished";
    }  
}