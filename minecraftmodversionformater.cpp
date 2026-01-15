#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Global maps for stages, build types, and their abbreviations
map<string, string> stages = {
    {"1", "Pre-Alpha"},
    {"2", "Alpha"},
    {"3", "Beta"},
    {"4", "Release Candidate"},
    {"5", "Release"}
};

map<string, string> stage_abbrev = {
    {"Pre-Alpha", "PA"},
    {"Alpha", "A"},
    {"Beta", "B"},
    {"Release Candidate", "RC"},
    {"Release", "R"}
};

map<string, string> build_types = {
    {"1", "Development Build"},
    {"2", "Development Preview"},
    {"3", "Experimental Build"},
    {"4", "Test Build"},
    {"5", "Snapshot"},
    {"6", "Stable Build"}
};

map<string, string> build_suffix = {
    {"Development Build", "d"},
    {"Development Preview", "p"},
    {"Experimental Build", "e"},
    {"Test Build", "t"},
    {"Snapshot", "x"},
    {"Stable Build", "s"}
};

string choose_option(map<string, string>& options, const string& prompt) {
    cout << "\n" << prompt << endl;
    for (const auto& pair : options) {
        cout << pair.first << ". " << pair.second << endl;
    }
    
    string choice;
    while (true) {
        cout << "Enter the number of your choice: ";
        cin >> choice;
        if (options.find(choice) != options.end()) {
            return options[choice];
        }
        cout << "Invalid choice, try again." << endl;
    }
}

string get_build_number() {
    string build_number;
    while (true) {
        cout << "Enter Build Number (e.g., 001): ";
        cin >> build_number;
        
        // Check if all characters are digits and length is <= 3
        bool is_valid = !build_number.empty() && build_number.length() <= 3;
        for (char c : build_number) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
        
        if (is_valid) {
            // Pad with zeros
            while (build_number.length() < 3) {
                build_number = "0" + build_number;
            }
            return build_number;
        }
        cout << "Please enter a numeric build number (max 3 digits)." << endl;
    }
}

void create_new() {
    cout << "\n=== Create New Version ===" << endl;
    string stage = choose_option(stages, "Select the Stage:");
    string build_type = choose_option(build_types, "Select the Build Type:");
    string build_number = get_build_number();

    string readable = "BehindtheBedrock " + stage + " " + build_type + " " + build_number;
    string compact = stage_abbrev[stage] + "0.1." + build_number + build_suffix[build_type];

    cout << "\n✅ Generated Version Names:" << endl;
    cout << "Readable / Display: " << readable << endl;
    cout << "Compact / Code:     " << compact << endl;
}

void update_existing() {
    cout << "\n=== Update Existing Version ===" << endl;
    cout << "Paste your existing Readable or Compact version: ";
    cin.ignore(); // Clear newline from previous input
    string existing;
    getline(cin, existing);

    string stage_found, build_type_found, build_number_found;

    // Try to parse readable format
    if (existing.find("BehindtheBedrock") == 0) {
        // Look for known stages in the string
        bool stage_identified = false;
        for (const auto& pair : stages) {
            if (existing.find(pair.second) != string::npos) {
                stage_found = pair.second;
                stage_identified = true;
                break;
            }
        }
        if (!stage_identified) {
            cout << "Could not identify the stage. Make sure it is correct." << endl;
            return;
        }

        // Look for known build types
        bool build_type_identified = false;
        for (const auto& pair : build_types) {
            if (existing.find(pair.second) != string::npos) {
                build_type_found = pair.second;
                build_type_identified = true;
                break;
            }
        }
        if (!build_type_identified) {
            cout << "Could not identify the build type. Make sure it is correct." << endl;
            return;
        }

        // Extract build number (last 3 digits)
        string digits;
        for (int i = existing.length() - 1; i >= 0 && digits.length() < 3; i--) {
            if (isdigit(existing[i])) {
                digits = existing[i] + digits;
            }
        }
        build_number_found = digits;

    } else {
        // Try compact format
        bool stage_identified = false;
        for (const auto& pair : stage_abbrev) {
            if (existing.find(pair.second) == 0) {
                stage_found = pair.first;
                stage_identified = true;
                break;
            }
        }
        if (!stage_identified) {
            cout << "Could not detect stage from compact format." << endl;
            return;
        }

        // Extract build number (last 3 digits before suffix)
        string digits;
        for (char c : existing) {
            if (isdigit(c)) {
                digits += c;
            }
        }
        if (digits.length() >= 3) {
            build_number_found = digits.substr(digits.length() - 3, 3);
        }

        // Get suffix (last character)
        char suffix = existing[existing.length() - 1];
        bool build_type_identified = false;
        for (const auto& pair : build_suffix) {
            if (pair.second[0] == suffix) {
                build_type_found = pair.first;
                build_type_identified = true;
                break;
            }
        }
        if (!build_type_identified) {
            cout << "Could not parse version. Please paste a correct Readable or Compact version." << endl;
            return;
        }
    }

    cout << "\nCurrent Version:" << endl;
    cout << "Stage: " << stage_found << endl;
    cout << "Build Type: " << build_type_found << endl;
    cout << "Build Number: " << build_number_found << endl;

    int build_num = stoi(build_number_found) + 1;
    string new_build_number = to_string(build_num);
    while (new_build_number.length() < 3) {
        new_build_number = "0" + new_build_number;
    }
    cout << "New Build Number: " << new_build_number << endl;

    string readable = "BehindtheBedrock " + stage_found + " " + build_type_found + " " + new_build_number;
    string compact = stage_abbrev[stage_found] + "0.1." + new_build_number + build_suffix[build_type_found];

    cout << "\n✅ Updated Version Names:" << endl;
    cout << "Readable / Display: " << readable << endl;
    cout << "Compact / Code:     " << compact << endl;
}

void help_menu() {
    cout << R"(
=== Help Menu ===

Stages:
- Pre-Alpha: Very early internal version.
- Alpha: Core gameplay in, but unstable.
- Beta: Feature-complete, may still have bugs.
- Release Candidate (RC): Almost final, testing for release.
- Release: Stable public version.

Build Types:
- Development Build: Raw internal dev build.
- Development Preview: Early version for other devs.
- Experimental Build: New features; might be unstable.
- Test Build: QA/testing build.
- Snapshot: Public preview build.
- Stable Build: Polished, safe build.

Usage:
1. Create New: Generate a brand new version.
2. Update Existing: Increment build number from an existing version.
3. Help Menu: Shows this information.
)" << endl;
}

int main() {
    cout << "=== BehindtheBedrock Version Generator ===" << endl;
    
    map<string, string> options = {
        {"1", "Create New Version"},
        {"2", "Update Existing Version"},
        {"3", "Help Menu"}
    };

    string choice = choose_option(options, "Select an option:");
    
    if (choice == "Create New Version") {
        create_new();
    } else if (choice == "Update Existing Version") {
        update_existing();
    } else if (choice == "Help Menu") {
        help_menu();
    }

    return 0;
}
