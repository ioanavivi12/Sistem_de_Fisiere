
typedef struct nod{
    void *info;
    struct nod *st, *dr;
}TNod, *TArb;

TArb NewNod(char *nume, TArb p, void *(*NewInfo)(char *, TArb));
int AddNod(TArb root, TArb newnod, int (*CompInfo)(void *, void *));
void PrintArb(TArb nod, void (*PrintInfo)(void *));
TArb CautaNod(TArb root, char *nume, int(*CompName)(void *, char *));
void DistrugereNod(TArb *nod, void (*DistrugereInfo)(void **));
TArb ParinteNod(TArb arb, TArb nod, int (*CompInfo)(void *, void *));
TArb StergereNod(TArb nod, void (*DistrugereInfo)(void **));
void DistrugereArbore(TArb *arb,  void (*DistrugereInfo)(void **));