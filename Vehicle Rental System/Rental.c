#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vehicle {
    int id;
    char name[50];
    char type[20];
    float price;
    int available;
    char location[50];
};


void addVehicle() {
    struct Vehicle v;
    FILE *fp = fopen("vehicles.txt", "a");

    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID: \n");
    scanf("%d", &v.id);

    printf("Enter Name: \n");
    scanf("%s", v.name);

    printf("Enter Type: \n");
    scanf("%s", v.type);

    printf("Enter Price per day: \n");
    scanf("%f", &v.price);

    printf("Enter Location: \n");
    scanf("%s", v.location);

    v.available = 1;

    fprintf(fp, "%d %s %s %.2f %d %s\n",
            v.id, v.name, v.type, v.price, v.available, v.location);

    fclose(fp);
    printf("Vehicle Added Successfully!\n");
}


void viewVehicles() {
    struct Vehicle v;
    FILE *fp = fopen("vehicles.txt", "r");

    if(fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\n   Vehicle List   \n");

    while(fscanf(fp, "%d %s %s %f %d %s",
          &v.id, v.name, v.type, &v.price, &v.available, v.location) != EOF) {

        printf("ID: %d | Name: %s | Type: %s | Price: %.2f | %s | Location: %s\n",
               v.id, v.name, v.type, v.price,
               v.available ? "Available" : "Booked",
               v.location);
    }

    fclose(fp);
}



void searchByLocation() {
    char loc[50];
    struct Vehicle v;
    FILE *fp = fopen("vehicles.txt", "r");

    if(fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("Enter location: ");
    scanf("%s", loc);

    printf("\nAvailable vehicles in %s:\n", loc);

    while(fscanf(fp, "%d %s %s %f %d %s",
          &v.id, v.name, v.type, &v.price, &v.available, v.location) != EOF) {

        if(strcmp(v.location, loc) == 0 && v.available == 1) {
            printf("ID: %d | %s | %.2f per day\n", v.id, v.name, v.price);
        }
    }

    fclose(fp);
}


void bookVehicle() {
    int id, days;
    struct Vehicle v;
    FILE *fp = fopen("vehicles.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Vehicle ID to book: ");
    scanf("%d", &id);

    printf("Enter number of days: ");
    scanf("%d", &days);

    int found = 0;

    while(fscanf(fp, "%d %s %s %f %d %s",
          &v.id, v.name, v.type, &v.price, &v.available, v.location) != EOF) {

        if(v.id == id && v.available == 1) {
            v.available = 0;
            float total = days * v.price;
            printf("Booking Successful!\nTotal Amount: %.2f\n", total);
            found = 1;
        }

        fprintf(temp, "%d %s %s %.2f %d %s\n",
                v.id, v.name, v.type, v.price, v.available, v.location);
    }

    if(!found) {
        printf("Vehicle not available!\n");
    }

    fclose(fp);
    fclose(temp);

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");
}


void returnVehicle() {
    int id;
    struct Vehicle v;
    FILE *fp = fopen("vehicles.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Vehicle ID to return: ");
    scanf("%d", &id);

    int found = 0;

    while(fscanf(fp, "%d %s %s %f %d %s",
          &v.id, v.name, v.type, &v.price, &v.available, v.location) != EOF) {

        if(v.id == id && v.available == 0) {
            v.available = 1;
            printf("Vehicle Returned Successfully!\n");
            found = 1;
        }

        fprintf(temp, "%d %s %s %.2f %d %s\n",
                v.id, v.name, v.type, v.price, v.available, v.location);
    }

    if(!found) {
        printf("Invalid ID or already available!\n");
    }

    fclose(fp);
    fclose(temp);

    remove("vehicles.txt");
    rename("temp.txt", "vehicles.txt");
}


int main() {
    int choice;

    while(1) {
        printf("\n    Vehicle Rental System   \n");
        printf("1. Add Vehicle\n");
        printf("2. View Vehicles\n");
        printf("3. Search by Location\n");
        printf("4. Book Vehicle\n");
        printf("5. Return Vehicle\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
            addVehicle(); 
            break;
            case 2: 
            viewVehicles(); 
            break;
            case 3: 
            searchByLocation(); 
            break;
            case 4: 
            bookVehicle(); 
            break;
            case 5: 
            returnVehicle(); 
            break;
            case 6: 
            exit(0);
            default: 
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
