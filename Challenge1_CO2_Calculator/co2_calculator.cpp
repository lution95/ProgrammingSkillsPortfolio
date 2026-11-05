#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <iomanip>
using namespace std;
const double LITRES_PER_100_MILES = 9.66;
const double DIESEL_KG_PER_LITRE = 2.68;
const double PETROL_KG_PER_LITRE = 2.31;
// Validate complete distance input.
double getDistance()
{
    double distance;
    string input;
    while (true)
    {
        cout << "Distance (miles): ";
        if (!getline(cin, input)) throw runtime_error("Input ended.");
        istringstream stream(input);
        if (stream >> distance && (stream >> ws).eof() && isfinite(distance)
            && distance >= 0 && distance <= numeric_limits<double>::max() / DIESEL_KG_PER_LITRE)
        {
            return distance;
        }
        cout << "Invalid distance. Use 0+." << endl;
    }
}
// Accept diesel or petrol.
char getFuelType()
{
    string input;
    while (true)
    {
        cout << "Fuel (D/P): ";
        if (!getline(cin, input)) throw runtime_error("Input ended.");
        char choice = input.size() == 1 ? static_cast<char>(toupper(static_cast<unsigned char>(input[0]))) : '\0';
        if (input.length() == 1 && (choice == 'D' || choice == 'P'))
        {
            return choice;
        }
        cout << "Invalid fuel. Use D/P." << endl;
    }
}
// Calculate emissions in kilograms.
double calculateEmissions(double distance, char fuelType)
{
    double litresUsed = (distance / 100.0) * LITRES_PER_100_MILES;
    double kgPerLitre = (fuelType == 'D') ? DIESEL_KG_PER_LITRE : PETROL_KG_PER_LITRE;
    return litresUsed * kgPerLitre;
}

int main()
{
    try {
    cout << "CO2 Calculator" << endl;

    double distance = getDistance();
    char fuelType = getFuelType();
    double emissions = calculateEmissions(distance, fuelType);

    cout << fixed << setprecision(2);
    cout << "\nJourney: " << distance << " miles ("
         << (fuelType == 'D' ? "diesel" : "petrol") << ")" << endl;
    cout << "CO2: " << emissions << " kg" << endl;

    return 0;
    } catch (const runtime_error &error) {
        cout << error.what() << endl;
        return 1;
    }
}
