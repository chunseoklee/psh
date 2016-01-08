class C
{
    static int N;
    static int[] cr,ms; // ms[0][1][2] => a,b,c
    static void Main(string[] args)
    {
        // Parse input to int
        N = int.Parse(System.Console.ReadLine());
        cr = new int[N];
        ms = new int[3];
        System.Console.WriteLine(N);

        string[] tokens = System.Console.ReadLine().Split();
        for(int i=0;i<3;i++) {
            ms[i] = int.Parse(tokens[i]);
            System.Console.WriteLine(ms[i]);
        }

        tokens = System.Console.ReadLine().Split();
        for(int i=0;i<N;i++) {
            cr[i] = int.Parse(tokens[i]);
            System.Console.WriteLine(cr[i]);
        }
        //// parse input end



    }
}
