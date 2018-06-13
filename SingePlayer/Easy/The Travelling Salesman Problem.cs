using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Point
{
    public int x;
    public int y;
    public Point(int X, int Y)
    {
        x = X;
        y = Y;
    }
}

class Solution
{
    static double Distance(Point P1, Point P2)
    {
        return Math.Sqrt(Math.Pow(P1.x-P2.x, 2) + Math.Pow(P1.y-P2.y, 2));
    }
    
    static void Main(string[] args)
    {
        var Points = new List<Point>();
        int N = int.Parse(Console.ReadLine());
        for (int i = 0; i < N; i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            int X = int.Parse(inputs[0]);
            int Y = int.Parse(inputs[1]);
            Points.Add(new Point(X, Y));
        }

        var FirstPoint = Points[0];
        var LastPoint = FirstPoint;
        Points.RemoveAt(0);
        
        double TotalDist = 0;
        while (Points.Count > 0)
        {
            double MinDist = int.MaxValue;
            Point ClosestPoint = null;
            foreach (var P in Points)
            {
                double Dist = Distance(LastPoint, P);
                if (Dist < MinDist)
                {
                    MinDist = Dist;
                    ClosestPoint = P;
                }
            }
            Console.Error.WriteLine(MinDist);
            TotalDist += MinDist;
            LastPoint = ClosestPoint;
            Points.Remove(ClosestPoint);
        }
        
        TotalDist += Distance(LastPoint, FirstPoint);
        Console.WriteLine(Math.Round(TotalDist));
    }
}
