#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LEN 256

int main() {
    char inputs[MAX][LEN];
    int count = 0;
    char buf[LEN];

    printf("\n===== Custom Wordlist Generator =====\n");
    printf("This tool will ask for personal info and generate a smart wordlist.\n\n");

    const char *questions[] = {
        "First name", "Last name", "Nickname", "Partner's name",
        "Child's name", "Pet name", "Company", "Birth year", 
        "Birth date (DDMM)", "Birth place", "Favorite team", "Hobby", "Favorite color"
    };

    for (int i = 0; i < sizeof(questions)/sizeof(questions[0]); i++) {
        printf("%s: ", questions[i]);
        fgets(buf, LEN, stdin);
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) > 0)
            strcpy(inputs[count++], buf);
    }

    printf("\n  Enter extra keywords (one at a time). Press ENTER on empty line to stop.\n");
    while (count < MAX) {
        printf("Keyword: ");
        fgets(buf, LEN, stdin);
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) break;
        strcpy(inputs[count++], buf);
    }

    /// error here?
    if (count == 0) {
    printf("\n[-] You didn't input anything  -_-\n");
    return 1;
}
    ///
    ///
    ///

    FILE *fp = fopen("base.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", inputs[i]);
    }
    fclose(fp);


    printf("\n Downloading a good rule file...\n");
    system("wget -q https://raw.githubusercontent.com/stealthsploit/Optimised-hashcat-Rule/refs/heads/master/OneRuleToRuleThemAll.rule -O OneRuleToRuleThemAll.rule");

    printf("-- Combining words...\n");
    system("hashcat --stdout -a 1 base.txt base.txt > combined.txt");

    printf("-- Applying rules...\n");
    system("hashcat --stdout -a 0 combined.txt -r OneRuleToRuleThemAll.rule > final.txt");

    printf("\n  Done. final wordlist saved as: final.txt\n");

    printf("-- Do you want to delete intermediate files? (y/n): ");
    fgets(buf, LEN, stdin);
    if (buf[0] == 'y' || buf[0] == 'Y') {
        remove("base.txt");
        remove("combined.txt");
        remove("OneRuleToRuleThemAll.rule");
        printf("-- Intermediate files deleted.\n");
    } else {
        printf("-- Intermediate files kept.\n");
    }
  printf("\nIf you think the generated wordlist isn't enough try running your hashcat attack with a mask or add another rule to the wordlist\n cuz i aint doing that for u\n");

    return 0;
}

