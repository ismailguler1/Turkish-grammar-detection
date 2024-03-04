#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>


char alphabet[58] = {'a','b','c','ç','d','e','f','g','ğ','h','ı','i','j','k','l','m','n','o','ö','p','r','s','ş','t','u','ü','v','y','z','A','B','C','Ç','D','E','F','G','Ğ','H','I','İ','J','K','L','M','N','O','Ö','P','R','S','Ş','T','U','Ü','V','Y','Z'};
char consonant[42] = {'b', 'c', 'ç', 'd', 'f', 'g', 'ğ', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'r', 's', 'ş', 't', 'v', 'y', 'z', 'B', 'C', 'Ç', 'D', 'F', 'G', 'Ğ', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'R', 'S', 'Ş', 'T', 'V', 'Y', 'Z'};
char vowel[16] = {'a', 'e', 'ı', 'i', 'o', 'ö', 'u', 'ü', 'A', 'E', 'I', 'İ', 'O', 'Ö', 'U', 'Ü'};

char strongConsonant[16] = {'ç', 'f', 'h', 'k', 'p', 's', 'Ş', 't', 'Ç', 'F', 'H', 'K', 'P', 'S', 'Ş', 'T'};
char softConsonant[26] = {'b', 'c', 'd', 'g', 'ğ', 'j', 'l', 'm', 'n', 'r', 'v', 'y', 'z', 'B', 'C', 'D', 'G', 'Ğ', 'J', 'L', 'M', 'N', 'R', 'V', 'Y', 'Z'};


void NumberOfWords(int word);//Kelime sayısı
void NumberOfLetters(char text[10000]);//Harf sayısı
void NumberOfSentences(char text[10000]);//cümle sayısı
void connexion(char table[1000][20],int word);//ulama
void numOfPluralWords(char table[1000][20], int word);//Çoğul kelime sayısı
void PalatalHarmony(char table[1000][20], int word);//Büyük ünlü uyumu
void strongsoftConsonant(char table[1000][20], int word);//Kalın ünsüz
void Wordsearch(char text[10000]);//Kelime aratma fonksiyonu


int main()
{
    setlocale(LC_ALL, "Turkish_turkish.1254");
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);

    char text[10000];
    char table[1000][20];


    printf("Please write a paragraph : \n");
    gets(text);

    // converting the 1 dimensional array that has been entered to 2 dimensional array
    int letter = 0, word = 0;
    for (int i = 0; i <= (strlen(text)); i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            table[word][letter] = '\0'; // assigning NULL to every word's last position
            word++;                     // after the assignment process increase word's count for next word
            letter = 0;                 // next word's first letter
        }
        else
        {
            table[word][letter] = text[i];   //assigning the character at text[i] to the table[word]
            letter++;
        }
    }

    NumberOfSentences(text);
    NumberOfWords(word);
    NumberOfLetters(text);


    printf("\n\nDEAR USER I'M CHECKING FOR: \n");
    printf("-----------------------------\n");
    printf("Connexion\nPalatal Harmony\nStrong Consonants\nPlural Words\nWord Search\n\nQuit\n");

    //MENU
    char rule1[]="Connexion";
    char rule3[]="Palatal Harmony";
    char rule4[]="Strong Consonants";
    char rule5[]="Plural Words";
    char rule6[]="Word Search";
    char rule8[]="Quit";

    char choice[30];

    do
    {
        printf("\nPlease write the rule you wanted to check :\n");
        gets(choice);

        if (strcmp(choice,rule1)==0)
        {
            connexion(table, word);
        }
        if(strcmp(choice,rule3) == 0)
        {
            PalatalHarmony(table, word);
        }
        if(strcmp(choice,rule4) == 0)
        {
            strongsoftConsonant(table, word);
        }
        if(strcmp(choice,rule5) == 0)
        {
            numOfPluralWords(table, word);
        }
        if(strcmp(choice,rule6) == 0)
        {
            Wordsearch(text);
        }
    }
    while (strcmp(choice,rule8)!=0);  //exits the loop if the user types quit

    return 0;
}


//The function that computes the amount of words in the text
void NumberOfWords(int word)
{
    int num_of_words=0;
    for(int i=0 ; i<word ; i++)
    {
        num_of_words++;
    }
    printf("\nThere are total %d words in this text\n",num_of_words);
}

//The function that computes the amount of letters in the text
void NumberOfLetters(char text[10000])
{
    int numow=0;

    for(int i=0; i<strlen(text); i++)
    {
        for(int j=0; j<58; j++)
        {
            if(text[i]==alphabet[j])
            {
                numow++;
            }
        }
    }

    printf("There are total %d letters in this text",numow);
}

//The function that computes the amount of sentences in the text
void NumberOfSentences(char text[10000])
{
    int num_of_sentences = 0;
    for(int i=0; i<strlen(text); i++)
    {
        if(text[i] == '.')
        {                             //if there are three dots, one sentence will count as 3 that's why we have to substract by 2
            num_of_sentences++;
            if(text[i] == '.' && text[i-1] == '.' && text[i-2] == '.')
            {
                num_of_sentences-=2;
            }
        }
        else if(text[i] == '!')
        {
            num_of_sentences++;
        }
        else if(text[i] == '?')
        {
            num_of_sentences++;
        }
    }
    printf("\nThere are total %d sentences in this text",num_of_sentences);
}

//The function that computes the amount of connexions in the text
void connexion(char table[1000][20],int word)
{
    int con = 0;

    printf("\n Connexions");
    printf("\n------------\n");

    for (int i=0 ; i<word ; i++)
    {
        int size = strlen(table[i]);
        for(int j=0 ; j<16 ; j++)
        {
            for(int k=0; k<42 ; k++)
            {
                if(table[i][size-1] == consonant[k] && table[i+1][0] == vowel[j])
                {
                    printf("%s %s\n", table[i], table[i+1]);
                    con++;
                }
            }
        }
    }
    printf("\nTotal number of connexions in this text : %d\n", con);
}

//The function that computes the amount of words which comply with palatal harmony rule
void PalatalHarmony(char table[1000][20], int word)
{
    printf("\nWords that comply with palatal harmony rule:");
    printf("\n-----------------------------\n");
    int palatal = 0;
    for (int i = 0; i < word; i++)
    {
        int numOfDenseVowel = 0;
        int numOfSlimVowel = 0;

        int size = strlen(table[i]);
        for (int j = 0; j < size; j++)
        {
            if (table[i][j] == 'a' || table[i][j] == 'ı' || table[i][j] == 'o' || table[i][j] == 'u' || table[i][j] == 'A' || table[i][j] == 'I' || table[i][j] == 'O' || table[i][j] == 'U')
            {
                numOfDenseVowel++;
            }
            if (table[i][j] == 'e' || table[i][j] == 'i' || table[i][j] == 'ö' || table[i][j] == 'ü' || table[i][j] == 'E' || table[i][j] == 'İ' || table[i][j] == 'Ö' || table[i][j] == 'Ü')
            {
                numOfSlimVowel++;
            }
        }
        if ((numOfDenseVowel != 0 && numOfSlimVowel == 0) || (numOfDenseVowel == 0 && numOfSlimVowel != 0))
        {
            printf("%s\n", table[i]);
            palatal++;
        }
    }
    printf("\nThere are total %d words that comply with palatal harmony rule\n", palatal);
}


//The function that computes the amount of plural words in the text
void numOfPluralWords(char table[1000][20], int word)
{
    int pluralWords = 0;

    printf("\nPlural words from the text");
    printf("\n-----------------------------\n");
    for (int i = 0; i < word; i++)
    {
        int size = strlen(table[i]);
        for (int j = 0; j < size; j++)
        {
            if (table[i][j] == 'l' && (table[i][j + 1] == 'e' || table[i][j + 1] == 'a') && table[i][j + 2] == 'r')
            {
                printf("%s\n", table[i]);
                pluralWords++;
            }
        }
    }
    printf("\nThere are %d plural words in the text\n", pluralWords);
}

//The function that computes the amount of words that include strong consonants and does not include soft consonants in the text
void strongsoftConsonant(char table[1000][20], int word)
{
    printf("\nWords that include strong consonants and does not include soft consonants");
    printf("\n--------------------------------------------------------------------------\n");
    int strongWords = 0;
    for (int i = 0; i < word; i++)
    {
        int strong = 0, soft = 0;
        int size = strlen(table[i]);
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k<16; k++)
            {
                if (table[i][j] == strongConsonant[k])
                {
                    strong++;
                }
                for (int m = 0; m<26; m++)
                {
                    if (table[i][j] == softConsonant[m])
                    {
                        soft++;
                    }
                }
            }
        }
        if (strong != 0 && soft == 0)
        {
            printf("%s\n", table[i]);
            strongWords++;
        }
    }
    printf("\nThere are %d words that include strong consonants and does not include soft consonants\n", strongWords);
}

//The function that searches for the whether the selected word is present or not
void Wordsearch(char text[10000])
{
    char search[20];
    char newtext[10000];
    char newSearch[20];

    printf("\nPlease write the word you wanted to search :   ");
    gets(search);

    for(int i=0; i<strlen(search); i++)
    {
        newSearch[i] = tolower(search[i]);
    }
    for(int i=0; i<strlen(text); i++)
    {
        newtext[i] = tolower(text[i]);
    }

    char *ptr = strstr(newtext,newSearch);

    if(ptr != NULL)
    {
        printf("The word you have searched for contains in this text\n");
    }
    else
    {
        printf("The word you have serched for does not contain in this text\n");
    }
}