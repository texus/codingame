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
        string ENCRYPT = Console.ReadLine();
        var parts = ENCRYPT.Split();

        // Convert unary to binary
        string binary = "";
        int type = -1;
        for (int i = 0; i < parts.Length; ++i)
        {
            if (type == -1)
            {
                if (parts[i].Length == 1)
                    type = 1;
                else if (parts[i].Length == 2)
                    type = 0;
                else
                {
                    Console.WriteLine("INVALID");
                    return;
                }
            }
            else if (type == 0)
            {
                for (int j = 0; j < parts[i].Length; ++j)
                    binary += "0";
                
                type = -1;
            }
            else if (type == 1)
            {
                for (int j = 0; j < parts[i].Length; ++j)
                    binary += "1";
                
                type = -1;
            }
        }
        
        // Binary string has to contain 7 bits per character
        if (binary.Length % 7 != 0)
        {
            Console.WriteLine("INVALID");
            return;
        }
        
        // Extract characters from binary string
        for (int i = 0; i < binary.Length / 7; ++i)
        {
            string charBinary = binary.Substring(7*i, 7);
            
            int charToDisplay = 0;
            for (int j = 0; j < 7; ++j)
                charToDisplay += (int)(Math.Pow(2, 6-j) * (charBinary[j] - '0'));
            
            Console.Write((char)charToDisplay);
        }
                
        Console.Write("\n");
    }
}
