#include <stdio.h>
#include <string.h>
#define MAXCITY 30

char cities[MAXCITY][50];
int citycount=0;

void addCity();

int main()
{

    addCity();
    return 0;
}
void addCity(){
    if(citycount >= MAXCITY){
        printf("Reached to city limit\n");
        return;

    }
    else{
        char city[50];
        printf("Enter city %d name:",citycount+1);
        scanf("%s",city);

        for(int i=0;i<citycount;i++){
            if(strcmp(city,cities[i])==0){
                printf("This city is already exist!\n");
                return;
            }

        }
        strcpy(cities[citycount],city);
       (citycount)++;

    }

}
