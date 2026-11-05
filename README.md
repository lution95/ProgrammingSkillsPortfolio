# C++ Programming Challenges

Three console applications demonstrating C++ functions, input validation, file handling, structures, classes, and persistent data storage.

## Projects

| Challenge | Application | Description |
|---|---|---|
| 1 | CO₂ Calculator | Estimates emissions from a car journey |
| 2 | Alexa, Tell Me a Joke | Loads jokes from a file and reveals punchlines interactively |
| 3 | Book Manager | Lists, borrows, and returns books, saving availability changes |

## Requirements

- A C++ compiler supporting C++11 or later
- A terminal or C++ development environment
- `randomJokes.txt` for the joke application
- `bookData.txt` for the Book Manager

Run file-based applications from a directory containing their required data files.

## Build and Run

Compile each application separately. The source filenames below are examples; replace them with the filenames in this repository.

```bash
g++ -std=c++11 co2Calculator.cpp -o co2Calculator
g++ -std=c++11 jokeApp.cpp -o jokeApp
g++ -std=c++11 bookManager.cpp -o bookManager
```

Run an application:

```bash
./co2Calculator
./jokeApp
./bookManager
```

On Windows, run the corresponding `.exe` file.

## Challenge 1: CO₂ Calculator

Calculates estimated CO₂ emissions using the distance travelled in miles and the selected fuel type.

### Features

- Accepts decimal distances, including zero
- Rejects negative distances, non-finite values, text, and extra characters
- Accepts `D` for diesel or `P` for petrol, in either letter case
- Displays results to two decimal places
- Handles unexpectedly ended input through an exception

### Program Structure

- `getDistance()` reads and validates the journey distance.
- `getFuelType()` reads and validates the fuel choice.
- `calculateEmissions()` calculates the estimated emissions.
- `main()` coordinates the functions and prints the result.

### Calculation

The calculator assumes fuel consumption of **9.66 litres per 100 miles**.

```text
Fuel used (litres) = (distance in miles / 100) × 9.66
CO₂ emissions (kg) = fuel used × emission factor
```

| Fuel | Emission factor | Result for 100 miles |
|---|---|---|
| Diesel | 2.68 kg CO₂ per litre | 25.89 kg CO₂ |
| Petrol | 2.31 kg CO₂ per litre | 22.31 kg CO₂ |

These estimates use a fixed fuel-consumption rate and do not account for differences in vehicles or driving conditions.

## Challenge 2: Alexa, Tell Me a Joke

A text-based joke application that loads jokes from `randomJokes.txt`.

### Usage

1. Start the application.
2. Enter `Alexa, tell me a joke`.
3. Read the randomly selected setup.
4. Press Enter to reveal the punchline.
5. Repeat, or enter `quit` to exit.

Requests are converted to lowercase, allowing different letter cases.

### Features

- Stores each setup and punchline together in a `Joke` structure
- Uses a `vector<Joke>` to hold loaded jokes
- Splits each record at its first question mark
- Skips malformed lines and removes trailing carriage returns
- Reports an error and exits if no jokes load
- Seeds the random generator once at startup

### Data File

Each joke must occupy one line. The first question mark separates the setup from the punchline.

Example:

```text
What do you call a bear with no teeth? A gummy bear!
```

## Challenge 3: Book Manager

Manages books loaded from `bookData.txt`, with availability changes saved between runs.

### Features

- Lists all loaded books
- Displays an individual book by ID
- Borrows and returns books
- Prevents borrowing an already borrowed book
- Prevents returning an already available book
- Validates records and rejects duplicate IDs
- Saves availability changes to the data file

### Program Structure

Each `Book` object stores:

- Title
- Author
- Page count
- ID
- Borrowed status

Private attributes are accessed or updated through public methods.

- `loadBooks()` reads and validates comma-separated records.
- `askForBook()` finds a book by ID and returns a pointer or `nullptr`.
- `setBorrowed()` updates its borrowed status.
- `saveBooks()` writes changes to the data file.

Invalid records are skipped. The program stops if no books load.

### Data File

Each record contains five comma-separated fields representing the title, author, page count, ID, and borrowed status. Use the field order and status encoding expected by `loadBooks()`.

### Reported Checks

The supplied project report describes:

- Loading and listing all ten supplied books
- Viewing book `002`, *1984*
- Borrowing the book and confirming its saved status after restarting
- Returning the book and confirming its availability after another restart

### Known Limitation

If saving fails, the availability change is reversed in memory. However, an interruption while rewriting the file may leave the saved data incomplete. Back up `bookData.txt` before testing.

## C++ Concepts Demonstrated

- Functions and named constants
- Input validation using streams
- String processing and case conversion
- File input and output
- Structures and vectors
- Classes and encapsulation
- Pointers and `nullptr`
- Exceptions
- Numeric output formatting

## References

References supplied with the project report:

- Dantas, C.E.C., Rocha, A.M. and Maia, M.A. (2023). *How do Developers Improve Code Readability? An Empirical Study of Pull Requests.* IEEE International Conference on Software Maintenance and Evolution. https://doi.org/10.1109/ICSME58846.2023.00022
- Microsoft (2022). *basic_ifstream class.* Microsoft Learn. https://learn.microsoft.com/en-us/cpp/standard-library/basic-ifstream-class?view=msvc-170
- Microsoft (2025). *basic_istream class.* Microsoft Learn. https://learn.microsoft.com/en-us/cpp/standard-library/basic-istream-class?view=msvc-170
- Paiva, J.C., Leal, J.P. and Figueira, A. (2022). *Automated Assessment in Computer Science Education: A State-of-the-Art Review.* ACM Transactions on Computing Education, 22(3), article 34. https://doi.org/10.1145/3513140
- Rani, P. et al. (2023). *A decade of code comment quality assessment: A systematic literature review.* Journal of Systems and Software, 195, 111515. https://doi.org/10.1016/j.jss.2022.111515
- Stroustrup, B. (2024). *Programming: Principles and Practice Using C++.* 3rd edn. Addison-Wesley Professional.
