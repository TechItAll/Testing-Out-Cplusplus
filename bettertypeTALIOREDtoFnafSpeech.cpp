#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

class SlowTyper {
private:
    string file_path;
    double default_delay;
    double punctuation_delay;
    string pause_text;

public:
    /**
     * Initialize the SlowTyper instance with file path and typing settings.
     * 
     * Args:
     * - file_path: Path to the file to be typed out.
     * - default_delay: Default delay between characters (in seconds).
     * - punctuation_delay: Delay after punctuation (in seconds).
     * - pause_text: Text to display when pausing for input.
     */
    SlowTyper(const string& file_path, double default_delay = 0.05, 
              double punctuation_delay = 0.2, const string& pause_text = "\n(Press Enter to continue...)")
        : file_path(file_path), default_delay(default_delay), 
          punctuation_delay(punctuation_delay), pause_text(pause_text) {}

    /**
     * Clear the console screen.
     */
    static void clear_screen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    /**
     * Sleep for a specified duration in seconds.
     */
    void sleep_seconds(double seconds) {
        this_thread::sleep_for(chrono::milliseconds(static_cast<int>(seconds * 1000)));
    }

    /**
     * Check if a character is a digit.
     */
    bool is_digit(char c) {
        return c >= '0' && c <= '9';
    }

    /**
     * Reads text from a file and types it out slowly with Markdown-like support.
     * 
     * Features:
     * - `[X]`: Custom delay where X is a number in seconds.
     * - `[I]`: Pause and wait for user input before continuing.
     * - Handles Markdown styles (e.g., **bold**, *italic*) character by character.
     */
    void slow_type() {
        try {
            // Open the file and read its contents
            ifstream file(file_path);
            if (!file.is_open()) {
                cerr << "Error: File '" << file_path << "' not found." << endl;
                return;
            }

            string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();

            // Clear the screen before starting
            clear_screen();

            size_t i = 0;
            while (i < text.length()) {
                char current_char = text[i];

                // Handle Markdown-like tags
                if (current_char == '[') {
                    // Detect custom delay tag [X]
                    if (i + 1 < text.length() && is_digit(text[i + 1])) {
                        size_t end_idx = text.find(']', i);
                        if (end_idx != string::npos) {
                            string delay_str = text.substr(i + 1, end_idx - i - 1);
                            double custom_delay = stod(delay_str);
                            sleep_seconds(custom_delay);
                            i = end_idx; // Move index to after the closing bracket
                        }
                    }
                    // Detect pause tag [I]
                    else if (i + 1 < text.length() && text[i + 1] == 'I') {
                        cout << pause_text;
                        cin.ignore();
                        i += 2; // Skip past [I]
                        continue;
                    }
                }
                // Handle basic punctuation delays
                else if (current_char == '.' || current_char == '!' || current_char == '?') {
                    cout << current_char << flush;
                    sleep_seconds(punctuation_delay);
                }
                else if (current_char == ',' || current_char == ';' || current_char == ':') {
                    cout << current_char << flush;
                    sleep_seconds(punctuation_delay / 2);
                }
                else if (current_char == '\n') {
                    cout << current_char << flush;
                    sleep_seconds(punctuation_delay / 1.5);
                }
                // Handle Markdown-like **bold** or *italic* character by character
                else if (current_char == '*' && i + 1 < text.length()) {
                    if (text[i + 1] == '*') {  // **bold**
                        size_t end_idx = text.find("**", i + 2);
                        if (end_idx != string::npos) {
                            string bold_text = text.substr(i + 2, end_idx - i - 2);
                            for (char b_char : bold_text) {
                                cout << "\033[1m" << b_char << "\033[0m" << flush;  // Bold using ANSI
                                sleep_seconds(default_delay);
                            }
                            i = end_idx + 1;
                        } else {
                            cout << current_char << flush;
                        }
                    } else {  // *italic*
                        size_t end_idx = text.find('*', i + 1);
                        if (end_idx != string::npos) {
                            string italic_text = text.substr(i + 1, end_idx - i - 1);
                            for (char i_char : italic_text) {
                                cout << "\033[3m" << i_char << "\033[0m" << flush;  // Italic using ANSI
                                sleep_seconds(default_delay);
                            }
                            i = end_idx;
                        } else {
                            cout << current_char << flush;
                        }
                    }
                }
                else {
                    // Print other characters normally
                    cout << current_char << flush;
                    sleep_seconds(default_delay);
                }
                i++;
            }

            cout << endl;  // Move to the next line after printing
        }
        catch (const exception& e) {
            cerr << "An unexpected error occurred: " << e.what() << endl;
        }
    }
};

// Example usage
int main() {
    string file_path = R"(C:\Users\blues\OneDrive\Desktop\VsCode\note.txt)";
    SlowTyper typer(file_path, 0.07, 0.5, "");
    typer.slow_type();

    return 0;
}
