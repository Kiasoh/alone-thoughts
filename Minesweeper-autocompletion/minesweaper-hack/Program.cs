using System;
public enum State
{
    CITIZEN,
    BELONG_TO_ONE,
    BELONG_TO_MANY,
    IN_DANGER_DEF,
    IN_DANGER_MAY,
    ALONE,
    UNDEFINED
}

public class Program
{
    static int n, m;
    public static int RemainingBomb (char[,] playGround , int i , int j )
    {
        return Convert.ToInt32 ( playGround[i, j] ) - Convert.ToInt32 ( '0' ) - ThreatLevel(playGround , i , j);
    }

    public static State GetState( char[,] playGround, int x, int y, ref int bombCount )
    {
        bool firstSnitchFlag = false; bool secondSnitchFlag = false; int questionMark = 0; bool citizen = false; int neighborBomb = 1; int realCase = 0;
        for ( int i = x - 1; i <= x + 1; i++ )
        {
            if ( i < 0 || i >= playGround.GetLength(0) ) continue;
            for ( int j = y - 1; j <= y + 1; j++ )
            {
                if ( j < 0 || j >= playGround.GetLength ( 1 ) || ( i == x && j == y ) ) continue;
                realCase++;
                if ( playGround[i, j] == '.' ) citizen = true;
                else if ( playGround[i, j] == '?' ) questionMark++;
                else if ( playGround[i, j] == '*' ) bombCount++;
                else if ( Char.IsDigit( playGround[i, j ] ) ) { if ( !firstSnitchFlag ) { firstSnitchFlag = true; neighborBomb = RemainingBomb ( playGround, i, j ); } else if ( RemainingBomb ( playGround, i, j ) != 0 ) { secondSnitchFlag = true; if (neighborBomb > 0) neighborBomb = RemainingBomb ( playGround, i, j ); }  }
            }
        }
//        if ( RemainingBomb ( playGround, x, y ) == questionMark ) return State.ALONE;
        if ( bombCount == 0 && citizen && questionMark==0 ) return State.CITIZEN;
        if ( firstSnitchFlag ) { bombCount = neighborBomb; return secondSnitchFlag ? State.BELONG_TO_MANY : State.BELONG_TO_ONE; }
        if (bombCount > 0) return (citizen && neighborBomb > 0) ? questionMark > 0 ? State.UNDEFINED : State.IN_DANGER_DEF : State.ALONE;
        return questionMark > 0 ? State.ALONE : State.ALONE;
    }

    public static int ThreatLevel ( char[,] playGround , int x, int y )
    {
        int level = 0;
        for ( int i = x - 1; i <= x + 1; i++ )
        {
            if ( i < 0 || i >= playGround.GetLength ( 0 ) ) continue;
            for ( int j = y - 1; j <= y + 1; j++ )
            {
                if ( j < 0 || j >= playGround.GetLength ( 1 ) || ( i == x && j == y ) ) continue;
                if ( playGround[i, j] == '*' ) level++;
            }
        }
        return level;
    }
    public static int EmptyField( char[,] playGround, int x, int y )
    {
        int level = 0;
        for ( int i = x - 1; i <= x + 1; i++ )
        {
            if ( i < 0 || i >= playGround.GetLength ( 0 ) ) continue;
            for ( int j = y - 1; j <= y + 1; j++ )
            {
                if ( j < 0 || j >= playGround.GetLength ( 1 ) || ( i == x && j == y ) ) continue;
                if ( playGround[i, j] == '?' ) level++;
            }
        }
        return level;
    }
    public static void MakeEmptiesBomb( char[,] playGround, int x, int y )
    {
        for ( int i = x - 1; i <= x + 1; i++ )
        {
            if ( i < 0 || i >= playGround.GetLength ( 0 ) ) continue;
            for ( int j = y - 1; j <= y + 1; j++ )
            {
                if ( j < 0 || j >= playGround.GetLength ( 1 ) || ( i == x && j == y ) ) continue;
                if ( playGround[i, j] == '?' ) playGround[i , j] = '*';
            }
        }
    }
    public static void Pain1 ( char[,] playGround)
    {
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < m; j++ )
            {
                if ( playGround[i, j] != '?' && !Char.IsDigit(playGround[i, j]) ) continue;
                if ( Char.IsDigit ( playGround[i, j] ) )
                {
                    if (RemainingBomb(playGround, i, j) == EmptyField( playGround, i, j ) )
                        MakeEmptiesBomb(playGround, i, j);
                    continue;
                }
                int bombCount = 0;
                State state = GetState ( playGround, i, j, ref bombCount );
                if ( state == State.IN_DANGER_DEF ) playGround[i, j] = (char) ( bombCount + Convert.ToChar ( '0' ) );
                else if ( state == State.ALONE ) playGround[i, j] = '*';
                else if ( state == State.CITIZEN ) playGround[i, j] = '.';
                else if ( state == State.BELONG_TO_ONE && bombCount > 0 ) playGround[i, j] = '*'; 
             }
        }
    }
    public static void Pain2 ( char[,] playGround )
    {
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < m; j++ )
            {
                if ( playGround[i, j] == '?' )
                    playGround[i, j] =  ThreatLevel ( playGround, i, j ) == 0 ? '.' : (char) ( ThreatLevel ( playGround, i, j ) + Convert.ToInt32 ( '0' ) );
            }
        }
    }
    public static void Pain3 ( char[,] playGround )
    {
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < m; j++ )
            {
                if ( playGround[i, j] != '?' && !Char.IsDigit ( playGround[i, j] ) ) continue;
                if ( Char.IsDigit ( playGround[i, j] ) )
                {
                    if ( RemainingBomb ( playGround, i, j ) == EmptyField ( playGround, i, j ) )
                        MakeEmptiesBomb ( playGround, i, j );
                    continue;
                }
                int bombCount = 0;
                State state = GetState ( playGround, i, j, ref bombCount );
                if ( state == State.BELONG_TO_MANY && bombCount > 0)
                {
                    playGround[i, j] = '*';
                }
            }
        }
    }
    public static void Print ( char[,] playGround )
    {
        int bombCount = 0;
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < m; j++ ) 
                if ( playGround[i,j] == '*')
                    bombCount++;
        Console.WriteLine (bombCount);
        for (int I = 0; I < n;I++ )
        {
            for(int J = 0; J < m;J++ )
               Console.Write(playGround[I,J] + " | ");
 //               Console.Write(playGround[I,J] );
            Console.Write ( "\n" );
        }
    }
    public static bool IsEveryOneSatisfied( char[,] playGround )
    {
        return true;
    }
    public static void Main ()
    {
        string[] s = Console.ReadLine ().Split ( " " );
        n = int.Parse ( s[0] ); m = int.Parse ( s[1] );
        char[ , ] c = new Char[ n , m ];
        for (int i = 0; i < n; i++)
        {
            string s2 = Console.ReadLine ();
            for (int j = 0; j < m; j++)
            {
                c[i, j] = s2[j];
            }
        }
        Pain1 ( c );
        Console.WriteLine ("Stage 1");
        Print ( c );
        Pain3 ( c );
        Console.WriteLine ( "Stage 2" );
        Print ( c );
        Pain2 ( c );
        Print ( c );
    }
}