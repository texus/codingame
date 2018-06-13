using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static List<string> Words = new List<string>();
    static List<List<char>> Grid = new List<List<char>>();
    static List<List<bool>> GridRemaining = new List<List<bool>>();

    static void TryMatchSingWord(int x, int y, int dirX, int dirY, string word)
    {
        for (int i = 0; i < word.Length; ++i)
        {
            if (y + i*dirX < 0)
                return;
            if (x + i*dirY < 0)
                return;
            if (y + i*dirX >= Grid.Count)
                return;
            if (x + i*dirY >= Grid[0].Count)
                return;
            
            if (Grid[y + i*dirX][x + i*dirY] != word[i])
                return;
        }

        for (int i = 0; i < word.Length; ++i)
            GridRemaining[y + i*dirX][x + i*dirY] = false;
    }
    
    static void TryMatchWords(int x, int y)
    {
        foreach (string word in Words)
        {
            TryMatchSingWord(x, y, 1, 1, word);
            TryMatchSingWord(x, y, 1, 0, word);
            TryMatchSingWord(x, y, 1, -1, word);
            TryMatchSingWord(x, y, 0, 1, word);
            TryMatchSingWord(x, y, 0, -1, word);
            TryMatchSingWord(x, y, -1, 1, word);
            TryMatchSingWord(x, y, -1, 0, word);
            TryMatchSingWord(x, y, -1, -1, word);
        }
    }
    
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for (int i = 0; i < n; i++)
        {
            string aword = Console.ReadLine();
            Words.Add(aword);
        }
        string[] inputs = Console.ReadLine().Split(' ');
        int h = int.Parse(inputs[0]);
        int w = int.Parse(inputs[1]);
        for (int i = 0; i < h; i++)
        {
            string line = Console.ReadLine();
            Grid.Add(new List<char>());
            GridRemaining.Add(new List<bool>());
            foreach (char c in line)
            {
                Grid[i].Add(c);
                GridRemaining[i].Add(true);
            }
        }

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
                TryMatchWords(x, y);
        }
        
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                if (GridRemaining[y][x])
                    Console.Write(Grid[y][x]);
            }
        }
        Console.WriteLine();
    }
}
