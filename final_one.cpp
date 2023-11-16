    #include <iostream>
    #include <string>
    #include <map>
    #include <set>
    #include <fstream>
    #include <sstream>

    using namespace std;

    struct Event {
        string eventName;
        string organizer;
        string description;
        int availableSeats;
    };

    class UniversityEventManagement {
    private:
        map<string, Event> events;
        map<string, string> enrollmentIds;
        map<pair<string, string>, int> bookings; // Updated to store (enrollmentId, eventName) along with the number of tickets

    public:
        void addEvent(const string& eventName, const Event& event) {
            events[eventName] = event;
        }

        void displayAllEvents() {
            for (const auto& event : events) {
                cout << "\n";
                cout << "-------------------------------------------------------------------\n";
                cout << "Event Name: " << event.first << "\n";
                cout << "Organizer: " << event.second.organizer << "\n";
                cout << "Description: " << event.second.description << "\n";
                cout << "Available Seats: " << event.second.availableSeats << "\n";
                cout << "--------------------------------------------------------------------\n";
                cout << "\n";
            }
        }

        bool bookEvent(const string& enrollmentId, const string& eventName, int numTickets) {
            if (enrollmentIds.find(enrollmentId) == enrollmentIds.end()) {
                cout << "Invalid Enrollment ID." << endl;
                return false;
            }

            if (events.find(eventName) == events.end()) {
                cout << "Event not found." << endl;
                return false;
            }

            int availableSeats = events[eventName].availableSeats;
            if (numTickets > availableSeats) {
                cout << "Not enough available seats for " << numTickets << " ticket(s)." << endl;
                return false;
            }

            // Check if the booking already exists
            if (bookings.find({enrollmentId, eventName}) != bookings.end()) {
                int bookedTickets = bookings[{enrollmentId, eventName}];
                if (bookedTickets + numTickets > availableSeats) {
                    cout << "You have already booked " << bookedTickets << " ticket(s) for this event. You cannot book more than " << availableSeats << " ticket(s)." << endl;
                    return false;
                }
                bookings[{enrollmentId, eventName}] += numTickets;
            } else {
                bookings[{enrollmentId, eventName}] = numTickets;
            }

            events[eventName].availableSeats -= numTickets;

            // Store the booking with the number of tickets
            storeBooking(enrollmentId, eventName, numTickets);

            cout << "Booking successful! Enjoy the event." << endl;
            return true;
        }

        void registerEnrollmentId(const string& enrollmentId) {
            if (isValidEnrollmentId(enrollmentId)) {
                enrollmentIds[enrollmentId] = "";
                cout << "Enrollment ID registered successfully!" << endl;
                saveEnrollmentIds();
            } else {
                cout << "Invalid enrollment ID format. Registration failed." << endl;
            }
        }

        bool isValidEnrollmentId(const string& enrollmentId) {
            return enrollmentId.find('@') != string::npos &&
                enrollmentId.substr(enrollmentId.find('@')) == "@bennett.edu.in";
        }

        void storeBooking(const string& enrollmentId, const string& eventName, int numTickets) {
            ofstream csvFile("bookings.csv", ios::app);
            if (csvFile.is_open()) {
                csvFile << enrollmentId << "," << eventName << "," << numTickets << "\n";
                csvFile.close();
            } else {
                cout << "Error: Unable to open the CSV file for storing bookings." << endl;
            }
        }

        void saveEnrollmentIds() {
            ofstream csvFile("enrollmentIds.csv");
            if (csvFile.is_open()) {
                for (const auto& enrollment : enrollmentIds) {
                    csvFile << enrollment.first << "\n";
                }
                csvFile.close();
            } else {
                cout << "Error: Unable to open the CSV file for saving enrollment IDs." << endl;
            }
        }

        void loadEnrollmentIds() {
            ifstream csvFile("enrollmentIds.csv");
            if (csvFile.is_open()) {
                string enrollmentId;
                while (getline(csvFile, enrollmentId)) {
                    enrollmentIds[enrollmentId] = "";
                }
                csvFile.close();
            } else {
                cout << "No saved enrollment IDs found." << endl;
            }
        }

        void loadBookings() {
            ifstream csvFile("bookings.csv");
            if (csvFile.is_open()) {
                string line;
                while (getline(csvFile, line)) {
                    stringstream ss(line);
                    string enrollmentId, eventName;
                    int numTickets;
                    getline(ss, enrollmentId, ',');
                    getline(ss, eventName, ',');
                    ss >> numTickets;
                    bookings[{enrollmentId, eventName}] = numTickets;
                }
                csvFile.close();
            }
        }
    };

    int main() {
        UniversityEventManagement eventManager;
        eventManager.loadEnrollmentIds();
        eventManager.loadBookings();

        Event event1 = {"Survive_First_Year", "WIEEE", "Tips for getting a good start in college!", 250};
        Event event2 = {"Movie_Screening", "ANSH", "Enjoy a movie with your pals!", 150};
        Event event3 = {"Anime_Character_Cosplay", "Anime_Club", "Cosplaying anime characters is a great way to express your affection for them!", 20};
        Event event4 = {"Bgmi_Tournament", "BU_Gamers", "Demonstrate your talents in the online battleground with your four friends!", 64};
        Event event5 = {"Dance_Competition", "RIVAAZ", "If you enjoy dancing, put your skills on display on stage!", 10};
        Event event6 = {"Lyricism", "ADVAITA", "Show the power of your lyricism!", 50};

        eventManager.addEvent("Survive_First_Year", event1);
        eventManager.addEvent("Movie_Screening", event2);
        eventManager.addEvent("Anime_Character_Cosplay", event3);
        eventManager.addEvent("Bgmi_Tournament", event4);
        eventManager.addEvent("Dance_Competition", event5);
        eventManager.addEvent("Lyricism", event6);


        cout << "-------------------------------------------------------------------------------------------\n";
        cout<< "\n";
        cout << "           EEEEEE  V       V EEEEEE N      N TTTTTTT IIIIIII FFFFFFF YY     YY \n";
        cout << "           E        V     V  E      N N    N    T       I    F         Y   Y   \n";
        cout << "           EEEEEE    V   V   EEEEEE N  N   N    T       I    FFFFFF      Y     \n";
        cout << "           E          V V    E      N   N  N    T       I    F           Y     \n";
        cout << "           EEEEEE      V     EEEEEE N     NN    T    IIIIIII F           Y     \n";
        cout<< "\n";
        cout << "--------------------------------------------------------------------------------------------\n";
        cout<< "\n";
        cout << "                                WELCOME TO EVENTIFY\n";
        cout << "                           -----------------------------\n";


        char choice;
        string enrollmentId, eventName;
        int numTickets;

        do {
            cout<< "---------------------------\n";
            cout << "Menu:\n";
            cout<< "---------------------------\n";
            cout << "1. Display All Events\n";
            cout << "2. Register\n";
            cout << "3. Book an Event\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout<< "---------------------------\n";


            switch (choice) {
                case '1':
                    eventManager.displayAllEvents();
                    break;

                case '2':
                    cout << "Enter your enrollment ID: ";
                    cin >> enrollmentId;
                    eventManager.registerEnrollmentId(enrollmentId);
                    break;

                case '3':
                    cout << "Enter your enrollment ID: ";
                    cin >> enrollmentId;
                    cout << "Enter the event name: ";
                    cin >> eventName;
                    cout << "Enter the number of tickets to book: ";
                    cin >> numTickets;
                    eventManager.bookEvent(enrollmentId, eventName, numTickets);
                    break;

                case '4':
                    cout << "Goodbye!" << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != '4');

        return 0;
    }