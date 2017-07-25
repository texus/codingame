using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static void Main(string[] args)
    {
        int L = int.Parse(Console.ReadLine());
        int N = int.Parse(Console.ReadLine());
        var Data = new Tuple<string, int, uint>[N];
        for (int i = 0; i < N; i++)
        {
            string R = Console.ReadLine();
            var Pieces = R.Split();
            Data[i] = new Tuple<string, int, uint>(Pieces[0], int.Parse(Pieces[1]), uint.Parse(Pieces[2]));
        }

        bool SpeedingFound = false;
        for (int i = 1; i < N; i++)
        {
            var distance = Data[i].Item2 - Data[i-1].Item2;
            var duration = (Data[i].Item3 - Data[i-1].Item3) / 3600.0;
            
            if (distance / duration > L)
            {
                Console.WriteLine(Data[i].Item1 + " " + Data[i].Item2.ToString());
                SpeedingFound = true;
            }
        }

        if (!SpeedingFound)
            Console.WriteLine("OK");
    }
}
