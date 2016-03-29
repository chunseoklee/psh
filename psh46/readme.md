# B. KMP algorithm
```cpp
// p[] : pattern
// m   : length of pattern
// b[] : KMP table

void kmp_Preprocess()
{
    int i = 0, j = -1;
    b[i] = j;
    while (i < m)
    {
        while (j >= 0 && p[i] != p[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

int kmpSearch(char t[], char p[], int b[])
{
    int i = 0, j = 0, n = strlen(t), m = strlen(p);

    while (i < n)
    {
        while (j >= 0 && t[i] != p[j])
            j = b[j];
        i++; j++;

        if (j == m)
            return i - j;
    }
    return -1;
}
```
# C. Convex Hull Trick
[http://wcipeg.com/wiki/Convex_hull_trick]
