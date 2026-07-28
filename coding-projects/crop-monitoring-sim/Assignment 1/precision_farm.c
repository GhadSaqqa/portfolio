// Ghad Saqqa, 8049890

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// without these (libraries) functions wont be recognised by C

// Constants and typedefs (no change here)
// #define basically creates a constant via simple text replacement. It is used here since we don't expect the values to change.
#define Max_plots 16 // define tells the code to replace every occurrence of "Max_plots". Assignment tells to 20 however it later specifies 1-4 for each crop meaning 4+4+4+4 = 16 is the max  
#define Moisture_threshold 30.0f // define replaces Moisture_threshold with 30.0f. 'f' makes it a float (4 bytes), faster and sufficient since high precision isn't needed.
#define Nutrient_decay 0.99f
#define Critical_nutrient 30.0f // nutrient threshold
#define Fertilizer_restore 20.0f
#define Max_Crops 4 // Wheat, corn ,rice and soybean

// Crop maturity periods (days)
const int MaturityDays[Max_Crops] = {120, 100, 150, 110}; //  Each crop has a maturity period: wheat - 120 days; corn 100 days; rice 150 days; soybean 110 days. This will be saved according to the order of CropType
// Base yields per hectare (kg)
const float BaseYields[Max_Crops] = {2880.0, 10000.0, 4500.0, 2000.0}; // yield per hectare of the respective crops are: wheat - 2,880 kg/ha; corn - 10,000 kg/ha; rice - 4,500 kg/ha; soybean - 2,000 kg/ha


// typedef defines CropType as a new type of variable, giving meaningful names (WHEAT, CORN, RICE, SOYBEAN) instead of plain integers. Makes code easier to read and maintain
typedef enum {WHEAT, CORN, RICE, SOYBEAN} CropType; // or enum CropType {WHEAT, CORN, RICE, SOYBEAN};

typedef struct {float N, P, K, Fe;} Nutrients; // 'Nutrients' is a new data type created for easier handling of plant nutrient data in a structured way. Specifying to code that N (Nitrogen), P (Phosphorus), K (Potassium), Fe (Iron) will be data with type "Nutrients". Using this will make code easier and more organised as it groups data (nutrients) with similar types together. This approach is easier to manage than handling them as individual variables or strings.  It also simplifies future input operations (e.g., using scanf) for nutrient values, making the code cleaner and more maintainable.

typedef struct {//new struct declared named "Costs" which will group resources and selling prices together into one struct respective to their crop type
    float water_cost;
    float fertilizer_cost;
    float pesticide_cost;
    float wheat_price;
    float corn_price;
    float rice_price;
    float soybean_price;
} Costs;
// after all plot variables have been declared its time to create struct to save all variables needed for the plot. Struct "Plot" holds everything needed for a single farm plot, This keeps farm data for each plot bundled, making it easier to manage and simulate.

typedef struct {
    CropType crop;
    int days_grown;
    float moisture;
    Nutrients nutrients;
    int rain_forecast;
    float pest_probability;
    int pest_damage;
    float water_used;
    float fertilizer_used;
    float pesticide_used;
    float yield;
    float revenue;
    float expenditure;
    float profit;
} Plot;
// note: this is basically creating a blueprint for the code to trace over but we still have to define each code in main


// Function Declarations: These tell C to expect the function in the code and allow the main() function to use it before its actual definition.

void load_costs(const char *filename, Costs *costs); // Loads resource costs from a file into the given Costs struct
void init_plot(Plot *p, CropType crop); // Initialises a Plot struct with random starting conditions and a specific crop type
void simulate_day(Plot *p, Costs *costs, int total_days); // Simulates one day of farm activity, updating the Plot and adjusting costs
void calculate_results(Plot *p, Costs *costs); // Calculates final yield, revenue, expenses, and profit for a given Plot based on Costs
void print_report(Plot *p, int plot_number, int crop_count, float price); // Prints a detailed report for a Plot including yield, revenue, expenditure, and profit

// Main function
int main(int argc, char *argv[]) {  // To run we are expecting only 4 arguments --> program name + 3 arguments (ex. precision_farm 90 5 resource_cost.dat) so if something is missing code should not run
    if (argc != 4) {
        printf("Error: Please provide 3 arguments (number_of_days, number_of_plots, resource_cost_file).\n");
        printf("Usage: %s <number_of_days> <number_of_plots> <resource_cost_file>\n", argv[0]); // argv[0] used to save file name --> for flexibility with different file names rather than hardcoded precision_farm
        return 1;
    }
    // Since arg will save arguments as text (even numbers) we need to convert to integers to proceed which is done using atoi --> ASIC to integer
    // arg[0] is file name--> precision_farm
    int total_days = atoi(argv[1]);
    int total_plots = atoi(argv[2]);

    if (total_plots < 1 || total_plots > Max_plots) { // already assigned max plots to be 20, so this will detect number of plots inputed by user and will operate accordingly if it =<20
        printf("Error: Number of plots must be between 1 and %d.\n", Max_plots);
        return 1;
    }

    Costs resources_costs;  // Create a variable 'resources_costs' of type 'Costs' (the struct)
    load_costs(argv[3], &resources_costs); // load_costs will open the resource file which is resource_cost.dat in this case, will read the numbers inside it and save them into the Costs struct that was made before respective to their name and location

    srand(time(NULL));  // Seed(initialise) the random number generator with the current time to ensure different results each time the program runs

    Plot farm[Max_plots]; // create variable 'farm' of type 'Plot' (the struct) allowing to plot what is needed only and was already declared before main
    int crop_counts[Max_Crops] = {0}; // Number of plots per crop

    // Assign plots to crops (up to 4 per crop)
    int plot_number = 0;
    /* we need at least 1 for each in the first 4 plots then at random, so:
     Assign 1 plot to each crop */
    for (int crop = 0; crop < Max_Crops && plot_number < total_plots; ++crop) {
        init_plot(&farm[plot_number], (CropType)crop); // Initialise the plot at the array farm[plot_number] with the randomly selected crop type (random_crop). CropType struct declared at the beginning, 
        crop_counts[crop]++; // add 1 if conditions of loop met
        plot_number++;
    }

    // Randomly assign the remaining plots
    while (plot_number < total_plots) {  // While there are still plots left to assign
        CropType random_crop = (CropType)(rand() % Max_Crops);  // Randomly select a crop type (0 to Max_Crops-1) (basically 0-3) as we already have one guaranteed from step 1, making the max 3 only and min 0
        init_plot(&farm[plot_number], random_crop);  // Initialize the plot at farm[plot_number] with the randomly selected crop
        crop_counts[random_crop]++;  // Increment the count of plots for the selected crop type
        plot_number++; 
    }

    // Simulation loop
    for (int current_day = 0; current_day < total_days; current_day++) {  // Loop for each day of the simulation
        for (int i = 0; i < total_plots; i++) {  // Loop for each plot of land
            simulate_day(&farm[i], &resources_costs, total_days);  // Pass total_days here
        }
    }

    // Final calculations and reports
    for (int i = 0; i < total_plots; i++) {  // Loop through all the plots again after the simulation
        calculate_results(&farm[i], &resources_costs);  // Calculate the final results for the current plot

        float price = 0; //   // Set price based on the crop type, switch is similar to if but more organised where it detects the case we have and display output accordingly
        switch (farm[i].crop) {
            case WHEAT: price = resources_costs.wheat_price; break;
            case CORN: price = resources_costs.corn_price; break;
            case RICE: price = resources_costs.rice_price; break;
            case SOYBEAN: price = resources_costs.soybean_price; break;
        }
        print_report(&farm[i], i, crop_counts[farm[i].crop], price);
    }

    return 0;
}

// Function Definitions

// Load resource costs from resources file
void load_costs(const char *filename, Costs *costs) { // load_costs reads resource cost data and will save in Costs struct 
    FILE *file = fopen(filename, "r"); // open file
    if (!file) { // if Null
        printf("Error opening resource cost file!\n");
        exit(1); // terminate
    }
    fscanf(file, "Water: %f\n", &costs->water_cost); //scan the file for the water cost and store it in water_cost in costs struct
    fscanf(file, "Fertilizer: %f\n", &costs->fertilizer_cost);
    fscanf(file, "Pesticide: %f\n", &costs->pesticide_cost);
    fscanf(file, "Wheat: %f; Corn: %f; Rice: %f; Soybean: %f;",
           &costs->wheat_price, &costs->corn_price, &costs->rice_price, &costs->soybean_price);
    fclose(file);
}

// Initialise a plot with random starting conditions
void init_plot(Plot *p, CropType crop) { 
    p->crop = crop; 
    p->days_grown = 0;
    p->nutrients.N = rand() % 101;  // Random value between 0 and 100 for Nitrogen though I doubt there will be zero nutrient in soil but put to adapt to different environments
    p->nutrients.P = rand() % 101;  
    p->nutrients.K = rand() % 101;  
    p->nutrients.Fe = rand() % 101; 
    p->moisture = 40.0f + rand() % 61; // realistically a farm will have proper moisture environment (70-80%) but to have this code run for different environments choose 40%-100%  
    p->rain_forecast = 0;
    p->pest_probability = rand() % 21; // 0–20% initial pest chance (realistic and average from multiple sources)
    p->pest_damage = 0;
    p->water_used = 0;
    p->fertilizer_used = 0;
    p->pesticide_used = 0;
    p->yield = 0;
    p->revenue = 0;
    p->expenditure = 0;
    p->profit = 0;
}

// Simulate one day of farm activity
void simulate_day(Plot *p, Costs *costs, int total_days) {   
    // Ensure days_grown does not exceed the input total_days or crop's maturity days
    if (p->days_grown < total_days && p->days_grown < MaturityDays[p->crop]) {
        p->days_grown++; // The code increments p->days_grown if the crop hasn't reached total_days or its maturity (MaturityDays[p->crop]
    }

    // Nutrient decay and fertilizer application
    p->nutrients.N *= Nutrient_decay;  //*= is multiply and equal so nutrients.N will become = nutrients.N * Nutrient decay
    p->nutrients.P *= Nutrient_decay;  
    p->nutrients.K *= Nutrient_decay;  
    p->nutrients.Fe *= Nutrient_decay; 

    // Fertilizer application when any nutrient falls below the critical threshold
    if (p->nutrients.N < Critical_nutrient || p->nutrients.P < Critical_nutrient || // || for "or" so if any nutrient is below its critical threshold the if function will be executed
        p->nutrients.K < Critical_nutrient || p->nutrients.Fe < Critical_nutrient) {
        
        if (p->nutrients.N < Critical_nutrient) { // if iron nutrient is detected to be less than critcal level, fertilizer will restore
            p->nutrients.N += Fertilizer_restore;
            p->fertilizer_used += 1.0f; // add to counter that fertilizer has been used
        }
        if (p->nutrients.P < Critical_nutrient) {
            p->nutrients.P += Fertilizer_restore;
            p->fertilizer_used += 1.0f; 
        }
        if (p->nutrients.K < Critical_nutrient) {
            p->nutrients.K += Fertilizer_restore;
            p->fertilizer_used += 1.0f; 
        }
        if (p->nutrients.Fe < Critical_nutrient) {
            p->nutrients.Fe += Fertilizer_restore;
            p->fertilizer_used += 1.0f; 
        }
    }

    // Moisture handling
    p->moisture -= (5 + rand() % 6);  // Lose 5-10% daily due to evaporation

    // Forecast rain
    p->rain_forecast = rand() % 2; // randomly between 0 and 1, 1 rains 0 not raining
    
    // Apply if rain  
    if (p->rain_forecast == 1) {
        p->moisture += (5 + rand() % 11);  // Moisture gain if it rains by 5 and 15 (0-10 but + 5 increases range)
    }

    // Irrigate if needed
    if (p->moisture < Moisture_threshold) {  // If moisture is below the threshold, apply irrigation
        float water_needed = (Moisture_threshold - p->moisture) * 10;
        p->water_used += water_needed;  // Add the water used to the total
        p->moisture = Moisture_threshold; // Bring moisture up to threshold
    }

    // Pest simulation
    p->pest_probability += rand() % 2;  // Adds 0 or 1 units per day

    // Realistically 20% would be critical and since each level is %5, set  pest damage when the pest probability reaches 4 or more
    if (p->pest_probability >= 4) { 
        p->pest_damage = rand() % 3 + 1;  // Randomly assign 1, 2, or 3 levels of damage each time 
        p->yield *= (1.0f - (0.05f * p->pest_damage));  // Reduce yield by 5% per damage level

        // Apply pesticide only when damage occurs
        p->pesticide_used += 0.5f * p->pest_damage;  // Apply 0.5L for each damage level
        p->pest_probability = 0;  // Reset after pesticide application
    }

    // Increment the number of days grown
    if (p->days_grown < total_days) {
        p->days_grown++;  // Ensure days_grown does not exceed input total_days
    }
}


// Function to calculate the results of the farm plot (yield, revenue, expenditure, and profit)
void calculate_results(Plot *p, Costs *costs) {
    float price = 0;  
    int maturity_days = 0; 
    float base_yield = 0;

    // Switch statement to set the price, maturity days, and base yield based on the crop type
    switch (p->crop) {
        case WHEAT: 
            price = costs->wheat_price;  // Set price for wheat
            maturity_days = MaturityDays[WHEAT];  // Set the number of days for wheat to mature
            base_yield = BaseYields[WHEAT];  // Set the base yield for wheat
            break;
        case CORN:
            price = costs->corn_price; 
            maturity_days = MaturityDays[CORN]; 
            base_yield = BaseYields[CORN]; 
            break;
        case RICE:
            price = costs->rice_price; 
            maturity_days = MaturityDays[RICE];
            base_yield = BaseYields[RICE]; 
            break;
        case SOYBEAN:
            price = costs->soybean_price; 
            maturity_days = MaturityDays[SOYBEAN]; 
            base_yield = BaseYields[SOYBEAN];  
            break;
    }

    // Calculate the maturity ratio based on the number of days grown and the total maturity days for the crop
    float maturity_ratio = (float)p->days_grown / maturity_days; 
    
    if (maturity_ratio > 1.0f) maturity_ratio = 1.0f;  // If the crop has been grown beyond its maturity period, set it to 1 (fully mature).

    // Calculate the yield based on the maturity ratio. If the crop is fully mature, it gets its base yield.
    p->yield = base_yield * maturity_ratio;

    // Nutrient penalties: Reduce yield by 10% for each nutrient that falls below its critical threshold.
    if (p->nutrients.N < Critical_nutrient) p->yield *= 0.9f;  // If nitrogen is below the critical threshold, reduce yield by 10%.
    if (p->nutrients.P < Critical_nutrient) p->yield *= 0.9f;  
    if (p->nutrients.K < Critical_nutrient) p->yield *= 0.9f; 
    if (p->nutrients.Fe < Critical_nutrient) p->yield *= 0.9f; 

    // Pest damage penalties: Reduce yield based on pest damage.
    p->yield *= (1.0f - (0.05f * p->pest_damage));  // For each level of pest damage, reduce yield by 5%.

    p->revenue = p->yield * price; // Yield * market price 
    p->expenditure = p->water_used * costs->water_cost + p->fertilizer_used * costs->fertilizer_cost + p->pesticide_used * costs->pesticide_cost; 
    p->profit = p->revenue - p->expenditure;  // Revenue - total resource cost
}

// Function to print a detailed report for each plot, including yield, revenue, water usage, pesticide usage, and profit.
void print_report(Plot *p, int plot_number, int crop_count, float price) {
    // Array to store crop names
    const char *crop_names[] = {"Wheat", "Corn", "Rice", "Soybean"};

    // Print plot information: crop name, days grown, yield, price, revenue, expenditure, and profit
    printf("Plot %d Crop: %s \n\n", plot_number + 1, crop_names[p->crop]);  
    printf("Days Grown: %d / %d\n", p->days_grown, MaturityDays[p->crop]); 
    printf("Yield: %.2f kg\n", p->yield);  
    printf("Price: $%.2f/kg\n", price);  
    printf("Revenue: $%.2f\n", p->revenue);  
    printf("Expenditure: $%.2f\n", p->expenditure);  
    printf("Water Used: %.2f L\n", p->water_used);  
    printf("Fertilizer Used: %.2f kg\n", p->fertilizer_used);  
    printf("Pesticide Used: %.2f L\n", p->pesticide_used);  
    printf("Profit/Loss: $%.2f\n", p->profit);  

    // Print if the plot was unprofitable (if profit is less than 0)
    printf("\n\n");
    if (p->profit < 0) {
        printf(">> This plot was unprofitable.\n"); 
    }
}
