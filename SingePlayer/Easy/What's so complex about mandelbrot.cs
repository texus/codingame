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
        string c = Console.ReadLine();
        int m = int.Parse(Console.ReadLine());
        
        int SplitPos = c.LastIndexOf('+');
        if (SplitPos == -1)
            SplitPos = c.LastIndexOf('-');
        
        float x = float.Parse(c.Substring(0, SplitPos));
        float y = float.Parse(c.Substring(SplitPos, c.Length - SplitPos - 1));

        float f_real = 0;
        float f_im = 0;
        for (int i = 0; i < m; ++i)
        {
            float next_f_real = f_real*f_real - f_im*f_im + x;
            float next_f_im = 2*f_real*f_im + y;
            f_real = next_f_real;
            f_im = next_f_im;
            
            if (Math.Sqrt(f_real*f_real + f_im*f_im) >= 2)
            {
                Console.WriteLine(i+1);
                return;
            }
        }
        
        Console.WriteLine(m);
    }
}
