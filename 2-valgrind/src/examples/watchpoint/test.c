/********************************************************************
 *
 *  This is test program to illustrate Purify's Watchpoints
 *
 ********************************************************************/
extern int errno;

int main()
{
    int i;

    printf("Note: &errno = 0x%x.\n", &errno);
    purify_watch(&errno);

    errno = 0;
    close(1000);

    exit(0);
}
