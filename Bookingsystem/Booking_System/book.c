#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Taxi
{
    int id;
    char driverName[50];
    char carName[50];
    char carNumber[20];
    char location[50];
    int available;
};

struct Booking
{
    int bookingId;
    char customerName[50];
    char pickup[50];
    char drop[50];
    float distance;
    float chargeAmount;
    char paymentMethod[20];
    char paymentStatus[20];
};


void addTaxi()
{
    struct Taxi t;

    FILE *fp;

    fp = fopen("taxi.txt", "ab");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nADD TAXI\n");

    printf("Enter Taxi ID: ");
    scanf("%d", &t.id);

    printf("Enter Driver Name: ");
    scanf("%s", t.driverName);

    printf("Enter Car Name: ");
    scanf("%s", t.carName);

    printf("Enter Car Number: ");
    scanf("%s", t.carNumber);

    printf("Enter Taxi Location: ");
    scanf("%s", t.location);

    t.available = 1;

    fwrite(&t, sizeof(t), 1, fp);

    fclose(fp);

    printf("\nTaxi Added Successfully!\n");
}


void viewTaxi()
{
    struct Taxi t;

    FILE *fp;

    fp = fopen("taxi.txt", "rb");

    if (fp == NULL)
    {
        printf("\nNo Taxi Records Found!\n");
        return;
    }

    printf("\n TAXI DETAILS \n");

    while (fread(&t, sizeof(t), 1, fp))
    {
        printf("\nTaxi ID      : %d\n", t.id);
        printf("Driver Name  : %s\n", t.driverName);
        printf("Car Name     : %s\n", t.carName);
        printf("Car Number   : %s\n", t.carNumber);
        printf("Location     : %s\n", t.location);

        if (t.available == 1)
        {
            printf("Status       : Available\n");
        }
        else
        {
            printf("Status       : Booked\n");
        }
    }

    fclose(fp);
}


void bookTaxi()
{
    struct Taxi t;
    struct Booking b;

    FILE *ft;
    FILE *fb;

    int found = 0;
    int paymentChoice;

    ft = fopen("taxi.txt", "rb+");
    fb = fopen("booking.txt", "ab");

    if (ft == NULL || fb == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nBOOK TAXI\n");

    printf("Enter Booking ID: ");
    scanf("%d", &b.bookingId);

    printf("Enter Customer Name: ");
    scanf("%s", b.customerName);

    printf("Enter Pickup Location: ");
    scanf("%s", b.pickup);

    printf("Enter Drop Location: ");
    scanf("%s", b.drop);

    printf("Enter Distance (KM): ");
    scanf("%f", &b.distance);

    while (fread(&t, sizeof(t), 1, ft))
    {
        if (strcmp(t.location, b.pickup) == 0 && t.available == 1)
        {
            found = 1;

            

            b.chargeAmount = 50 + (b.distance * 15);

            printf("\n TAXI FOUND \n");

            printf("Driver Name : %s\n", t.driverName);
            printf("Car Name    : %s\n", t.carName);
            printf("Car Number  : %s\n", t.carNumber);

            printf("\nTotal Charge Amount : Rs %.2f\n", b.chargeAmount);


            printf("\nPAYMENT\n");

            printf("1. Cash\n");
            printf("2. UPI\n");
            printf("3. Card\n");

            printf("Choose Payment Method: ");
            scanf("%d", &paymentChoice);

            switch (paymentChoice)
            {
                case 1:

                    strcpy(b.paymentMethod, "Cash");
                    printf("\nCash Payment Selected\n");
                    break;

                case 2:
                {
                    char upiId[50];
                    strcpy(b.paymentMethod, "UPI");
                    printf("Enter UPI ID: ");
                    scanf("%s", upiId);
                    printf("\nProcessing UPI Payment...\n");
                    printf("Payment Successful!\n");
                    break;
                }

                case 3:
                {
                    char cardNumber[20];
                    strcpy(b.paymentMethod, "Card");
                    printf("Enter Card Number: ");
                    scanf("%s", cardNumber);
                    printf("\nProcessing Card Payment...\n");
                    printf("Payment Successful!\n");
                    break;
                }

                default:
                    strcpy(b.paymentMethod, "Cash");
                    printf("\nInvalid Option! Cash Selected\n");
            }

            strcpy(b.paymentStatus, "Paid");

    

            t.available = 0;
            fseek(ft, -sizeof(t), SEEK_CUR);
            fwrite(&t, sizeof(t), 1, ft);
            fwrite(&b, sizeof(b), 1, fb);

            printf("\nBOOKING CONFIRMED\n");
            printf("Booking ID       : %d\n", b.bookingId);
            printf("Customer Name    : %s\n", b.customerName);
            printf("Pickup Location  : %s\n", b.pickup);
            printf("Drop Location    : %s\n", b.drop);
            printf("Distance         : %.2f KM\n", b.distance);
            printf("Charge Amount    : Rs %.2f\n", b.chargeAmount);
            printf("Payment Method   : %s\n", b.paymentMethod);
            printf("Payment Status   : %s\n", b.paymentStatus);
            break;
        }
    }

    if (found == 0)
    {
        printf("\nNo Taxi Available At Your Location!\n");
    }
    fclose(ft);
    fclose(fb);
}

void completeRide()
{
    struct Taxi t;
    FILE *fp;
    int taxiId;
    int found = 0;
    fp = fopen("taxi.txt", "rb+");

    if (fp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }
    printf("\n===== COMPLETE RIDE =====\n");
    printf("Enter Taxi ID: ");
    scanf("%d", &taxiId);

    while (fread(&t, sizeof(t), 1, fp))
    {
        if (t.id == taxiId)
        {
            found = 1;
            t.available = 1;
            fseek(fp, -sizeof(t), SEEK_CUR);
            fwrite(&t, sizeof(t), 1, fp);
            printf("\nRide Completed Successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nTaxi Not Found!\n");
    }

    fclose(fp);
}

void viewBookings()
{
    struct Booking b;
    FILE *fp;
    fp = fopen("booking.txt", "rb");
    if (fp == NULL)
    {
        printf("\nNo Booking Records Found!\n");
        return;
    }

    printf("\nBOOKING HISTORY\n");

    while (fread(&b, sizeof(b), 1, fp))
    {
        printf("\nBooking ID       : %d\n", b.bookingId);
        printf("Customer Name    : %s\n", b.customerName);
        printf("Pickup Location  : %s\n", b.pickup);
        printf("Drop Location    : %s\n", b.drop);
        printf("Distance         : %.2f KM\n", b.distance);
        printf("Charge Amount    : Rs %.2f\n", b.chargeAmount);
        printf("Payment Method   : %s\n", b.paymentMethod);
        printf("Payment Status   : %s\n", b.paymentStatus);
    }

    fclose(fp);
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n BOOKING SYSTEM \n");

        printf("1. Add Taxi\n");
        printf("2. View Taxi\n");
        printf("3. Book Taxi\n");
        printf("4. Complete Ride\n");
        printf("5. View Booking History\n");
        printf("6. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addTaxi();
                break;

            case 2:
                viewTaxi();
                break;

            case 3:
                bookTaxi();
                break;

            case 4:
                completeRide();
                break;

            case 5:
                viewBookings();
                break;

            case 6:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}