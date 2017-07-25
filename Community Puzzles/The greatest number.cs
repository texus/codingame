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
        int N = int.Parse(Console.ReadLine());
        string input = Console.ReadLine();

        var chars = input.Split();
        Array.Sort(chars);

        // Exception for when all numbers are 0
        if (chars[chars.Length-1] == "0")
        {
            Console.WriteLine(0);
            return;
        }

        if (chars[0] == "-")
        {
            Console.Write('-');
            
            if (chars[1] == ".")
            {
                Console.Write(chars[2]);
                Console.Write(".");

                for (int i = 3; i < chars.Length; ++i)
                    Console.Write(chars[i]);
            }
            else // No comma
            {
                var index = 1;
                while (chars[index] == "0")
                    index++;
                
                for (int i = index; i < chars.Length; ++i)
                    Console.Write(chars[i]);
            }
        }
        else // Number is positive
        {
            if (chars[0] == ".")
            {
                Console.Write(chars[chars.Length-1]);

                for (int i = chars.Length-2; i > 1; --i)
                    Console.Write(chars[i]);
                
                // A zero behind the comma is dropped
                if (chars[1] != "0")
                {
                    Console.Write('.');
                    Console.Write(chars[1]);
                }
            }
            else // No comma
            {
                var index = 1;
                while (chars[index] == "0")
                    index++;
                
                for (int i = chars.Length; i > 0; --i)
                    Console.Write(chars[i-1]);
            }
        }
        
        Console.Write("\n");
    }
}
