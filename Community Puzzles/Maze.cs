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
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int W = int.Parse(inputs[0]);
        int H = int.Parse(inputs[1]);
        inputs = Console.ReadLine().Split(' ');
        int X = int.Parse(inputs[0]);
        int Y = int.Parse(inputs[1]);
        
        int[,] grid = new int[W,H];
        for (int i = 0; i < H; i++)
        {
            string R = Console.ReadLine();
            for (int j = 0; j < W; j++)
                grid[j,i] = R[j];
        }

        var positions = new List<Tuple<int,int>>();
        positions.Add(new Tuple<int,int>(X,Y));

        var answers = new List<Tuple<int,int>>();
        while (positions.Count > 0)
        {
            var newPositions = new List<Tuple<int,int>>();
            foreach (var pos in positions)
            {
                // A position can be added twice when two of its neighbors were inspected at the same time
                if (grid[pos.Item1, pos.Item2] == '+')
                    continue;
                
                grid[pos.Item1, pos.Item2] = '+';

                if (pos.Item2 + 1 < H && grid[pos.Item1, pos.Item2 + 1] == '.')
                    newPositions.Add(new Tuple<int,int>(pos.Item1, pos.Item2 + 1));
                if (pos.Item2 > 0 && grid[pos.Item1, pos.Item2 - 1] == '.')
                    newPositions.Add(new Tuple<int,int>(pos.Item1, pos.Item2 - 1));
                if (pos.Item1 + 1 < W && grid[pos.Item1 + 1, pos.Item2] == '.')
                    newPositions.Add(new Tuple<int,int>(pos.Item1 + 1, pos.Item2));
                if (pos.Item1 > 0 && grid[pos.Item1 - 1, pos.Item2] == '.')
                    newPositions.Add(new Tuple<int,int>(pos.Item1 - 1, pos.Item2));
                
                if (pos.Item1 == 0 || pos.Item2 == 0 || pos.Item1 == W-1 || pos.Item2 == H-1)
                    answers.Add(new Tuple<int,int>(pos.Item1, pos.Item2));
            }
            
            positions = newPositions;
        }
        
        answers.Sort((x, y) => {
            int result = x.Item1.CompareTo(y.Item1);
            return result == 0 ? x.Item2.CompareTo(y.Item2) : result;
        });
        
        Console.WriteLine(answers.Count);
        foreach (var pos in answers)
            Console.WriteLine(pos.Item1.ToString() + " " + pos.Item2.ToString());
    }
}
