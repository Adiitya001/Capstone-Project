#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class JournalEntry {
public:
    string date;
    string mood;
    string entry;

    // Mark display() as const
    void display() const {
        cout << "Date: " << date << endl;
        cout << "Mood: " << mood << endl;
        cout << "Entry: " << entry << endl;
    }
};

void saveEntry(const JournalEntry& entry) {
    ofstream file("journal.txt", ios::app);
    if (file.is_open()) {
        file << entry.date << "|" << entry.mood << "|" << entry.entry << endl;
        file.close();
        cout << "Entry saved successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

vector<JournalEntry> loadEntries() {
    vector<JournalEntry> entries;
    ifstream file("journal.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            JournalEntry entry;
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            entry.date = line.substr(0, pos1);
            entry.mood = line.substr(pos1 + 1, pos2 - pos1 - 1);
            entry.entry = line.substr(pos2 + 1);
            entries.push_back(entry);
        }
        file.close();
    }
    return entries;
}

void createEntry() {
    JournalEntry newEntry;
    cout << "Enter the date (DD/MM/YYYY): ";
    getline(cin, newEntry.date);

    cout << "Enter your mood (e.g., Happy, Sad, Excited, etc.): ";
    getline(cin, newEntry.mood);

    cout << "Write your journal entry: ";
    getline(cin, newEntry.entry);

    saveEntry(newEntry);
}

void viewEntries() {
    vector<JournalEntry> entries = loadEntries();
    if (entries.empty()) {
        cout << "No entries found!" << endl;
    } else {
        for (const auto& entry : entries) {
            entry.display();  // Now we can call this on const objects
            cout << "-----------------------" << endl;
        }
    }
}

int main() {
    int choice;
    do {
        cout << "Mood-Based Journal App\n";
        cout << "1. Create a new journal entry\n";
        cout << "2. View previous entries\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            createEntry();
            break;
        case 2:
            viewEntries();
            break;
        case 3:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 3);

    return 0;
}
