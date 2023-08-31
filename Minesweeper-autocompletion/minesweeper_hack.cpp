#include <bits/stdc++.h>
using namespace std;
enum State
{
    CITIZEN,
    BELONG_TO_ONE,
    BELONG_TO_MANY,
    IN_DANGER_DEF,
    IN_DANGER_MAY,
    ALONE,
    UNDEFINED
};

int ThreatLevel ( char playGround[][100] , int x, int y );
bool IsDigit(char c);


int n , m;
int RemainingBomb (char playGround[][100] , int i , int j )
{
    return (int)playGround[i][j]  - (int)'0' - ThreatLevel(playGround , i , j);
}
State GetState( char playGround[][100], int x, int y, int &bombCount )
{
    bool firstSnitchFlag = false; bool secondSnitchFlag = false; int questionMark = 0; bool citizen = false; int neighborBomb = 1; int realCase = 0;
    for ( int i = x - 1; i <= x + 1; i++ )
    {
        if ( i < 0 || i >= n ) continue;
        for ( int j = y - 1; j <= y + 1; j++ )
        {
            if ( j < 0 || j >= m || ( i == x && j == y ) ) continue;
            realCase++;
            if ( playGround[i][j] == '.' ) citizen = true;
            else if ( playGround[i][j] == '?' ) questionMark++;
            else if ( playGround[i][j] == '*' ) bombCount ++;
            else if ( IsDigit( playGround[i][j] ) ) { if ( !firstSnitchFlag ) { firstSnitchFlag = true; neighborBomb = RemainingBomb ( playGround, i, j ); } else if ( RemainingBomb ( playGround, i, j ) != 0 ) { secondSnitchFlag = true; if (neighborBomb > 0) neighborBomb = RemainingBomb ( playGround, i, j ); }  }
        }
    }
    //if ( RemainingBomb ( playGround, x, y ) == questionMark ) return State::ALONE;
    if ( bombCount == 0 && citizen && questionMark==0 ) return State::CITIZEN;
    if ( firstSnitchFlag ) { bombCount = neighborBomb; return secondSnitchFlag ? State::BELONG_TO_MANY : State::BELONG_TO_ONE; }
    if (bombCount > 0) return (citizen && neighborBomb > 0) ? questionMark > 0 ? State::UNDEFINED : State::IN_DANGER_DEF : State::ALONE;
    return questionMark > 0 ? State::ALONE : State::ALONE;
}
bool IsDigit(char c) 
{
    if (c >= '0' && c <= '9') return true;
    return false;
}
int ThreatLevel ( char playGround[][100] , int x, int y )
{
    int level = 0;
    for ( int i = x - 1; i <= x + 1; i++ )
    {
        if ( i < 0 || i >= n ) continue;
        for ( int j = y - 1; j <= y + 1; j++ )
        {
            if ( j < 0 || j >= m || ( i == x && j == y ) ) continue;
            if ( playGround[i][j] == '*' ) level++;
        }
    }
    return level;
}
int EmptyField( char playGround[][100], int x, int y )
{
    int level = 0;
    for ( int i = x - 1; i <= x + 1; i++ )
    {
        if ( i < 0 || i >= n ) continue;
        for ( int j = y - 1; j <= y + 1; j++ )
        {
            if ( j < 0 || j >= m || ( i == x && j == y ) ) continue;
            if ( playGround[i][j] == '?' ) level++;
        }
    }
    return level;
}
void MakeEmptiesBomb( char playGround[][100], int x, int y )
{
    for ( int i = x - 1; i <= x + 1; i++ )
    {
        if ( i < 0 || i >= n ) continue;
        for ( int j = y - 1; j <= y + 1; j++ )
        {
            if ( j < 0 || j >= m || ( i == x && j == y ) ) continue;
            if ( playGround[i][j] == '?' ) playGround [i][j] = '*';
        }
    }
}
void Pain1 ( char playGround[][100])
{
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < m; j++ )
        {
            if ( playGround[i][j] != '?' && !IsDigit(playGround[i][j]) ) continue;
            if ( IsDigit ( playGround[i][j] ) )
            {
                if (RemainingBomb(playGround, i, j) == EmptyField( playGround, i, j ) )
                    MakeEmptiesBomb(playGround, i, j);
                continue;
            }
            int bombCount = 0;
            State state = GetState ( playGround, i, j, bombCount );
            if ( state == State::IN_DANGER_DEF ) playGround[i][j] = ( bombCount + '0' );
            else if ( state == State::ALONE ) {playGround[i][j] = '*';}
            else if ( state == State::CITIZEN ) playGround[i][j] = '.';
            else if ( state == State::BELONG_TO_ONE && bombCount > 0 ) {playGround[i][j] = '*';} 
         }
    }
}
void Pain2 ( char playGround[][100] )
{
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < m; j++ )
        {
            if ( playGround[i][j] == '?' )
                playGround[i][j] =  ThreatLevel ( playGround, i, j ) == 0 ? '.' : ( ThreatLevel ( playGround, i, j ) + '0' );
        }
    }
}
void Pain3 ( char playGround[][100] )
{
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < m; j++ )
        {
            if ( playGround[i][j] != '?' && !IsDigit(playGround[i][j]) ) continue;
            if ( IsDigit ( playGround[i][j] ) )
            {
                if (RemainingBomb(playGround, i, j) == EmptyField( playGround, i, j ) )
                    MakeEmptiesBomb(playGround, i, j);
                continue;
            }
            int bombCount = 0;
            State state = GetState ( playGround, i, j, bombCount );
            if ( state == State::BELONG_TO_MANY && bombCount > 0 )
                playGround[i][j] = '*'; 
         }
    }
}
void Print ( char playGround[][100] )
{
    int bombCount = 0;
    for(int i = 0; i < n;i++ )
        for(int j = 0;j < m;j++ )
            if ( playGround[i][j] == '*')
                bombCount++;
    cout << bombCount << endl;
    for (int I = 0; I < n;I++ )
    {
        for(int J = 0; J < m ;J++ )
        {
            cout<<playGround[I][J];
        }
        cout << endl;
    }
}
int main ()
{
    cin >> n >> m;
    char c [100][100];
    char temp;
    scanf("%c" ,&temp );
    for (int i = 0; i < n; i++)
    {
        
        for (int j = 0; j < m; j++)
        {
            scanf("%c" , &c[i][j]);
        }
        scanf("%c" ,&temp );
    }
    Pain1 ( c );
    Pain3 ( c );
    Pain2 ( c );
    Print ( c );
}