#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXCITY 30
#define FUELPRICE 310
#define MAXDELIVERY 50

char cities[MAXCITY][50];
int distance[MAXCITY][MAXCITY];
int citycount=0;
char vehicleNames[3][10] = {"Van", "Truck", "Lorry"};
int deliveryCount=0;
int bestPath[MAXCITY], tempPath[MAXCITY], visited[MAXCITY];
int minDistance;

int sourcedel[MAXDELIVERY],destinationdel[MAXDELIVERY],weightdel[MAXDELIVERY],vehicleTypedel[MAXDELIVERY];
float deliveryCostdel[MAXDELIVERY], fuelUseddel[MAXDELIVERY],fuelCostdel[MAXDELIVERY],totalCostdel[MAXDELIVERY],profitdel[MAXDELIVERY],customerChargedel[MAXDELIVERY],timedel[MAXDELIVERY] ;
int source,destination,weight,vehicletype;

void addCity();
void removeCity();
void renameCity();
void displayCities();
void distanceInput();
void displayDistance();
void DeliveryRequestHandling();
void permute(int depth, int currentCity, int destination, int totalDistance, int source);
void findLeastCostRoute(int source, int destination);
void deliveryReports();
void saveDistanceDataToTxtFile();
void saveDeliveryDataToTxtFile();
void loadDistanceDataFromTxtFile();


int main(){
    loadDistanceDataFromTxtFile();

    int choice;
do {
    printf("\n----Logistics Management System----\n");
    printf("1. Add City\n");
    printf("2. Remove City\n");
    printf("3. Rename City\n");
    printf("4. Distance Input\n");
    printf("5. Show Distance Table\n");
    printf("6. Enter Delivery Details\n");
    printf("7. Find Least-Cost Route\n");
    printf("8. View Delivery Reports\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);


    switch(choice) {
        case 1:
             addCity();
             break;
        case 2:
             removeCity();
             break;
        case 3:
            renameCity();
            break;
        case 4:
             distanceInput();
             break;
        case 5:
             displayDistance();
             break;
        case 6:
             DeliveryRequestHandling();
             break;
        case 7:{
            int src, dest;
            displayCities();
            printf("Enter source city index: ");
            scanf("%d", &src);
            printf("Enter destination city index: ");
            scanf("%d", &dest);
            findLeastCostRoute(src, dest);
            break;
           }

        case 8:
             deliveryReports();
             break;

        case 0:
            saveDistanceDataToTxtFile();
            saveDeliveryDataToTxtFile();
            printf("Exiting...\n");
            break;
         default:
            printf("Invalid choice.\n");

}
} while (choice != 0);





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
void renameCity() {
    int index;
    char newName[50];
    displayCities();
    printf("Enter index of city to rename: ");
    scanf("%d", &index);
    if (index < 0 || index >= citycount) {
        printf("Invalid index.\n");
        return;
    }
    printf("Enter new name: ");
    scanf("%s", newName);
    strcpy(cities[index], newName);
    printf("City renamed successfully.\n");
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
    displayCities();
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

    displayCities();
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
    float deliverytime=d/speed;
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
void permute(int depth, int currentCity, int destination, int totalDistance, int source) {
    if (depth == 3 || currentCity == destination) {
        totalDistance += distance[currentCity][destination];
        if (totalDistance < minDistance) {
            minDistance = totalDistance;
            memcpy(bestPath, tempPath, sizeof(int) * depth);
            bestPath[depth] = destination;
        }
        return;
    }

    for (int i = 0; i < citycount; i++) {
        if (!visited[i] && i != source && i != destination && distance[currentCity][i] > 0) {
            visited[i] = 1;
            tempPath[depth] = i;
            permute(depth + 1, i, destination, totalDistance + distance[currentCity][i], source);
            visited[i] = 0;
        }
    }
}
void findLeastCostRoute(int source, int destination){

    if (source == destination) {
        printf("Source and destination must be different.\n");
        return;
    }
    if (source < 0 || source >= citycount || destination < 0 || destination >= citycount) {
    printf("Invalid city index.\n");
    return;
}



    minDistance = INT_MAX;
    memset(visited, 0, sizeof(visited));
    memset(tempPath, -1, sizeof(tempPath));
    memset(bestPath, -1, sizeof(bestPath));

    visited[source] = 1;
    permute(0, source, destination, 0, source);

    if (minDistance == INT_MAX) {
        printf("No valid route found.\n");
        return;
    }

    printf("\n--- Least-Cost Route ---\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[destination]);
    printf("Route: %s", cities[source]);
    for (int i = 0; i < 4 && bestPath[i] != -1; i++) {
        printf(" -> %s ", cities[bestPath[i]]);
    }
    printf("\n");
    printf("Minimum Distance: %d km\n", minDistance);
    printf("-------------------------\n");
}
void deliveryReports() {
    float totalDistance = 0, totalTime = 0, totalRevenue = 0, totalProfit = 0;
    int longest = 0, shortest = INT_MAX;

    for (int i = 0; i < deliveryCount; i++) {
        int d = distance[sourcedel[i]][destinationdel[i]];
        totalDistance += d;
        totalTime += timedel[i];
        totalRevenue += customerChargedel[i];
        totalProfit += profitdel[i];
        if (d > longest) longest = d;
        if (d < shortest) shortest = d;
    }

    printf("\n--- Performance Report ---\n");
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", totalDistance);
    printf("Average Delivery Time: %.2f hours\n", deliveryCount ? totalTime / deliveryCount : 0);
    printf("Total Revenue: %.2f LKR\n", totalRevenue);
    printf("Total Profit: %.2f LKR\n", totalProfit);
    printf("Longest Route: %d km\n", longest);
    printf("Shortest Route: %d km\n", shortest);
    printf("---------------------------\n");
}
void saveDistanceDataToTxtFile() {
    FILE *froute = fopen("routes.txt", "w");
    if (froute == NULL) {
        printf("Cannot create file!\n");
        return;
    }


    fprintf(froute, "City count: %d\n\n", citycount);


    fprintf(froute, "%-12s", "");
    for (int i = 0; i < citycount; i++) {
        fprintf(froute, "%-12s", cities[i]);
    }
    fprintf(froute, "\n");


    for (int i = 0; i < citycount; i++) {
        fprintf(froute, "%-12s", cities[i]);
        for (int j = 0; j < citycount; j++) {
            fprintf(froute, "%-12d", distance[i][j]);
        }
        fprintf(froute, "\n");
    }

    fclose(froute);
}
void saveDeliveryDataToTxtFile() {
    FILE *fdel = fopen("deliveries.txt", "w");
    if (fdel == NULL) {
        printf("Cannot create file!\n");
        return;
    }

    fprintf(fdel, "Delivery Count: %d\n\n", deliveryCount);


    fprintf(fdel, "%-4s %-12s %-12s %-8s %-8s %-12s %-12s %-12s %-14s %-12s %-16s %-12s\n",
            "No", "Source", "Destination", "Weight", "Vehicle", "BaseCost", "FuelUsed",
            "FuelCost", "OperationalCost", "Profit", "CustomerCharge", "Time(hrs)");


    for (int i = 0; i < deliveryCount; i++) {
        fprintf(fdel, "%-4d %-12s %-12s %-8d %-8s %-12.2f %-12.2f %-12.2f %-14.2f %-12.2f %-16.2f %-12.2f\n",
                i + 1,cities[sourcedel[i]],cities[destinationdel[i]],weightdel[i],
                vehicleTypedel[i] == 1 ? "Van" :
                vehicleTypedel[i] == 2 ? "Truck" : "Lorry",
                deliveryCostdel[i],fuelUseddel[i],fuelCostdel[i],totalCostdel[i], profitdel[i],customerChargedel[i],timedel[i]);

    }

    fclose(fdel);
}
void loadDistanceDataFromTxtFile() {
    FILE *froute = fopen("routes.txt", "r");
    if (froute == NULL) {
        printf("routes.txt not found. Starting fresh.\n");
        return;
    }

    fscanf(froute, "City count: %d\n\n", &citycount);


    char temp[100];
    for (int i = 0; i < citycount + 1; i++) {
        fscanf(froute, "%s", temp);
    }


    for (int i = 0; i < citycount; i++) {
        fscanf(froute, "%s", cities[i]);
        for (int j = 0; j < citycount; j++) {
            fscanf(froute, "%d", &distance[i][j]);
        }
    }

    fclose(froute);
}
