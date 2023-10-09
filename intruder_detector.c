#define MAG0 1
#define MAG1 2
#define MAG2 4
#define LED0 8
#define LED1 16
#define LED2 32
#define BUZZER 64

int ledpin_val[3] = {0xFFFFFFF7, 0xFFFFFFEF, 0xFFFFFFDF};   // LED0 - 11111111111111111111111111110111
                                                            // LED1 - 11111111111111111111111111101111
                                                            // LED2 - 11111111111111111111111111011111

int buzzerpin_val = 0xFFFFFFBF;   // BUZZ - 11111111111111111111111110111111

// Output pins
int buzzerpin = 0;
int ledpin[3] = {0};

// Input pins 
int magpin[3] = {0};

int main()
{

    while(1){
        // Read from the magnetic reed switches
        asm (
            "and %0, x30, 1"        //MAG0
            : "=r"(magpin[0])
        );

        asm (
            "and %0, x30, 2"        //MAG1
            : "=r"(magpin[1])
        );

        asm (
            "and %0, x30, 4"        //MAG2
            : "=r"(magpin[2])
        );

        if(!magpin[0]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[0] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 8"         //LED0
                :
                :"r"(ledpin_val[0])
                :"x30"
            );
        }
        if(!magpin[1]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[1] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 16"         //LED1
                :
                :"r"(ledpin_val[1])
                :"x30"
            );
        }
        if(!magpin[2]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[2] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 32"         //LED2
                :
                :"r"(ledpin_val[2])
                :"x30"
            );
        }
        if(magpin[0] && magpin[1] && magpin[2]){
            buzzerpin = 0;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[0] = 0;
            ledpin[1] = 0;
            ledpin[2] = 0;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED0
                :
                :"r"(ledpin_val[0])
                :"x30"
            );
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED1
                :
                :"r"(ledpin_val[1])
                :"x30"
            );
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED2
                :
                :"r"(ledpin_val[2])
                :"x30"
            );
        }
    }

    return 0;
}