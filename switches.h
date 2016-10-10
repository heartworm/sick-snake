#define OFFHATU 0
#define OFFHATD 1
#define OFFHATL 2
#define OFFHATR 3
#define OFFBUTL 4
#define OFFBUTR 5


#define HATL ((buttonState >> OFFHATL) & 1)
#define HATR ((buttonState >> OFFHATR) & 1)
#define HATU ((buttonState >> OFFHATU) & 1)
#define HATD ((buttonState >> OFFHATD) & 1)
#define BUTR ((buttonState >> OFFBUTR) & 1)
#define BUTL ((buttonState >> OFFBUTL) & 1)