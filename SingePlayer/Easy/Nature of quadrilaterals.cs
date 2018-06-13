using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static double Angle(int xA, int yA, int xB, int yB, int xC, int yC)
    {
        double result = Math.Atan2(yC - yB, xC - xB) - Math.Atan2(yA - yB, xA - xB) % (2*Math.PI);
        if (result < 0)
            return result + 2*Math.PI;
        else
            return result;
    }
    
    static double Length(int xA, int yA, int xB, int yB)
    {
        return Math.Sqrt((xA-xB)*(xA-xB) + (yA-yB)*(yA-yB));
    }
    
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        for (int i = 0; i < n; i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            string A = inputs[0];
            int xA = int.Parse(inputs[1]);
            int yA = int.Parse(inputs[2]);
            string B = inputs[3];
            int xB = int.Parse(inputs[4]);
            int yB = int.Parse(inputs[5]);
            string C = inputs[6];
            int xC = int.Parse(inputs[7]);
            int yC = int.Parse(inputs[8]);
            string D = inputs[9];
            int xD = int.Parse(inputs[10]);
            int yD = int.Parse(inputs[11]);
            
            double AngleA = Math.Round(Angle(xD, yD, xA, yA, xB, yB), 4);
            double AngleB = Math.Round(Angle(xA, yA, xB, yB, xC, yC), 4);
            double AngleC = Math.Round(Angle(xB, yB, xC, yC, xD, yD), 4);
            double AngleD = Math.Round(Angle(xC, yC, xD, yD, xA, yA), 4);
            double LengthAB = Math.Round(Length(xA, yA, xB, yB), 4);
            double LengthBC = Math.Round(Length(xB, yB, xC, yC), 4);
            double LengthCD = Math.Round(Length(xC, yC, xD, yD), 4);
            double LengthDA = Math.Round(Length(xD, yD, xA, yA), 4);
            
            if ((AngleA == AngleB) && (AngleB == AngleC) && (AngleC == AngleD))
            {
                if ((LengthAB == LengthBC) && (LengthBC == LengthCD) && (LengthCD == LengthDA))
                    Console.WriteLine("{0}{1}{2}{3} is a square.", A, B, C, D);
                else
                    Console.WriteLine("{0}{1}{2}{3} is a rectangle.", A, B, C, D);
            }
            else if ((LengthAB == LengthBC) && (LengthBC == LengthCD) && (LengthCD == LengthDA))
                Console.WriteLine("{0}{1}{2}{3} is a rhombus.", A, B, C, D);
            else if ((LengthAB == LengthCD) && (LengthBC == LengthDA) && (AngleA == AngleC) && (AngleB == AngleD))
                Console.WriteLine("{0}{1}{2}{3} is a parallelogram.", A, B, C, D);
            else
                Console.WriteLine("{0}{1}{2}{3} is a quadrilateral.", A, B, C, D);
        }
    }
}
