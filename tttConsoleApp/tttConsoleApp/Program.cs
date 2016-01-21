using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tttConsoleApps
{
    class Program
    {
        private static string p1n = "CROSSES";
        private static string p2n = "NOUGHTS";
        private static string p1s = "  X";
        private static string p2s = "  O";
        private static int N;
        private static string [,] ar;
        static void Main(string[] args)
        {
            while (true)
            {
                newgame();
                Console.WriteLine("Another game. y/n?");                
                if (Console.ReadLine() != "y")
                {
                    break;
                }
            }
            

        }
        static void newgame()
        {
            
            Console.WriteLine("Tic-tac-toe NxN");
            Console.WriteLine("1 for player vs CPU, 2 for player vs player");
            string mode = Console.ReadLine();
            Console.WriteLine("What is the size N?");
            N = Int32.Parse(Console.ReadLine());
            ar = new string[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    ar[i, j] = (i * N + j + 1).ToString().PadLeft(3, ' ');
                }
            }

            if (mode == "1")
            {
                singlePlayer();
            }
            else if (mode == "2")
            {
                multiPlayer();
            }
            else
            {
                Console.WriteLine("Wrong input");
            }

        }
        static void singlePlayer()
        {
            Console.WriteLine("s");
        }
        static void multiPlayer()
        {
            Console.WriteLine(p1n + " is X. " + p2n +" is O.");
            string pname; // player name
            string sign; // player symbol
            int step = 0; // steps incremental
            int pos_number; // position number
            int winner = 0;
            while(true)
            {
                display_board();
                if (((step++) % 2) == 0)
                {
                    pname = p1n;
                    sign = p1s;
                }
                else {
                    pname = p2n;
                    sign = p2s;
                }
                Console.WriteLine(pname + " please select the number for next step.");
                while (true)
                {
                    pos_number = Int32.Parse(Console.ReadLine()) - 1; // need a error handler
                    if (isOKtoPlace(pos_number))
                    {
                        ar[pos_number / N, pos_number % N] = sign;
                        break;
                    }
                    else
                    {
                        Console.WriteLine((pos_number+1) + " is taken, enter a different number.");
                    }
                }
                
                winner = check_for_winner();
                if (winner == 1)
                {
                    display_board();
                    Console.WriteLine(p1n + " won the game in " + (step/2+1) + " steps");
                    step = 0;
                    break;
                }
                else if (winner == 2)
                {
                    display_board();
                    Console.WriteLine(p2n + " won the game in " + step/2 + " steps");
                    step = 0;
                    break;
                }
                if (!isBoardFull())
                {
                    display_board();
                    Console.WriteLine("Board is full. " + p2n + " won the game in " + (step/2+1) + " steps");
                    step = 0;
                    break;
                }
                
            }
        }
        static void display_board()
        {
            string hline = "-";
            for (int i = 0; i < N; i++)
            {
                hline = hline + "----";
            }
            Console.WriteLine(hline);
            for (int i = 0; i < N; i++)
            {
                Console.Write("|");
                for (int j = 0; j < N; j++)
                {
                    Console.Write(ar[i,j] + "|");
                }
                Console.WriteLine();
                Console.WriteLine(hline);
            }
        }
        static bool isOKtoPlace(int pos)
        {
            if ((ar[pos / N, pos % N] == "  X") || (ar[pos / N, pos % N] == "  O"))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        static int check_for_winner()
        {
            int xo = 0;
            for (int i = 0; i < N; i++) // for horizontal
            {
                for (int j = 0; j < N; j++)
                {
                    if ( ar[i,j] == "  X")
                    {
                        xo++;                        
                    }
                    else if (ar[i,j] == "  O")
                    {
                        xo--;
                    }
                }
                //Console.WriteLine("Test:"+xo);
                if (xo == N)
                {
                    return 1;
                }
                else if (xo == -N)
                {
                    return 2;
                }
                xo = 0;
            }
            for (int i = 0; i < N; i++) // for vertical
            {
                for (int j = 0; j < N; j++)
                {
                    if (ar[j, i] == "  X")
                    {
                        xo++;
                    }
                    else if (ar[j, i] == "  O")
                    {
                        xo--;
                    }
                }
                if (xo == N)
                {
                    return 1;
                }
                else if (xo == -N)
                {
                    return 2;
                }
                xo = 0;
            }
            for (int i = 0; i < N; i++) // for right diagnal
            {
                if (ar[i, i] == "  X")
                {
                    xo++;
                }
                else if (ar[i, i] == "  O")
                {
                    xo--;
                }
            }
            if (xo == N)
            {
                return 1;
            }
            else if (xo == -N)
            {
                return 2;
            }
            xo = 0;
            for (int i = 0; i < N; i++) // for left diagnal
            {
                if (ar[i, (N-i-1)] == "  X")
                {
                    xo++;
                }
                else if (ar[i, (N-i-1)] == "  O")
                {
                    xo--;
                }
            }
            if (xo == N)
            {
                return 1;
            }
            else if (xo == -N)
            {
                return 2;
            }
            return 0;
        }
        static bool isBoardFull()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (!((ar[i, j] == p1s) || (ar[i, j] == p2s)))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    }
}
