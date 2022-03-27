
int sum(int x, int y, int z)
{
    return x + y + z;
}

int sqr(int v)
{
    return v * v;
}

int delta(int a, int b)
{
    int diff = sqr(a) - sqr(b);
    return diff;
}

int main(void)
{
    int x = sum(5, 11, 8);
    int y = delta(3, x);

    return y;
}
