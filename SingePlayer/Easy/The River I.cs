using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static long DigitsSum(long n)
    {
        long sum = 0;
        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }
    
    static void Main(string[] args)
    {
        long r1 = long.Parse(Console.ReadLine());
        long r2 = long.Parse(Console.ReadLine());

        while (r1 != r2)
        {
            if (r1 < r2)
                r1 = r1 + DigitsSum(r1);
            else
                r2 = r2 + DigitsSum(r2);
        }

        Console.WriteLine(r1);
    }
}
