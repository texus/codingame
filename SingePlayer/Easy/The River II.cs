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

        for (long r2 = r1-1; r2 > 0; --r2)
        {
            long next = r2 + DigitsSum(r2);
            Console.Error.WriteLine(next);
            if (next == r1)
            {
                Console.WriteLine("YES");
                return;
            }
        }

        Console.WriteLine("NO");
    }
}
