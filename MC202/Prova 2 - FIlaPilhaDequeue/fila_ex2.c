int dequeue(int* bottom, char* fila, int size)
{
    *bottom = (*bottom + 1) % size;
    return 1;
}

int firstUniqChar(char* s) 
{
    int size = strlen(s);
    int top = size;
    int bottom = 0;
    int j = 0;

    while(bottom < size)
    {
        int repetido = 0;

        while(j < size)
        {
            if (s[bottom] == s[j])
            {
                repetido = 1;
                dequeue(&bottom, s, size);
                break;
            }
            j++;
        }

        if (!repetido)
        {
            return s[bottom];
        }
    }

    return -1;
}