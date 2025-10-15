#include <stdio.h>
#include <string.h>
#define MAXCITY 30

char cities[MAXCITY][50];
int citycount=0;

void addCity();
void removeCity();
void displayCities();


int main()
{

    addCity();
    removeCity();
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
void removeCity() {
    if (citycount == 0) {
        printf("No cities to remove.\n");
        return;
    }
    displayCities();

    int index;
    printf("Enter index of city to remove: ");
    scanf("%d", &index);

    if (index < 0 || index >= citycount) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index; i < citycount - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }

    (citycount)--;
    printf("City removed successfully.\n");
}
void displayCities(){
    printf("INDEX\t\tCITY\n");
    printf("-------------------\n");
    for(int i=0;i<citycount;i++){
        printf("%d\t\t%s\n",i,cities[i]);
    }
}
