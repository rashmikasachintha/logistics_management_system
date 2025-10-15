#include <stdio.h>
#include <string.h>
#define MAXCITY 30
#define FUELPRICE 310
#define MAXDELIVERY 50

char cities[MAXCITY][50];
int distance[MAXCITY][MAXCITY];
int citycount=0;
char vehicleNames[3][10] = {"Van", "Truck", "Lorry"};
int deliveryCount=0;
int sourcedel[MAXDELIVERY],destinationdel[MAXDELIVERY],weightdel[MAXDELIVERY],vehicleTypedel[MAXDELIVERY];
float deliveryCostdel[MAXDELIVERY], fuelUseddel[MAXDELIVERY],fuelCostdel[MAXDELIVERY],totalCostdel[MAXDELIVERY],profitdel[MAXDELIVERY],customerChargedel[MAXDELIVERY],timedel[MAXDELIVERY] ;

void addCity();
void removeCity();
void displayCities();
void distanceInput();
void displayDistance();
void DeliveryRequestHandling();


int main()
{

    addCity();
    removeCity();
    displayDistance();
    distanceInput();
    DeliveryRequestHandling();
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
void distanceInput(){
    int start,stop,dist;
    displayCities(cities,&citycount);
    if(citycount<2){
        printf("add at least two cities\n");
        return;
    }
    printf("Enter start city index:");
    scanf("%d",&start);
    printf("Enter destination index: ");
    scanf("%d",&stop);
    if(start==stop){
        printf("Distance=0");
        distance[start][stop]=distance[stop][start]=0;
        return;

    }
    printf("Enter distance between %s-%s :",cities[start],cities[stop]);
    scanf("%d",&dist);
    distance[start][stop]=distance[stop][start]=dist;
}
void displayDistance(){
    printf("\n--Distance Table--\n");
    printf("\t");
    for(int i=0;i<citycount;i++){
        printf("%s\t",cities[i]);
    }
    printf("\n");

    for(int i=0;i<citycount;i++){
        printf("%s\t",cities[i]);
        {
            for(int k=0;k<citycount;k++){
                printf("%d\t",distance[i][k]);
            }
            printf("\n");
        }
    }

}
void DeliveryRequestHandling(){
    int source,destination,weight,vehicletype;
    displayCities(cities,citycount);
    printf("Enter source city index:");
    scanf("%d",&source);
    printf("Enter destination city index:");
    scanf("%d",&destination);

    if(source == destination){
        printf("source city and destination city should be defferent");
        return;
    }
    printf("Enter weight(in kg):");
    scanf("%d",&weight);
    printf("1=Van\n2=Truck\n3=Lorry\n");
    printf("Enter vehicle type(NO):");
    scanf("%d",&vehicletype);

    int rateperkm[]={30,40,80};
    int capacity[]={1000,5000,10000};
    int avgspeed[]={60,50,45};
    int fuelefficiency[]={12,6,4};

    if(weight>capacity[vehicletype-1]){
        printf("Weight exceed vehicle maximum capacity");
        return;
    }
    float d=(float)distance[source][destination];
    float deliverycost=d*rateperkm[vehicletype-1]*(1+weight*(1.0/10000.0));
    float speed=(float)avgspeed[vehicletype-1];
    float deliverytime=deliverycost/speed;
    float fuelused=d/(float)fuelefficiency[vehicletype-1];
    float fuelcost=fuelused*FUELPRICE;
    float totalcost=deliverycost+fuelcost;
    float profit=totalcost*0.25;
    float finalcharge=totalcost+profit;

    sourcedel[deliveryCount] = source;
    destinationdel[deliveryCount] =destination;
    weightdel[deliveryCount] = weight;
    vehicleTypedel[deliveryCount] = vehicletype;
    deliveryCostdel[deliveryCount] = deliverycost;
    fuelUseddel[deliveryCount] = fuelused;
    fuelCostdel[deliveryCount] = fuelcost;
    totalCostdel[deliveryCount] = totalcost;
    profitdel[deliveryCount] = profit;
    customerChargedel[deliveryCount] = finalcharge;
    timedel[deliveryCount] = deliverytime;


    printf("\n====Dilvery Cost Estimation====\n");
    printf("From:%s\nTo:%s\nVehicle:%s\nWeight:%.2f kg\n",cities[sourcedel[deliveryCount]],cities[destinationdel[deliveryCount]],vehicleNames[vehicleTypedel[deliveryCount]],weightdel[deliveryCount]);
    printf("Delivery Cost:%.2f\n",deliveryCostdel[deliveryCount]);
    printf("Fuel Used:%.2f\n",fuelUseddel[deliveryCount]);
    printf("Fuel Cost:%.2f\n",fuelCostdel[deliveryCount]);
    printf("Total cost:%.2f\n",totalCostdel[deliveryCount]);
    printf("Profit:%.2f\n",profitdel[deliveryCount]);
    printf("Customer Charge:%.2f\n",customerChargedel[deliveryCount]);
    printf("Estimated Time:%.2f\n",timedel[deliveryCount]);
    printf("===============================================\n");

    deliveryCount++;

}

