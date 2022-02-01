int abs(int v)
{
    int result = v < 0 ? -v : v;
    return result;
}

int make_array(void)
{
    int array[4];

    for (int i = 0; i < 4; i++)
        array[i] = 10*i;
    return array[0] + abs(array[2]);
}

int diff(int a, int b)
{
    int delta = b - a;
    return abs(delta);
}

int main(void)
{
    int d = diff(33, 107);
    int m = make_array();
    return d + m;
}
