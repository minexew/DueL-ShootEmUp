
#define Function __declspec (dllexport)

typedef struct { short x, y; } WayPoint;

typedef struct
{
    char iHdr[8];
    short verif;
} fhdr; // 10 bytes total

typedef struct
{
    unsigned short ID;
    unsigned short wpCount;
} bhdr;
